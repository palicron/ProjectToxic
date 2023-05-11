// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toxic/PlayerDefinitions.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Base.generated.h"

class ATx_Base_AICharacterCtr;
class ATx_Base_Character;
/**
 * 
 */
UCLASS()
class TOXIC_API UGameplayAbility_Base : public UGameplayAbility
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	ATx_Base_Character* OwningCharacterRef;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	ATx_Base_AICharacterCtr* OwningCharacterCtrRef;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Target Config")
	AbilityType AbilityCurrentType;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Target Config")
	EAbilityCostType Resource = EAbilityCostType::Mana ;
	
public:
	
	UFUNCTION(BlueprintCallable,Category="Getter and Setters")
	ATx_Base_Character* GetOwningBaseCharacter();

	UFUNCTION(BlueprintCallable,Category="Getter and Setters")
	ATx_Base_AICharacterCtr* GetOwningBaseCharacterCtr();
	
	UFUNCTION(BlueprintCallable)
	void ChangeOwningCharacterState(CharacterState NewState);

	UFUNCTION(BlueprintCallable)
	FGamePlayAbilityInfo GetAbilityInfo() const ;

	UFUNCTION(BlueprintCallable)
	bool CanCastAbility() const;

	FORCEINLINE bool IsAbilityOfType(const AbilityType NewType) const {return AbilityCurrentType == NewType; }

	FORCEINLINE AbilityType GetCurrentType() const { return AbilityCurrentType;}

	FORCEINLINE void SetCurrentType(const AbilityType NewType) {  AbilityCurrentType = NewType;}
};
