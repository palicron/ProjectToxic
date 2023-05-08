// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilitys/GameplayAbility_Base.h"
#include "GameplayAbility_ClickTarget.generated.h"

/**
 * 
 */
UCLASS()
class TOXIC_API UGameplayAbility_ClickTarget : public UGameplayAbility_Base
{
	GENERATED_BODY()

public:



	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Target Config")
	float AbilityRange = 500.f;
	

	UFUNCTION(BlueprintCallable)
	bool IsTargetInRage(const FVector& TargetLocation);
	
	UFUNCTION(BlueprintCallable)
	bool IsTargetInRangeOfActor(const AActor* ActorLocation);


};
