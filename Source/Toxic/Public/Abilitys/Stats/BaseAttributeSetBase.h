// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "BaseAttributeSetBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthPercetageChangeDelegate,float,CurrentHealth,float , MaxHealth);

UCLASS()
class TOXIC_API UBaseAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()


private:
	
	UBaseAttributeSetBase();


public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attribute base")
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attribute base")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintAssignable)
	FHealthPercetageChangeDelegate OnHealthChange;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
