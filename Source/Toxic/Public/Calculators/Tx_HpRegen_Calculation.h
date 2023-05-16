// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "Tx_HpRegen_Calculation.generated.h"

/**
 * 
 */
UCLASS()
class TOXIC_API UTx_HpRegen_Calculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

private:

	UTx_HpRegen_Calculation();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
public:
	
	FGameplayEffectAttributeCaptureDefinition StrgGain;

	FGameplayEffectAttributeCaptureDefinition Level;

	FGameplayEffectAttributeCaptureDefinition BaseStrg;

	FGameplayEffectAttributeCaptureDefinition BonusStrg;

	FGameplayEffectAttributeCaptureDefinition BaseHealthRegen; 

	FGameplayEffectAttributeCaptureDefinition BonusHealthRegen;

	FGameplayEffectAttributeCaptureDefinition RegainPerStrg;
};
