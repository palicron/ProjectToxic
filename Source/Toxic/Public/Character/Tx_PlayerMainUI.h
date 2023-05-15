// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Tx_PlayerMainUI.generated.h"

/**
 * 
 */

class UProgressBar;
class ATx_PlayerCtr;
class UAbilitySystemComponent;
class UTextBlock;
UCLASS()
class TOXIC_API UTx_PlayerMainUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ManaBar;
	
	UPROPERTY()
	ATx_PlayerCtr* OwningPlayerCtrRef;
	
	UPROPERTY()
	UAbilitySystemComponent* OwningAbilitySystemRef;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentHealthText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHealthText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentManaText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxManaText;

public:

	UFUNCTION(BlueprintCallable)
	void SetNewHealth(float NewHealth,float MaxHealth);

	UFUNCTION(BlueprintCallable)
	void SetMaxNewHealth(float MaxHealth);

	UFUNCTION(BlueprintCallable)
	void SetManaHealth(float NewMana,float MaxMana);

	UFUNCTION(BlueprintCallable)
	void SetMaxNewMana(float MaxMana);
	
};
