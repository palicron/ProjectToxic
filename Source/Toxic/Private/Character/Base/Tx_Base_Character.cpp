// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Base/Tx_Base_Character.h"
#include "AbilitySystemComponent.h"
#include "Abilitys/GameplayAbility_Base.h"
#include "Abilitys/Stats/BaseAttributeSetBase.h"
#include "Character/Tx_Base_AICharacterCtr.h"
#include "Character/Tx_OverHeadBar.h"
#include "Character/Tx_PlayerMainUI.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Player/Tx_PlayerCamera.h"
#include "Player/Tx_PlayerCtr.h"

// Sets default values
ATx_Base_Character::ATx_Base_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	NetUpdateFrequency = 66.f;
	MinNetUpdateFrequency = 33.f;

	CurrentCharacterState = CharacterState::Cs_Idle;

	UnderCircleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Under Circle"));
	
	UnderCircleMesh->SetupAttachment(RootComponent);

	OverHeadBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHead LifeBar"));
	
	OverHeadBarWidget->SetupAttachment(RootComponent);
	
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem Comp"));

	AttributeSerBaseComp = CreateDefaultSubobject<UBaseAttributeSetBase>(TEXT("Attribute Base"));

}

UAbilitySystemComponent* ATx_Base_Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void ATx_Base_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATx_Base_Character,CurrentTargetCharacter);
	DOREPLIFETIME(ATx_Base_Character,CurrentCharacterState);
	DOREPLIFETIME_CONDITION(ATx_Base_Character,LastClickTarget,COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ATx_Base_Character,OwningPlayerRef,COND_OwnerOnly);
}


// Called when the game starts or when spawned
void ATx_Base_Character::BeginPlay()
{
	Super::BeginPlay();

	
	AcquireAbility(AbilityAttackRef);

	for (const auto& AbilityRef : AbilitySlots)
	{
		if(IsValid(AbilityRef.Value))
		{
			AcquireAbility(AbilityRef.Value);
		}
		
	}
	
	if(AbilitySystemComp)
	{
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSerBaseComp->GetHealthAttribute()).AddUObject(this,&ATx_Base_Character::OnHealthChange);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSerBaseComp->GetMaxHealthAttribute()).AddUObject(this,&ATx_Base_Character::OnMaxHealthChange);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSerBaseComp->GetManaAttribute()).AddUObject(this,&ATx_Base_Character::OnManaChange);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSerBaseComp->GetMaxManaAttribute()).AddUObject(this,&ATx_Base_Character::OnMaxManahChange);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSerBaseComp->GetMovementSpeedAttribute()).AddUObject(this,&ATx_Base_Character::OnMovementSpeedChange);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSerBaseComp->GetBaseStrengthAttribute()).AddUObject(this,&ATx_Base_Character::OnStrChange);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSerBaseComp->GetBonusStrengthAttribute()).AddUObject(this,&ATx_Base_Character::OnBonusStrChange);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSerBaseComp->GetBaseIntelligenceAttribute()).AddUObject(this,&ATx_Base_Character::OnIntChange);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSerBaseComp->GetBonusIntelligenceAttribute()).AddUObject(this,&ATx_Base_Character::OnBonusIntChange);
	}

	BP_SpeedChange();
	BP_OnHealthChange(1.0f);
	
	OverHeadLifeBarRef = Cast<UTx_OverHeadBar>(OverHeadBarWidget->GetWidget());
	
	if(IsValid(OverHeadLifeBarRef))
	{
		OverHeadLifeBarRef->SetHealthPercentage(1.f);
	}

	GetWorld()->GetTimerManager().SetTimer(InitialDelayHandle,this,&ATx_Base_Character::InitStartingGamePlayEffects,0.2,false);
	
}

void ATx_Base_Character::CheckDistanceToAttack() 
{
	const UWorld* WorldRef =  GetWorld();
	if(WorldRef && HasAuthority())
	{
		WorldRef->GetTimerManager().SetTimer(MeleeAttackHandle,this ,
				&ATx_Base_Character::TryToAttackTarget,.5f,true);	
	}
	
}

