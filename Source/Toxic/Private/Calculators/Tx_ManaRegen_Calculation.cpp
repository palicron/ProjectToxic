// Fill out your copyright notice in the Description page of Project Settings.


#include "Calculators/Tx_ManaRegen_Calculation.h"

#include "Abilitys/Stats/BaseAttributeSetBase.h"

UTx_ManaRegen_Calculation::UTx_ManaRegen_Calculation()
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

	BaseManaRegen.AttributeToCapture = UBaseAttributeSetBase::GetBaseManaRegenAttribute();
	BaseManaRegen.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BaseManaRegen.bSnapshot = false;
	

	BonusManaRegen.AttributeToCapture = UBaseAttributeSetBase::GetBonusManaRegenAttribute();
	BonusManaRegen.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BonusManaRegen.bSnapshot = false;

	RegainPerInt.AttributeToCapture = UBaseAttributeSetBase::GetRegainPerIntAttribute();
	RegainPerInt.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	RegainPerInt.bSnapshot = false;


	RelevantAttributesToCapture.Add(IntGain);
	RelevantAttributesToCapture.Add(Level);
	RelevantAttributesToCapture.Add(BaseInt);
	RelevantAttributesToCapture.Add(BonusInt);
	RelevantAttributesToCapture.Add(BaseManaRegen);
	RelevantAttributesToCapture.Add(BonusManaRegen);
	RelevantAttributesToCapture.Add(RegainPerInt);
}

float UTx_ManaRegen_Calculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float TempIntGain = 0.0f;
	GetCapturedAttributeMagnitude(IntGain,Spec,EvaluationParameters,TempIntGain);

	float LevelTemp = 0.f;
	GetCapturedAttributeMagnitude(Level,Spec,EvaluationParameters,LevelTemp);

	float TempBaseInt = 0.0f;
	GetCapturedAttributeMagnitude(BaseInt,Spec,EvaluationParameters,TempBaseInt);

	float TempBonusInt = 0.0f;
	GetCapturedAttributeMagnitude(BonusInt,Spec,EvaluationParameters,TempBonusInt);

	float TempBaseManaRegen = 0.0f;
	GetCapturedAttributeMagnitude(BaseManaRegen,Spec,EvaluationParameters,TempBaseManaRegen);

	float TempBonusManaRegen = 0.0f;
	GetCapturedAttributeMagnitude(BonusManaRegen,Spec,EvaluationParameters,TempBonusManaRegen);
	
	float TempRegainPerInt = 0.0f;
	GetCapturedAttributeMagnitude(RegainPerInt,Spec,EvaluationParameters,TempRegainPerInt);

	const float TotalInt = (TempBaseInt + TempBonusInt) + ((LevelTemp + 1 )*TempIntGain);

	return (TotalInt * TempRegainPerInt) + TempBaseManaRegen + TempBonusManaRegen;
}
