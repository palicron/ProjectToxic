// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tx_PlayerCamera.generated.h"

class UTx_GameInstace;
class ATx_PlayerCtr;
UCLASS()
class TOXIC_API ATx_PlayerCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATx_PlayerCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* TopDownCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(BlueprintReadOnly)
	UTx_GameInstace* GameInstanceRef;
	
	UPROPERTY(BlueprintReadOnly)
	ATx_PlayerCtr* PlayerCtr;

	UFUNCTION(BlueprintCallable)
	void InitSetUp();


public:
	
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

};