void ATx_Base_Character::StopAllActionByPlayer()
{
	AbilitySystemComp->CancelAllAbilities();

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	//SetCurrentCharacterState(CharacterState::Cs_Idle);

	SetCurrentActorTarget(nullptr);

	if(AIControllerReference)
	{
		AIControllerReference->StopMovement();
	}

	
}

void ATx_Base_Character::ConfirmTargetAbility()
{

	if(HasAuthority() && IsValid(AbilitySystemComp))
	{
		AbilitySystemComp->TargetConfirm();
	}
}

void ATx_Base_Character::OnRep_OwningPlayerRef()
{
	if(IsValid(OwningPlayerRef) && !HasAuthority())
	{
	//	OwningPlayerRef->UpdateLifeUI(AbilitySystemComp->GetNumericAttribute(AttributeSerBaseComp->GetHealthAttribute()),
	//	AbilitySystemComp->GetNumericAttribute(AttributeSerBaseComp->GetMaxHealthAttribute()));

	//	OwningPlayerRef->UpdateManaUI(AbilitySystemComp->GetNumericAttribute(AttributeSerBaseComp->GetManaAttribute()),
	//AbilitySystemComp->GetNumericAttribute(AttributeSerBaseComp->GetMaxManaAttribute()));


	//	OwningPlayerRef->UpdateStats(StatusType::ST_BaseStrength , AbilitySystemComp->GetNumericAttribute(AttributeSerBaseComp->GetBaseStrengthAttribute()));
	}
}


void ATx_Base_Character::TryToAttackTarget() 
{
	if( HasAuthority() && IsValid(CurrentTargetCharacter) )
	{
		
		const float DistanceToTarget = FVector::Dist(GetActorLocation(),CurrentTargetCharacter->GetActorLocation());
		
		if( DistanceToTarget <= 350.f )
		{
			
			if(AbilitySystemComp->TryActivateAbilityByClass(AbilityAttackRef))
			{
				
				CurrentCharacterState = CharacterState::Cs_Attacking;
				
				const FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),CurrentTargetCharacter->GetActorLocation());

				SetActorRotation(PlayerRot);

				GetWorld()->GetTimerManager().ClearTimer(MeleeAttackHandle);
			}
			else
			{
				GetWorld()->GetTimerManager().ClearTimer(MeleeAttackHandle);
			}
			
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(MeleeAttackHandle);
	}
	
}


// Called every frame
void ATx_Base_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void ATx_Base_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATx_Base_Character::GetDistanceToTargetCharacter() const
{
	if(IsValid(CurrentTargetCharacter))
	{
		return FVector::Dist2D(GetActorLocation(),CurrentTargetCharacter->GetActorLocation());
	}

	return -1.0f;
	
}

void ATx_Base_Character::SetCurrentCharacterState(CharacterState NewState)
{
	if(CurrentCharacterState==NewState) return;
	
	 CurrentCharacterState = NewState;
	if(OwningPlayerRef)
	{
		

	 switch (NewState)
	 {
	 case CharacterState::Cs_Idle:
	 	OwningPlayerRef->SetCtrControllerMode(ControllerType::Ct_Normal);
	 	break;
	 case CharacterState::Cs_MovingToLocation:
	 	OwningPlayerRef->SetCtrControllerMode(ControllerType::Ct_Normal);
	 	break;
	 case CharacterState::Cs_MovingToTarget:
	 	OwningPlayerRef->SetCtrControllerMode(ControllerType::Ct_Normal);
	 	break;
	 case CharacterState::Cs_Attacking:
	 	OwningPlayerRef->SetCtrControllerMode(ControllerType::Ct_Normal);
	 	break;
	 case CharacterState::Cs_Stunned:
	 	OwningPlayerRef->SetCtrControllerMode(ControllerType::Ct_DisableMovement);
	 	break;
	 case CharacterState::Cs_Dead: break;
	 case CharacterState::Cs_Channeling:
	 	OwningPlayerRef->SetCtrControllerMode(ControllerType::Ct_DisableMovement);
	 	break;
	 case CharacterState::Cs_Targeting:
	 	OwningPlayerRef->SetCtrControllerMode(ControllerType::Ct_Targeting);
	 	break;
	 default: ;
	 }
	}
	
}

void ATx_Base_Character::ServerTraceToObjective(FVector ClickPOsition)
{
	DrawDebugSphere(GetWorld(),ClickPOsition,50.f,16,FColor::Red,true,10.f);
	
	BP_SendEvent(ClickPOsition);
}

