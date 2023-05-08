// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilitys/GameplayAbility_Base.h"
#include "MyGameplayAbility_Toggle.generated.h"

/**
 * 
 */
UCLASS()
class TOXIC_API UMyGameplayAbility_Toggle : public UGameplayAbility_Base
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Toggle Ability")
	bool bIsAbilityToggle = false;

	UFUNCTION(BlueprintCallable)
	void OnToggleAbility();
	
};
