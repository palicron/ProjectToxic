// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tx_PlayerCtr.generated.h"

class ATx_PlayerCamera;
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

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector2D CurrentScreenSize;

	
	UFUNCTION(BlueprintCallable)
	void UpdateMousePosition();
	
protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player Controller")
	float ScreenSafeZoneValue;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player Controller")
	bool bCanPlayerMoveCamera = true;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player Controller")
	ATx_PlayerCamera* ControllerPlayer;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Config")
	float ShortPressThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Config")
	UNiagaraSystem* FXCursor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input Config")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(BlueprintReadWrite, Category="Input Config")
	UEnhancedInputLocalPlayerSubsystem* InputSubsystemRef ;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector2D CurrentMousePosition;

	UFUNCTION(BlueprintCallable)
	bool CheckMouseOnTheEdge();
	
	FVector2D GetScreenCurrentSize() const;

	UFUNCTION(BlueprintCallable)
	void MoveCameraToTargetLocation();
	
	
};