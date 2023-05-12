// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Tx_OverHeadBar.generated.h"
class UProgressBar;
/**
 * 
 */
UCLASS()
class TOXIC_API UTx_OverHeadBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

public:

	UFUNCTION(BlueprintCallable)
	void SetHealthPercentage(float NewPercentage);

	

	
	
};
