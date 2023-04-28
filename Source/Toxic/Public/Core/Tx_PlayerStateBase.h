// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Tx_PlayerStateBase.generated.h"

/**
 * 
 */
UCLASS()
class TOXIC_API ATx_PlayerStateBase : public APlayerState
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector_NetQuantize LastClickTarget;

	UFUNCTION(Server,Reliable)
	void ServerLastClickTarget(FVector_NetQuantize NewClickTarget);
	
protected:

	ATx_PlayerStateBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	

};
