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
	
public:
	
	UFUNCTION(BlueprintCallable,Category="Getter and Setters")
	ATx_Base_Character* GetOwningBaseCharacter();

	UFUNCTION(BlueprintCallable,Category="Getter and Setters")
	ATx_Base_AICharacterCtr* GetOwningBaseCharacterCtr();


	UFUNCTION(BlueprintCallable)
	void ChangeOwningCharacterState(CharacterState NewState);
};
