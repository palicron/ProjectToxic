// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "Tx_Regen_ManaSum_calculator.generated.h"

/**
 * 
 */
UCLASS()
class TOXIC_API UTx_Regen_ManaSum_calculator : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

private:
	UTx_Regen_ManaSum_calculator();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
public:

	FGameplayEffectAttributeCaptureDefinition CurrentManaRegen;

	FGameplayEffectAttributeCaptureDefinition CurrentMana;
	
	FGameplayEffectAttributeCaptureDefinition CurrentMaxMana;
};
