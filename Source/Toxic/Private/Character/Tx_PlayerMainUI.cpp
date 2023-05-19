// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Tx_PlayerMainUI.h"

#include "AbilitySystemComponent.h"
#include "Character/Tx_PlayerPortrait_Stats.h"
#include "Character/Base/Tx_Base_Character.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Player/Tx_PlayerCamera.h"
#include "Player/Tx_PlayerCtr.h"



void UTx_PlayerMainUI::SetNewHealth(float NewHealth, float MaxHealth)
{
	if(IsValid(HealthBar) && IsValid(CurrentHealthText))
	{
		CurrentHealthText->SetText(FText::FromString(FString::FromInt(FMath::Floor(NewHealth))));
		HealthBar->SetPercent(NewHealth/MaxHealth);
	}
}

void UTx_PlayerMainUI::SetMaxNewHealth(float MaxHealth)
{
	if(IsValid(MaxHealthText))
	{
		MaxHealthText->SetText(FText::FromString(FString::SanitizeFloat(MaxHealth,0)));
	}
}

void UTx_PlayerMainUI::SetHealthRegen(float Regen)
{
	if(IsValid(LifeRegen))
	{
		FString RegenString = FString::SanitizeFloat(Regen,1);
		RegenString = "+"+RegenString;
		LifeRegen->SetText(FText::FromString(RegenString));
	}
}

void UTx_PlayerMainUI::SetManaHealth(float NewMana, float MaxMana)
{
	if(IsValid(ManaBar) && IsValid(CurrentManaText))
	{
		
		CurrentManaText->SetText(FText::FromString(FString::FromInt(FMath::Floor(NewMana))));
		ManaBar->SetPercent( NewMana/MaxMana);
	}
}

void UTx_PlayerMainUI::SetMaxNewMana(float MaxMana)
{
	if(IsValid(MaxManaText))
	{
		MaxManaText->SetText(FText::FromString(FString::SanitizeFloat(MaxMana,0)));
	}
}

void UTx_PlayerMainUI::SetManaRegen(float Regen)
{
	if(IsValid(ManaRegen))
	{
		FString RegenString = FString::SanitizeFloat(Regen,1);
		RegenString = "+"+RegenString;
		ManaRegen->SetText(FText::FromString(RegenString));
	}
}

void UTx_PlayerMainUI::UpdateStatsUI(StatusType NewStats,float NewValue) const
{

	if(!IsValid(StatAndPort)) return;
	
	switch (NewStats)
	{
	case StatusType::ST_BaseStrength:
		StatAndPort->SetBaseStrText(NewValue);
		break;
	case StatusType::ST_BonusStrength:
		StatAndPort->SetBonusStrText(NewValue);
		break;
	case StatusType::ST_BaseAgility:
		StatAndPort->SetBaseAgiText(NewValue);
		break;
	case StatusType::ST_BonusAgility:
		StatAndPort->SetBonusAgiText(NewValue);
		break;
	case StatusType::ST_BaseIntelligence:
		StatAndPort->SetBaseIntText(NewValue);
		break;
	case StatusType::ST_BonusIntelligence:
		StatAndPort->SetBonusIntText(NewValue);
		break;
	default: ;
	}
}
