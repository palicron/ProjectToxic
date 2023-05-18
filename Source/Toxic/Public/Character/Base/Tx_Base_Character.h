// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Toxic/PlayerDefinitions.h"
#include "GameplayEffectTypes.h"
#include "AttributeSet.h"
#include "Tx_Base_Character.generated.h"


class UWidgetComponent;
class UGameplayAbility_Base;
class UBaseAttributeSetBase;
class ATx_Base_AICharacterCtr;
class ATx_PlayerCamera;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetConfirLocation,FVector&, NewLocation);
UCLASS()
class TOXIC_API ATx_Base_Character : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATx_Base_Character();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Team ID")
	uint8 TeamId = 255;

	UFUNCTION(BlueprintCallable)
	void CheckDistanceToAttack();

	UFUNCTION(BlueprintCallable)
	void StopAllActionByPlayer();

	UFUNCTION(BlueprintCallable)
	void ConfirmTargetAbility();
	
	UPROPERTY(ReplicatedUsing = OnRep_OwningPlayerRef  , VisibleAnywhere,BlueprintReadWrite)
	ATx_PlayerCamera* OwningPlayerRef;

	UFUNCTION()
	void OnRep_OwningPlayerRef();
	
	UPROPERTY(Replicated, EditAnywhere,BlueprintReadWrite)
	FVector_NetQuantize LastClickTarget;

	UPROPERTY(BlueprintAssignable)
	FOnTargetConfirLocation OnTargetConfirmLocationDelegate;
	
	void ServerTraceToObjective(FVector ClickPOsition);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_SendEvent(FVector vector);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bUsingToggleAbility =false;
	
protected:
	
	UPROPERTY( ReplicatedUsing = OnRep_CharacterState, EditAnywhere,BlueprintReadWrite,Category="Player State")
	CharacterState CurrentCharacterState;
	
	UFUNCTION()
	void OnRep_CharacterState(CharacterState LastState);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FTimerHandle MeleeAttackHandle;
	
	UFUNCTION(BlueprintCallable)
	void TryToAttackTarget();
	


	UPROPERTY( ReplicatedUsing= OnRep_CurrentTargetCharacter,VisibleAnywhere,BlueprintReadWrite)
	ATx_Base_Character* CurrentTargetCharacter = nullptr;

	UFUNCTION()
	void OnRep_CurrentTargetCharacter(ATx_Base_Character* LastTarget);
	
	UPROPERTY(BlueprintReadOnly)
	ATx_Base_AICharacterCtr* AIControllerReference;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Game Ability")
	TMap<int32,TSubclassOf<UGameplayAbility>> AbilitySlots;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Game Ability")
	TSubclassOf<UGameplayAbility> AbilityAttackRef;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Game Ability")
	TSubclassOf<UGameplayAbility> AbilityHookRef;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Game Ability")
	TSubclassOf<UGameplayAbility> AbilitySlot2Ref;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Character Abilitys")
	UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Character Abilitys")
	UBaseAttributeSetBase* AttributeSerBaseComp;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ActiveBasicAttack();
	
	virtual void PossessedBy(AController* NewController) override;


	virtual void OnHealthChange(const FOnAttributeChangeData &  Data);

	
	virtual void OnMaxHealthChange(const FOnAttributeChangeData & Data);

	
	virtual void OnManaChange(const FOnAttributeChangeData &  Data);

	
	virtual void OnMaxManahChange(const FOnAttributeChangeData & Data);

	virtual void OnStrChange(const FOnAttributeChangeData & Data);

	virtual void OnAgiChange(const FOnAttributeChangeData & Data);

	virtual void OnIntChange(const FOnAttributeChangeData & Data);

	virtual void OnBonusStrChange(const FOnAttributeChangeData & Data);

	virtual void OnBonusAgiChange(const FOnAttributeChangeData & Data);

	virtual void OnBonusIntChange(const FOnAttributeChangeData & Data);

	virtual void OnMovementSpeedChange(const FOnAttributeChangeData & Data);


	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnHealthChange(float NewValue);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_SpeedChange();
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnMaxHealthChange(float NewValue,float OldValue);

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animations")
	UAnimMontage* AttackMontage;
	
	UFUNCTION(BlueprintCallable)
	void SetOwningPlayerBaseRef(ATx_PlayerCamera* BaseCharacterOwner);
	
	UFUNCTION(BlueprintCallable)
	void TryUsingAbility(int32 SlotIndex);
	
	UFUNCTION(BlueprintCallable,Category="Character Base")
	void AcquireAbility(TSubclassOf<UGameplayAbility> AbilityToAcquire);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	float GetDistanceToTargetCharacter() const ;
	
	////Targeting funtions////
	UFUNCTION(BlueprintCallable)
	void OnTargetLocationConfirm(FVector& TargetLocation);
	
	/////UI Changes////
	UFUNCTION(BlueprintCallable)
	TSubclassOf<UGameplayAbility> GetAbilitiyInSlot(int32 SlotIndex) const;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMaterialInstanceDynamic* CircleMaterialIntance;
	
	UFUNCTION(BlueprintCallable)
	void SetUnderCircleMaterialColor(FColor NewColor);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* UnderCircleMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UWidgetComponent* OverHeadBarWidget;

	UPROPERTY()
	class UTx_OverHeadBar* OverHeadLifeBarRef;


	UPROPERTY(BlueprintReadWrite)
	FTimerHandle InitialDelayHandle;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TSubclassOf<class UGameplayEffect>>  EffectToApplyOnBegin;

	UFUNCTION(BlueprintCallable)
	void InitStartingGamePlayEffects()const;
	
	/////// Setter And Getters///////////
	///
	///


	UFUNCTION(BlueprintCallable)
	void SetCharacterCollision(ECollisionEnabled::Type NewType );

	UFUNCTION(Client,Reliable)
	void SetCharacterCollisionClient(ECollisionEnabled::Type NewType );
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetAiController( ATx_Base_AICharacterCtr* NewCtr) {AIControllerReference = NewCtr; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ATx_Base_AICharacterCtr* GetAiController( ) { return AIControllerReference ; }

	UFUNCTION(BlueprintCallable)
	void SetCurrentCharacterState(CharacterState NewState);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ATx_Base_Character* GetCurrentActorTarget() const {return CurrentTargetCharacter;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetCurrentActorTarget(ATx_Base_Character* NewTarget) { CurrentTargetCharacter = NewTarget;}
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE CharacterState GetCurrentCharacterState() const{ return CurrentCharacterState; }


	UFUNCTION(BlueprintCallable)
	FORCEINLINE UAbilitySystemComponent*  GetAbilitySystemComp() const {return AbilitySystemComp;} ;
};
