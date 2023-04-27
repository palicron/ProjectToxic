// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActorTracerLocation.generated.h"

/**
 * 
 */
UCLASS()
class TOXIC_API AGATargetActorTracerLocation : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()


protected:
	
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;

	virtual void CancelTargeting() override;

	UPROPERTY()
	TWeakObjectPtr<UGameplayAbility> CurrentAbility;
	
};