void ATx_Base_Character::OnRep_CharacterState(CharacterState LastState)
{

	///Change late
	if(CurrentCharacterState==CharacterState::Cs_MovingToTarget)
	{
		if(IsValid(CurrentTargetCharacter))
		{
	
		}
	}
	

}

void ATx_Base_Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AcquireAbility(AbilityAttackRef);
	AbilitySystemComp->InitAbilityActorInfo(this, this); 
}



void ATx_Base_Character::AcquireAbility(TSubclassOf<UGameplayAbility> AbilityToAcquire)
{

	if(IsValid(AbilitySystemComp))
	{
		if(HasAuthority() && AbilityToAcquire)
		{
			FGameplayAbilitySpecDef SpecDef = FGameplayAbilitySpecDef();
			SpecDef.Ability = AbilityToAcquire;
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(SpecDef,1);
			AbilitySystemComp->GiveAbility(AbilitySpec);
			
		}
		AbilitySystemComp->InitAbilityActorInfo(this,this);
	}
}


void ATx_Base_Character::OnRep_CurrentTargetCharacter(ATx_Base_Character* LastTarget)
{
	if(IsValid(CurrentTargetCharacter))
	{
		CheckDistanceToAttack();
	}
}

void ATx_Base_Character::OnHealthChange(const FOnAttributeChangeData& Data)
{
	const float CurrentMaxHealth = AbilitySystemComp->GetNumericAttribute(UBaseAttributeSetBase::GetMaxHealthAttribute());
	const float CurrentRegent = AbilitySystemComp->GetNumericAttribute(UBaseAttributeSetBase::GetHealthRegenAttribute());
	if(IsValid(OwningPlayerRef) && HasAuthority())
	{
		OwningPlayerRef->UpdateLifeUI(Data.NewValue,CurrentMaxHealth,CurrentRegent);
	}

	if(IsValid(OverHeadLifeBarRef))
	{
		OverHeadLifeBarRef->SetHealthPercentage(Data.NewValue/CurrentMaxHealth);
	}
	BP_OnHealthChange(Data.NewValue/CurrentMaxHealth);
	
}

void ATx_Base_Character::OnMaxHealthChange(const FOnAttributeChangeData& Data)
{
	BP_OnMaxHealthChange(Data.NewValue,Data.OldValue);
}

void ATx_Base_Character::OnManaChange(const FOnAttributeChangeData& Data)
{
	const float CurrentMaxMana = AbilitySystemComp->GetNumericAttribute(UBaseAttributeSetBase::GetMaxManaAttribute());
	const float CurrentRegent = AbilitySystemComp->GetNumericAttribute(UBaseAttributeSetBase::GetManaRegenAttribute());	
	if(IsValid(OwningPlayerRef) && HasAuthority())
	{
		OwningPlayerRef->UpdateManaUI(Data.NewValue,CurrentMaxMana,CurrentRegent);
	}
}

void ATx_Base_Character::OnMaxManahChange(const FOnAttributeChangeData& Data)
{
}

void ATx_Base_Character::OnStrChange(const FOnAttributeChangeData& Data)
{
	if(IsValid(OwningPlayerRef) && HasAuthority())
	{
		OwningPlayerRef->UpdateStats(StatusType::ST_BaseStrength ,Data.NewValue);
		//OwningPlayerRef->GetPlayerUI()->UpdateStatsUI(StatusType::ST_BaseStrength ,Data.NewValue);
	}
}

void ATx_Base_Character::OnAgiChange(const FOnAttributeChangeData& Data)
{
	if(IsValid(OwningPlayerRef) && IsValid(OwningPlayerRef->GetPlayerUI()))
	{
		OwningPlayerRef->GetPlayerUI()->UpdateStatsUI(StatusType::ST_BaseAgility ,Data.NewValue);
	}
}

void ATx_Base_Character::OnIntChange(const FOnAttributeChangeData& Data)
{
	if(IsValid(OwningPlayerRef) && IsValid(OwningPlayerRef->GetPlayerUI()))
	{
		OwningPlayerRef->GetPlayerUI()->UpdateStatsUI(StatusType::ST_BaseIntelligence ,Data.NewValue);
	}
}

