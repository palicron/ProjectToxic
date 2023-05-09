// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilitys/Stats/BaseAttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "Net/UnrealNetwork.h"

UBaseAttributeSetBase::UBaseAttributeSetBase()
{
	Health.SetCurrentValue(MaxHealth.GetBaseValue());
}


void UBaseAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSetBase, Health, COND_None, REPNOTIFY_Always);
}


void UBaseAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, Health, OldHealth);
}

void UBaseAttributeSetBase::OnRep_CurrentLevel(const FGameplayAttributeData& OldCurrentLevel)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, CurrentLevel, OldCurrentLevel);
}

void UBaseAttributeSetBase::OnRep_BaseHealth(const FGameplayAttributeData& OldBaseHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, BaseHealth, OldBaseHealth);
	
}

void UBaseAttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, MaxHealth, OldMaxHealth);
}

void UBaseAttributeSetBase::OnRep_BaseStrength(const FGameplayAttributeData& OldBaseStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, BaseStrength, OldBaseStrength);
	
}

void UBaseAttributeSetBase::OnRep_BonusStrength(const FGameplayAttributeData& OldBonusStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, BonusStrength, OldBonusStrength);

}

void UBaseAttributeSetBase::OnRep_StrengthGain(const FGameplayAttributeData& OldStrengthGain)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, StrengthGain, OldStrengthGain);
	
}


void UBaseAttributeSetBase::OnRep_StrengthMultiplier(const FGameplayAttributeData& OldStrengthMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, StrengthMultiplier, OldStrengthMultiplier);
	
}




void UBaseAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if(Data.EvaluatedData.Attribute.GetUProperty() ==
		FindFieldChecked<FProperty>(UBaseAttributeSetBase::StaticClass(),GET_MEMBER_NAME_CHECKED(UBaseAttributeSetBase,Health)))
	{
		UE_LOG(LogTemp,Warning,TEXT("healt %f"),MaxHealth.GetCurrentValue());
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(),0.f,MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(),0.f,MaxHealth.GetCurrentValue()));
		UE_LOG(LogTemp,Warning,TEXT("DAmage take healt %f"),Health.GetCurrentValue());
		
	}
}

