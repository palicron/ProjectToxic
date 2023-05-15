// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "Tx_ManaCalculation.generated.h"

/**
 * 
 */
UCLASS()
class TOXIC_API UTx_ManaCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
private:
	UTx_ManaCalculation();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
public:

	FGameplayEffectAttributeCaptureDefinition IntGain;

	FGameplayEffectAttributeCaptureDefinition Level;

	FGameplayEffectAttributeCaptureDefinition BaseInt;

	FGameplayEffectAttributeCaptureDefinition BonusInt;

	FGameplayEffectAttributeCaptureDefinition BaseMana;

	FGameplayEffectAttributeCaptureDefinition IntMulti;


};
