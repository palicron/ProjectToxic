// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Toxic/PlayerDefinitions.h"
#include "Tx_Base_Character.generated.h"

class UGameplayAbility_Base;
class UBaseAttributeSetBase;
class ATx_Base_AICharacterCtr;
class ATx_PlayerCamera;


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
	UPROPERTY(VisibleAnywhere)
	ATx_PlayerCamera* OwningPlayerRef;

	UPROPERTY(Replicated, EditAnywhere,BlueprintReadWrite)
	FVector_NetQuantize LastClickTarget;
	
	
	void ServerTraceToObjective(FVector ClickPOsition);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_SendEvent(FVector vector);

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
	TSubclassOf<UGameplayAbility> AbilityAttackRef;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Game Ability")
	TSubclassOf<UGameplayAbility> AbilityHookRef;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Character Abilitys")
	UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Character Abilitys")
	UBaseAttributeSetBase* AttributeSerBaseComp;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ActiveBasicAttack();
	
	virtual void PossessedBy(AController* NewController) override;

public:


	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetOwningPlayerBaseRef(ATx_PlayerCamera* BaseCharacterOwner) { OwningPlayerRef = BaseCharacterOwner;};
	
	UFUNCTION(BlueprintCallable)
	void TryHookAbility();
	
	UFUNCTION(BlueprintCallable,Category="Character Base")
	void AcquireAbility(TSubclassOf<UGameplayAbility> AbilityToAcquire);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	float GetDistanceToTargetCharacter() const ;



	
	/////// Setter And Getters///////////
	
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
};
