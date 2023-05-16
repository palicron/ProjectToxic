// Fill out your copyright notice in the Description page of Project Settings.


#include "Calculators/Tx_HpRegen_Calculation.h"

#include "Abilitys/Stats/BaseAttributeSetBase.h"

UTx_HpRegen_Calculation::UTx_HpRegen_Calculation()
{

	StrgGain.AttributeToCapture = UBaseAttributeSetBase::GetStrengthGainAttribute();
	StrgGain.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	StrgGain.bSnapshot = false;

	Level.AttributeToCapture = UBaseAttributeSetBase::GetCurrentLevelAttribute();
	Level.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	Level.bSnapshot = false;


	BaseStrg.AttributeToCapture = UBaseAttributeSetBase::GetBaseStrengthAttribute();
	BaseStrg.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BaseStrg.bSnapshot = false;

	BonusStrg.AttributeToCapture = UBaseAttributeSetBase::GetBonusStrengthAttribute();
	BonusStrg.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BonusStrg.bSnapshot = false;

	BaseHealthRegen.AttributeToCapture = UBaseAttributeSetBase::GetBaseHealthRegenAttribute();
	BaseHealthRegen.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BaseHealthRegen.bSnapshot = false;
	

	BonusHealthRegen.AttributeToCapture = UBaseAttributeSetBase::GetBonusHealthRegenAttribute();
	BonusHealthRegen.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BonusHealthRegen.bSnapshot = false;

	RegainPerStrg.AttributeToCapture = UBaseAttributeSetBase::GetRegainPerStrgAttribute();
	RegainPerStrg.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	RegainPerStrg.bSnapshot = false;


	RelevantAttributesToCapture.Add(StrgGain);
	RelevantAttributesToCapture.Add(Level);
	RelevantAttributesToCapture.Add(BaseStrg);
	RelevantAttributesToCapture.Add(BonusStrg);
	RelevantAttributesToCapture.Add(BaseHealthRegen);
	RelevantAttributesToCapture.Add(BonusHealthRegen);
	RelevantAttributesToCapture.Add(RegainPerStrg);
}

float UTx_HpRegen_Calculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
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

	float BaseStrgtemp = 0.f;
	GetCapturedAttributeMagnitude(BaseStrg,Spec,EvaluationParameters,BaseStrgtemp);

	float BonusStrgtemp = 0.f;
	GetCapturedAttributeMagnitude(BonusStrg,Spec,EvaluationParameters,BonusStrgtemp);

	float BaseHealthRegentemp = 0.f;
	GetCapturedAttributeMagnitude(BaseHealthRegen,Spec,EvaluationParameters,BaseHealthRegentemp);

	float BonusHealthRegentemp = 0.f;
	GetCapturedAttributeMagnitude(BonusHealthRegen,Spec,EvaluationParameters,BonusHealthRegentemp);

	float RegainPerStrgtemp = 0.f;
	GetCapturedAttributeMagnitude(RegainPerStrg,Spec,EvaluationParameters,RegainPerStrgtemp);

	const float TotalStrg = (BaseStrgtemp + BonusStrgtemp) + ((LevelTemp + 1 )*StrgGainTemp);

	return (TotalStrg * RegainPerStrgtemp) + BaseHealthRegentemp + BonusHealthRegentemp;
}
