// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAddons/Tx_HookActor.h"

#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATx_HookActor::ATx_HookActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SceneCaptureComp = CreateDefaultSubobject<USceneCaptureComponent>("DefaultRootComponent");
	RootComponent = SceneCaptureComp;
	
	HookMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hook mesh"));
	HookMesh->SetupAttachment(RootComponent);
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hook Colission"));

	CollisionBox->SetupAttachment(HookMesh);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Comp"));

}

// Called when the game starts or when spawned
void ATx_HookActor::BeginPlay()
{
	Super::BeginPlay();

	HookSpawnLocation = GetActorLocation();

	HookSpeed = MovementComponent->InitialSpeed;

	MovementComponent->Velocity = GetActorForwardVector() * HookSpeed;

	//FVector HookPosition = ( GetActorLocation()	+ (GetActorForwardVector()* HookRange));

	
	
}

// Called every frame
void ATx_HookActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bCheck) return;

	const float CurrentHookLenght = FVector::Dist(GetActorLocation(), HookSpawnLocation);

	/// TODO Check if need to move to location
	
	if(CurrentState == HookStates::Hook_Traveling && CurrentHookLenght >= HookRange)
	{
		BP_MaxRangeHook();
		ChangeHookState(HookStates::Hook_Retriving);
	}
	else if(CurrentState == HookStates::Hook_Retriving &&  CurrentHookLenght < 20.f)
	{
		BP_EndLine();
		
		Destroy();
	}
}

void ATx_HookActor::StartHookingMove(FVector TargetLocation)
{
	bCheck = true;
	CurrentState = HookStates::Hook_Traveling;
	HookTargetLocation = TargetLocation;
	
}

void ATx_HookActor::ChangeHookState(HookStates newState)
{
	switch (newState) {
		case HookStates::Hook_Traveling:

			CurrentState = HookStates::Hook_Traveling;
		
		MovementComponent->Velocity = GetActorForwardVector()*HookSpeed;
		
			break;
	case HookStates::Hook_Retriving:

		CurrentState = HookStates::Hook_Retriving;
		
		MovementComponent->Velocity = GetActorForwardVector()*-HookSpeed;
		break;
	default: ;
	}
}