void ATx_Base_Character::OnBonusStrChange(const FOnAttributeChangeData& Data)
{
	if(IsValid(OwningPlayerRef) && IsValid(OwningPlayerRef->GetPlayerUI()))
	{
		OwningPlayerRef->GetPlayerUI()->UpdateStatsUI(StatusType::ST_BonusStrength ,Data.NewValue);
	}
}

void ATx_Base_Character::OnBonusAgiChange(const FOnAttributeChangeData& Data)
{
	if(IsValid(OwningPlayerRef) && IsValid(OwningPlayerRef->GetPlayerUI()))
	{
		OwningPlayerRef->GetPlayerUI()->UpdateStatsUI(StatusType::ST_BonusAgility ,Data.NewValue);
	}
}

void ATx_Base_Character::OnBonusIntChange(const FOnAttributeChangeData& Data)
{
	if(IsValid(OwningPlayerRef) && IsValid(OwningPlayerRef->GetPlayerUI()))
	{
		OwningPlayerRef->GetPlayerUI()->UpdateStatsUI(StatusType::ST_BonusIntelligence ,Data.NewValue);
	}
}


void ATx_Base_Character::OnMovementSpeedChange(const FOnAttributeChangeData& Data)
{
	const float CurrentMaxHealth = AbilitySystemComp->GetNumericAttribute(UBaseAttributeSetBase::GetMovementSpeedAttribute());
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			FString::Printf(TEXT("World delta for current frame equals %f"), CurrentMaxHealth));
    if(IsValid(GetCharacterMovement()))
	{
    	GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
	}
}



void ATx_Base_Character::OnTargetLocationConfirm(FVector& TargetLocation)
{
	OnTargetConfirmLocationDelegate.Broadcast(TargetLocation);
}


void ATx_Base_Character::SetOwningPlayerBaseRef(ATx_PlayerCamera* BaseCharacterOwner)
{
	 OwningPlayerRef = BaseCharacterOwner;
}

void ATx_Base_Character::TryUsingAbility(int32 SlotIndex)
{
	if(AbilitySlots.Contains(SlotIndex))
	{
		AbilitySystemComp->TryActivateAbilityByClass(AbilitySlots[SlotIndex]);
	}
}

TSubclassOf<UGameplayAbility> ATx_Base_Character::GetAbilitiyInSlot(int32 SlotIndex) const
{
	if(AbilitySlots.Contains(SlotIndex))
	{
		return AbilitySlots[SlotIndex];
	}
	return nullptr;
}

void ATx_Base_Character::SetUnderCircleMaterialColor(FColor NewColor) 
{
	if(IsValid(CircleMaterialIntance))
	{
		CircleMaterialIntance->SetVectorParameterValue("Color",NewColor);
	}
	else
	{
		
		if(IsValid(UnderCircleMesh))
		{
			CircleMaterialIntance = UnderCircleMesh->CreateDynamicMaterialInstance(0,UnderCircleMesh->GetMaterial(0));

			UnderCircleMesh->SetMaterial(0,CircleMaterialIntance);
			
			CircleMaterialIntance->SetVectorParameterValue("Color",NewColor);
		}
	}

		
}

void ATx_Base_Character::InitStartingGamePlayEffects() const
{
	if(IsValid(AbilitySystemComp))
	{
		for (const auto& NewGameEffect : EffectToApplyOnBegin)
		{
			FGameplayEffectContextHandle newHandeler;
			AbilitySystemComp->BP_ApplyGameplayEffectToSelf(NewGameEffect,0.0f,newHandeler);
		}
		
	}
}

void ATx_Base_Character::SetCharacterCollision(ECollisionEnabled::Type NewType)
{
	
	if(NewType != GetCapsuleComponent()->GetCollisionEnabled() && HasAuthority())
	{
		GetCapsuleComponent()->SetCollisionEnabled(NewType);
		SetCharacterCollisionClient(NewType);
	}

}

void ATx_Base_Character::SetCharacterCollisionClient_Implementation(ECollisionEnabled::Type NewType)
{
	if(NewType != GetCapsuleComponent()->GetCollisionEnabled())
	{
		GetCapsuleComponent()->SetCollisionEnabled(NewType);
	}
}





