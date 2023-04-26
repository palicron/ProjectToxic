// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Toxic/PlayerDefinitions.h"
#include "Tx_HookActor.generated.h"

class UBoxComponent;

class UProjectileMovementComponent;

UCLASS()
class TOXIC_API ATx_HookActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATx_HookActor();

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float HookSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float HookRange = 1000.f;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Mesh")
	UStaticMeshComponent* HookMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Mesh")
	UBoxComponent* CollisionBox; 

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hooking")
	FVector HookSpawnLocation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hooking")
	FVector HookTargetLocation;

	UPROPERTY(EditAnywhere, Category = "Compoents")
	class USceneCaptureComponent* SceneCaptureComp;

	bool bCheck = false;

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	HookStates CurrentState;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartHookingMove(FVector TargetLocation);

	UFUNCTION(BlueprintCallable)
	void ChangeHookState(HookStates newState);

};
