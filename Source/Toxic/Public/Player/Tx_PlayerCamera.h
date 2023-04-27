// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Toxic/PlayerDefinitions.h"
#include "GameFramework/Pawn.h"
#include "Tx_PlayerCamera.generated.h"

class ATx_Base_Character;
class UTx_GameInstace;
class ATx_PlayerCtr;
UCLASS()
class TOXIC_API ATx_PlayerCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATx_PlayerCamera();

	UPROPERTY(BlueprintReadOnly)
	ATx_PlayerCtr* PlayerCtr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* TopDownCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UFloatingPawnMovement* MovementComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Controll")
	TSubclassOf<ATx_Base_Character> OwningCharacterToSpawn;

	UPROPERTY(ReplicatedUsing=OnRep_OwningCharacterRef,VisibleAnywhere,BlueprintReadWrite)
	ATx_Base_Character* OwningCharacterRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TSubclassOf<AActor> SpawnEffect;
	UFUNCTION()
	void OnRep_OwningCharacterRef();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	ATx_Base_Character* CurrentSelectedCharacter;
	
	UPROPERTY(BlueprintReadOnly)
	UTx_GameInstace* GameInstanceRef;
	


	UFUNCTION(BlueprintCallable)
	void InitSetUp();

	UFUNCTION()
	void SpawnOwningCharacter();
	

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable)
	void MoveOwnedCharacterToLocation(const FVector NewLocation);
	
	void MoveOwnedCharacterToLocation(ATx_Base_Character* NewTarget);

	UFUNCTION()
	void StopMovementAllActions() const;

	UFUNCTION(BlueprintCallable)
	void SetOwningCharacterAbilityConfirm() const ;

	UFUNCTION(BlueprintCallable)
	void SetPlayerCtrNewMode(ControllerType NewType) const;

	
	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE ATx_Base_Character* GetOwningCharacter() const { return OwningCharacterRef; }

	
};
