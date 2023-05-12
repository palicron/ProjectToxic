// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Tx_OverHeadBar.h"

#include "Components/ProgressBar.h"

void UTx_OverHeadBar::SetHealthPercentage(float NewPercentage)
{
	if(IsValid(HealthBar))
	{
		HealthBar->SetPercent(NewPercentage);
	}
}
