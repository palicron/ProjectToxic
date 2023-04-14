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
	void SetUpInitValues();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector2D CurrentScreenSize;

	
	UFUNCTION(BlueprintCallable)
	void UpdateMousePosition();

	///Inputs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;
	
protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player Controller")
	float ScreenSafeZoneValue;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player Controller")
	float CameraMaxSpeed = 65.f;
	
	UPROPERTY()
	float SpeedScaleFactor = 1.f;

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

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void OnClickEnd();

	virtual void OnPossess(APawn* InPawn) override;
	///RPC
	///

	UFUNCTION(Server,Reliable)
	void ServerMoveOwningCharacter(const FVector TargetLocation);

	
	
};
