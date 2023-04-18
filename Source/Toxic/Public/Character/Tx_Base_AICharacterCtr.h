// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tx_Base_AICharacterCtr.generated.h"

class ATx_Base_Character;
/**
 * 
 */
UCLASS()
class TOXIC_API ATx_Base_AICharacterCtr : public AAIController
{
	GENERATED_BODY()

protected:


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Team Data")
	uint8 TeamId = 255;
	
	virtual void BeginPlay() override;

	UPROPERTY()
	ATx_Base_Character* ControlledCharacterRef;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

public:
	/**
	 * @brief 
	 * @param Location CHANGE THIS VFECTOR TO NET VECTORS  @TODO
	 */
	UFUNCTION()
	void MoveActorToLocation(const FVector Location);
	
	void MoveActorToTarget(ATx_Base_Character* Target);
	
};
