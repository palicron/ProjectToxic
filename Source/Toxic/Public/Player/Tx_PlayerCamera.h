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
	
	UPROPERTY(ReplicatedUsing=OnRep_ControllerType, EditAnywhere,BlueprintReadWrite)
	ControllerType CurrentCtrType = ControllerType::Ct_Normal;

    FVector LAsCLickTest;


protected:

	
	UFUNCTION()
	void OnRep_LastCLickTarget();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player UI")
	class UTx_PlayerMainUI* PlayerUIRef;
	
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

	UFUNCTION()
	void OnRep_ControllerType();

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

	virtual void ActiveSlotAbility(const int32 SlotIndex) const;

	
	UFUNCTION(BlueprintCallable)
	void MoveOwnedCharacterToLocation(const FVector NewLocation);
	
	void MoveOwnedCharacterToLocation(ATx_Base_Character* NewTarget);

	UFUNCTION()
	void StopMovementAllActions() const;

	UFUNCTION(BlueprintCallable)
	void SetOwningCharacterAbilityConfirm() const ;


	//RPCS//
	
	UFUNCTION(Server,Reliable)
	void ServerSetTargetConfirmLocation(FVector NewTarget);


	UFUNCTION(BlueprintImplementableEvent)
	void BP_SpawnUI();
	
	UFUNCTION(Client,BlueprintCallable,Reliable)
	void UpdateLifeUI(float NewLife,float MaxLife);


	//UFUNCTION()
	//void ClientUpdateLifeUI(float NewLife,float MaxLife);
	UFUNCTION(Server,Reliable)
	void ServerLastClickTarget(FVector_NetQuantize newLocation);
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTx_PlayerMainUI* GetPlayerUI() const {return PlayerUIRef;}

	UFUNCTION(BlueprintCallable)
	void SetPlayerUI(UTx_PlayerMainUI* NewPlayerUI);
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetCtrControllerMode(ControllerType NewType){CurrentCtrType = NewType;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ControllerType GetCtrControllerMode() const { return CurrentCtrType;}
	
	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE ATx_Base_Character* GetOwningCharacter() const { return OwningCharacterRef; }

	
};
