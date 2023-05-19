// Fill out your copyright notice in the Description page of Project Settings.


#include "Calculators/Tx_Regen_ManaSum_calculator.h"

#include "Abilitys/Stats/BaseAttributeSetBase.h"

UTx_Regen_ManaSum_calculator::UTx_Regen_ManaSum_calculator()
{
	CurrentManaRegen.AttributeToCapture = UBaseAttributeSetBase::GetManaRegenAttribute();
	CurrentManaRegen.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	CurrentManaRegen.bSnapshot = false;
	
	CurrentMana.AttributeToCapture = UBaseAttributeSetBase::GetManaAttribute();
	CurrentMana.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	CurrentMana.bSnapshot = false;

	CurrentMaxMana.AttributeToCapture = UBaseAttributeSetBase::GetMaxManaAttribute();
	CurrentMaxMana.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	CurrentMaxMana.bSnapshot = false;


	RelevantAttributesToCapture.Add(CurrentManaRegen);
	RelevantAttributesToCapture.Add(CurrentMana);
	RelevantAttributesToCapture.Add(CurrentMaxMana);
}


float UTx_Regen_ManaSum_calculator::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;


	float ManaRegenTemp = 0.f;
	GetCapturedAttributeMagnitude(CurrentManaRegen,Spec,EvaluationParameters,ManaRegenTemp);

	float CurrentManaTemp = 0.f;
	GetCapturedAttributeMagnitude(CurrentMana,Spec,EvaluationParameters,CurrentManaTemp);
	
	float CurrentMaxManaTemp = 0.f;
	GetCapturedAttributeMagnitude(CurrentMaxMana,Spec,EvaluationParameters,CurrentMaxManaTemp);


	if(CurrentManaTemp >= CurrentMaxManaTemp )
	{
		return 0.0;
	}

	if(CurrentManaTemp + ManaRegenTemp < CurrentMaxManaTemp)
	{
		return ManaRegenTemp;
	}

	return CurrentMaxManaTemp - CurrentManaTemp;
}
