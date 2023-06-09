// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "Tx_HpCalculation.generated.h"

/**
 * 
 */
UCLASS()
class TOXIC_API UTx_HpCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

protected:


	UTx_HpCalculation();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	

	FGameplayEffectAttributeCaptureDefinition StrgGain;

	FGameplayEffectAttributeCaptureDefinition Level;

	FGameplayEffectAttributeCaptureDefinition BaseStrg;

	FGameplayEffectAttributeCaptureDefinition BonusStrg;

	FGameplayEffectAttributeCaptureDefinition BaseHealth;

	FGameplayEffectAttributeCaptureDefinition StrgMulti;
};
