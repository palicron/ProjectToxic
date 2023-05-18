// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Tx_PlayerPortrait_Stats.generated.h"

class ATx_PlayerCamera;
/**
 * 
 */
class UTextBlock;
UCLASS()
class TOXIC_API UTx_PlayerPortrait_Stats : public UUserWidget
{
	GENERATED_BODY()

protected:

	

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BaseStrText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BaseAgiText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BaseIntText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BonusStrText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BonusAgyText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BonusIntText;
public:

	
	UFUNCTION(BlueprintCallable)
	void SetBaseStrText(float CurrentStr);

	UFUNCTION(BlueprintCallable)
	void SetBaseAgiText(float CurrentAgi);

	UFUNCTION(BlueprintCallable)
	void SetBaseIntText(float CurrentInt);

	UFUNCTION(BlueprintCallable)
	void SetBonusStrText(float CurrentBonusStr);

	UFUNCTION(BlueprintCallable)
	void SetBonusAgiText(float CurrentBonusAgi);

	UFUNCTION(BlueprintCallable)
	void SetBonusIntText(float CurrentBonusINt);

	
	
};
