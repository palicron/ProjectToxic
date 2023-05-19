// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Tx_PlayerPortrait_Stats.h"

#include "Components/TextBlock.h"

void UTx_PlayerPortrait_Stats::SetBaseStrText(float CurrentStr)
{
	if(IsValid(BaseStrText))
	{
		BaseStrText->SetText(FText::FromString(FString::FromInt(FMath::Floor(CurrentStr))));
	}
}

void UTx_PlayerPortrait_Stats::SetBaseAgiText(float CurrentAgi)
{
	if(IsValid(BaseAgiText))
	{
		BaseAgiText->SetText(FText::FromString(FString::FromInt(FMath::Floor(CurrentAgi))));
	}
}

void UTx_PlayerPortrait_Stats::SetBaseIntText(float CurrentInt)
{
	if(IsValid(BaseIntText))
	{
		BaseIntText->SetText(FText::FromString(FString::FromInt(FMath::Floor(CurrentInt))));
	}
}

void UTx_PlayerPortrait_Stats::SetBonusStrText(float CurrentBonusStr)
{
	if(IsValid(BonusStrText))
	{
		BonusStrText->SetText(FText::FromString(FString::SanitizeFloat(CurrentBonusStr,1)));
	}
}

void UTx_PlayerPortrait_Stats::SetBonusAgiText(float CurrentBonusAgi)
{
	if(IsValid(BonusAgyText))
	{
		BonusAgyText->SetText(FText::FromString(FString::SanitizeFloat(CurrentBonusAgi,1)));
	}
}

void UTx_PlayerPortrait_Stats::SetBonusIntText(float CurrentBonusINt)
{
	if(IsValid(BonusIntText))
	{
		BonusIntText->SetText(FText::FromString(FString::SanitizeFloat(CurrentBonusINt,1)));
	}
}
