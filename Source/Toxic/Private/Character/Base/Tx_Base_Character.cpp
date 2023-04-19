// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Base/Tx_Base_Character.h"
#include "AbilitySystemComponent.h"
#include "Abilitys/Stats/BaseAttributeSetBase.h"
#include "Net/UnrealNetwork.h"
#include "Player/Tx_PlayerCamera.h"

// Sets default values
ATx_Base_Character::ATx_Base_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NetUpdateFrequency = 66.f;
	MinNetUpdateFrequency = 33.f;

	CurrentCharacterState = CharacterState::Cs_Idle;

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

	DOREPLIFETIME(ATx_Base_Character,CurrentCharacterState);
}




// Called when the game starts or when spawned
void ATx_Base_Character::BeginPlay()
{
	Super::BeginPlay();

	AcquireAbility(AbilityAttackRef);
	
}



// Called every frame
void ATx_Base_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bCheckForEnemyOnRange && IsValid(CurrentTargetCharacter))
	{
		const float DistanceToTarget = FVector::Dist(GetActorLocation(),CurrentTargetCharacter->GetActorLocation());
		if(DistanceToTarget<=100.f && CurrentCharacterState != CharacterState::Cs_Attacking )
		{
			
		}
	}

}

// Called to bind functionality to input
void ATx_Base_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATx_Base_Character::OnRep_CharacterState(CharacterState LastState)
{
	///Change late
	if(CurrentCharacterState==CharacterState::Cs_MovingToTarget)
	{
		if(IsValid(CurrentTargetCharacter))
		{
			bCheckForEnemyOnRange = true;
		}
	}
	

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

void ATx_Base_Character::AttackAction()
{
	
}

void ATx_Base_Character::OnRep_CurrentTargetCharacter(ATx_Base_Character* LastTarget)
{
}