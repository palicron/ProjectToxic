// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tx_PlayerCtr.generated.h"

class UInputMappingContext;
class UNiagaraSystem;
class UEnhancedInputLocalPlayerSubsystem;
/**
 * 
 */
UCLASS()
class TOXIC_API ATx_PlayerCtr : public APlayerController
{
	GENERATED_BODY()

public:
	
	ATx_PlayerCtr();

protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Config")
	float ShortPressThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Config")
	UNiagaraSystem* FXCursor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input Config")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(BlueprintReadWrite, Category="Input Config")
	UEnhancedInputLocalPlayerSubsystem* InputSubsystemRef ; 
	
};
