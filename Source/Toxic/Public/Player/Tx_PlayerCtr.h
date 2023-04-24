// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tx_PlayerCtr.generated.h"

class ATx_Base_Character;
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	 UInputAction* SetFocusActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	 UInputAction* SetCancelAbilityInput;
	
protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player Controller")
	float ScreenSafeZoneValue;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player Controller")
	float CameraFocusAcceptanceRadius = 100.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player Controller")
	float CameraMaxSpeed = 65.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player Controller")
	float CameraFocusMaxSpeed = 500000.f;
	
	UPROPERTY()
	float SpeedScaleFactor = 1.f;

	bool bCanFocusOwnedCharacter;

	bool bOngoingFocusDistance;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player Controller")
	bool bCanPlayerMoveCamera = true;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player Controller")
	ATx_PlayerCamera* ControllerPlayer;

	FTimerHandle FocusCameraTimerHandle;
	
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

	UFUNCTION(BlueprintCallable)
	void MoveCameraToOwnCharacter();

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void OnClickEnd();

	UFUNCTION(Server,Unreliable)
	void StopAction();

	UFUNCTION()
	void OnFocusTrigger();

	UFUNCTION()
	FORCEINLINE void ResetOnFocusFlag() {bCanFocusOwnedCharacter = true;};

	virtual void OnPossess(APawn* InPawn) override;


	
	///RPC//////


	UFUNCTION(Server,Reliable)
	void ServerMoveCharacterToTargetActor( ATx_Base_Character* NewTargetCharacter) ;
	
	UFUNCTION(Server,Reliable)
	void ServerMoveOwningCharacter(const FVector TargetLocation);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
 
};
