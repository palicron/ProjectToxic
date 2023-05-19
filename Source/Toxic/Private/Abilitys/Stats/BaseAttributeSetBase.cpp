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

void UBaseAttributeSetBase::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, Mana, OldMana);
}

void UBaseAttributeSetBase::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, MaxMana, OldMaxMana);
}

void UBaseAttributeSetBase::OnRep_BaseMana(const FGameplayAttributeData& OldBaseMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, BaseMana, OldBaseMana);
}

void UBaseAttributeSetBase::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, MovementSpeed, OldMovementSpeed);
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

void UBaseAttributeSetBase::OnRep_BaseIntelligence(const FGameplayAttributeData& OldBaseIntelligence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, BaseIntelligence, OldBaseIntelligence);
}

void UBaseAttributeSetBase::OnRep_BonusIntelligence(const FGameplayAttributeData& OldBonusIntelligence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, BonusIntelligence, OldBonusIntelligence);
}

void UBaseAttributeSetBase::OnRep_IntelligenceGain(const FGameplayAttributeData& OldIntelligenceGain)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, IntelligenceGain, OldIntelligenceGain);
}

void UBaseAttributeSetBase::OnRep_IntelligenceMultiplier(const FGameplayAttributeData& OldIntelligenceMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, IntelligenceMultiplier, OldIntelligenceMultiplier);
}

void UBaseAttributeSetBase::OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, HealthRegen, OldHealthRegen);
}

void UBaseAttributeSetBase::OnRep_BaseHealthRegen(const FGameplayAttributeData& OldBaseHealthRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, BaseHealthRegen, OldBaseHealthRegen);
}

void UBaseAttributeSetBase::OnRep_BonusHealthRegen(const FGameplayAttributeData& OldBonusHealthRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, BonusHealthRegen, OldBonusHealthRegen);
}

void UBaseAttributeSetBase::OnRep_RegainPerStrg(const FGameplayAttributeData& OldRegainPerStrg)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, RegainPerStrg, OldRegainPerStrg);
}

void UBaseAttributeSetBase::OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, ManaRegen, OldManaRegen);
}

void UBaseAttributeSetBase::OnRep_BaseManaRegen(const FGameplayAttributeData& OldBaseManaRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, BaseManaRegen, OldBaseManaRegen);
}

void UBaseAttributeSetBase::OnRep_BonusManaRegen(const FGameplayAttributeData& OldBonusManaRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, BonusManaRegen, OldBonusManaRegen);
}

void UBaseAttributeSetBase::OnRep_RegainPerInt(const FGameplayAttributeData& OldRegainPerInt)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, RegainPerInt, OldRegainPerInt);
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

