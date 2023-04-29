// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActorTracerLocation.generated.h"


class ATx_Base_Character;
/**
 * 
 */
UCLASS()
class TOXIC_API AGATargetActorTracerLocation : public AGameplayAbilityTargetActor
{
	
	GENERATED_BODY()


protected:

	AGATargetActorTracerLocation();

	UPROPERTY()
	FGameplayAbilityTargetDataHandle CurrentTargetData;
	
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;

	virtual void CancelTargeting() override;
	
	UPROPERTY()
	ATx_Base_Character* CurrentActor;
	
	UPROPERTY()
	TWeakObjectPtr<UGameplayAbility> CurrentAbility;

	UPROPERTY()
	FVector TargetLocation;
	
	UFUNCTION()
	void ConfirmTargetLocation(FVector& NewTargetLocation);
	
};
