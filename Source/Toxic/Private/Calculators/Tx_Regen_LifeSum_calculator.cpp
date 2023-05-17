// Fill out your copyright notice in the Description page of Project Settings.


#include "Calculators/Tx_Regen_LifeSum_calculator.h"

#include "Abilitys/Stats/BaseAttributeSetBase.h"

UTx_Regen_LifeSum_calculator::UTx_Regen_LifeSum_calculator()
{

	CurrentHealRegen.AttributeToCapture = UBaseAttributeSetBase::GetHealthRegenAttribute();
	CurrentHealRegen.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	CurrentHealRegen.bSnapshot = false;
	
	CurrentHealth.AttributeToCapture = UBaseAttributeSetBase::GetHealthAttribute();
	CurrentHealth.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	CurrentHealth.bSnapshot = false;

	CurrentMaxHealth.AttributeToCapture = UBaseAttributeSetBase::GetMaxHealthAttribute();
	CurrentMaxHealth.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	CurrentMaxHealth.bSnapshot = false;


	RelevantAttributesToCapture.Add(CurrentHealRegen);
	RelevantAttributesToCapture.Add(CurrentHealth);
	RelevantAttributesToCapture.Add(CurrentMaxHealth);
}

float UTx_Regen_LifeSum_calculator::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float HealthRegenTemp = 0.f;
	GetCapturedAttributeMagnitude(CurrentHealRegen,Spec,EvaluationParameters,HealthRegenTemp);

	float CurrentHealthTemp = 0.f;
	GetCapturedAttributeMagnitude(CurrentHealth,Spec,EvaluationParameters,CurrentHealthTemp);
	
	float CurrentMaxHealthTemp = 0.f;
	GetCapturedAttributeMagnitude(CurrentMaxHealth,Spec,EvaluationParameters,CurrentMaxHealthTemp);


	if(CurrentHealthTemp >= CurrentMaxHealthTemp )
	{
		return 0.0;
	}

	if(CurrentHealthTemp + HealthRegenTemp < CurrentMaxHealthTemp)
	{
		return HealthRegenTemp;
	}

	return CurrentMaxHealthTemp - CurrentHealthTemp;
}
