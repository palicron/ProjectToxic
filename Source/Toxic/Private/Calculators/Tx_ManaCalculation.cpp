// Fill out your copyright notice in the Description page of Project Settings.


#include "Calculators/Tx_ManaCalculation.h"

#include "Abilitys/Stats/BaseAttributeSetBase.h"

UTx_ManaCalculation::UTx_ManaCalculation()
{
	IntGain.AttributeToCapture = UBaseAttributeSetBase::GetIntelligenceGainAttribute();
	IntGain.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	IntGain.bSnapshot = false;

	Level.AttributeToCapture = UBaseAttributeSetBase::GetCurrentLevelAttribute();
	Level.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	Level.bSnapshot = false;
	
	BaseInt.AttributeToCapture = UBaseAttributeSetBase::GetBaseIntelligenceAttribute();
	BaseInt.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BaseInt.bSnapshot = false;

	BonusInt.AttributeToCapture = UBaseAttributeSetBase::GetBonusIntelligenceAttribute();
	BonusInt.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BonusInt.bSnapshot = false;

	BaseMana.AttributeToCapture = UBaseAttributeSetBase::GetBaseManaAttribute();
	BaseMana.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BaseMana.bSnapshot = false;
	

	IntMulti.AttributeToCapture = UBaseAttributeSetBase::GetIntelligenceMultiplierAttribute();
	IntMulti.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	IntMulti.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntGain);
	RelevantAttributesToCapture.Add(Level);
	RelevantAttributesToCapture.Add(BaseInt);
	RelevantAttributesToCapture.Add(BonusInt);
	RelevantAttributesToCapture.Add(BaseMana);
	RelevantAttributesToCapture.Add(IntMulti);
}

float UTx_ManaCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	float IntGainTemp = 0.f;
	GetCapturedAttributeMagnitude(IntGain,Spec,EvaluationParameters,IntGainTemp);

	float LevelTemp = 0.f;
	GetCapturedAttributeMagnitude(Level,Spec,EvaluationParameters,LevelTemp);

	float BaseIntTemp = 0.f;
	GetCapturedAttributeMagnitude(BaseInt,Spec,EvaluationParameters,BaseIntTemp);
	
	float BonusIntTemp = 0.f;
	GetCapturedAttributeMagnitude(BonusInt,Spec,EvaluationParameters,BonusIntTemp);

	float BaseManaTemp = 0.f;
	GetCapturedAttributeMagnitude(BaseMana,Spec,EvaluationParameters,BaseManaTemp);

	float MultiTemp = 0.f;
	GetCapturedAttributeMagnitude(IntMulti,Spec,EvaluationParameters,MultiTemp);

	//(Intelligence Growth × (Current Level - 1) ➜ rounded down) + Base Intelligence +
		//Bonus Intelligence × 12 = Mana from Intelligence + 75 Base Mana = Total Mana
	
	const float FinalMana = FMath::Floor(IntGainTemp * (LevelTemp + 1)) + ((BaseIntTemp +
																	BonusIntTemp) * MultiTemp) + BaseManaTemp;
	return FinalMana;
}
