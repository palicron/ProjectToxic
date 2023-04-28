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

	AGATargetActorTracerLocation();

	UPROPERTY(ReplicatedUsing=OnRep_CurrenTargetData)
	FGameplayAbilityTargetDataHandle CurrentTargetData;

	UFUNCTION()
	void OnRep_CurrenTargetData();
	
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;

	virtual void CancelTargeting() override;

	UPROPERTY()
	TWeakObjectPtr<UGameplayAbility> CurrentAbility;


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
