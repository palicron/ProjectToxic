// Fill out your copyright notice in the Description page of Project Settings.


#include "Calculators/Tx_HpCalculation.h"

#include "Abilitys/Stats/BaseAttributeSetBase.h"

UTx_HpCalculation::UTx_HpCalculation()
{
	StrgGain.AttributeToCapture = UBaseAttributeSetBase::GetStrengthGainAttribute();
	StrgGain.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	StrgGain.bSnapshot = false;

	Level.AttributeToCapture = UBaseAttributeSetBase::GetCurrentLevelAttribute();
	Level.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	Level.bSnapshot = false;

	Level.AttributeToCapture = UBaseAttributeSetBase::GetCurrentLevelAttribute();
	Level.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	Level.bSnapshot = false;

	BaseStrg.AttributeToCapture = UBaseAttributeSetBase::GetBaseStrengthAttribute();
	BaseStrg.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BaseStrg.bSnapshot = false;

	BonusStrg.AttributeToCapture = UBaseAttributeSetBase::GetBonusStrengthAttribute();
	BonusStrg.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BonusStrg.bSnapshot = false;

	BaseHealth.AttributeToCapture = UBaseAttributeSetBase::GetBaseHealthAttribute();
	BaseHealth.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BaseHealth.bSnapshot = false;
	

	StrgMulti.AttributeToCapture = UBaseAttributeSetBase::GetStrengthMultiplierAttribute();
	StrgMulti.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	StrgMulti.bSnapshot = false;

	RelevantAttributesToCapture.Add(StrgGain);
	RelevantAttributesToCapture.Add(Level);
	RelevantAttributesToCapture.Add(BaseStrg);
	RelevantAttributesToCapture.Add(BonusStrg);
	RelevantAttributesToCapture.Add(BaseHealth);
	RelevantAttributesToCapture.Add(StrgMulti);
}

float UTx_HpCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	float StrgGainTemp = 0.f;
	GetCapturedAttributeMagnitude(StrgGain,Spec,EvaluationParameters,StrgGainTemp);

	float LevelTemp = 0.f;
	GetCapturedAttributeMagnitude(Level,Spec,EvaluationParameters,LevelTemp);

	float BaseStrgTemp = 0.f;
	GetCapturedAttributeMagnitude(BaseStrg,Spec,EvaluationParameters,BaseStrgTemp);
	
	float BonusStrgTemp = 0.f;
	GetCapturedAttributeMagnitude(BonusStrg,Spec,EvaluationParameters,BonusStrgTemp);

	float BaseHealthTemp = 0.f;
	GetCapturedAttributeMagnitude(BaseHealth,Spec,EvaluationParameters,BaseHealthTemp);

	float MultiTemp = 0.f;
	GetCapturedAttributeMagnitude(StrgMulti,Spec,EvaluationParameters,MultiTemp);

	//(Strength Growth × (Current Level - 1) ➜ rounded down) + Base Strength + Bonus Strength
	//																	× 18 = HP from Strength + 200 Base HP = Total HP
	
	const float FinalHealth = FMath::Floor(StrgGainTemp*(LevelTemp + 1)) + (BaseStrgTemp +
																	(BonusStrgTemp * MultiTemp)) + BaseHealthTemp;

	
	return FinalHealth;
}
