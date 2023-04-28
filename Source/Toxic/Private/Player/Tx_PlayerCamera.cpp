
#include "Player/Tx_PlayerCamera.h"

#include "NiagaraFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Character/Tx_Base_AICharacterCtr.h"
#include "Character/Base/Tx_Base_Character.h"
#include "Core/Tx_GameInstace.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/Tx_PlayerCtr.h"


ATx_PlayerCamera::ATx_PlayerCamera()
{
 	
	PrimaryActorTick.bCanEverTick = true;



	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));



}

void ATx_PlayerCamera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION(ATx_PlayerCamera,OwningCharacterRef,COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ATx_PlayerCamera,CurrentCtrType,COND_OwnerOnly);
	
	
}



void ATx_PlayerCamera::ServerLastClickTarget_Implementation(FVector_NetQuantize newLocation)
{
}

void ATx_PlayerCamera::setTestdEtes_Implementation(FVector coso)
{

	LAsCLickTest = coso;
	/*if(OwningCharacterRef)
	{
		OwningCharacterRef->ServerTraceToObjective(coso);
	}*/
}

void ATx_PlayerCamera::OnRep_LastCLickTarget()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("adasdasds asdasdsad asdasdsa"));
}

void ATx_PlayerCamera::BeginPlay()
{
	Super::BeginPlay();
	
	InitSetUp();
	SpawnOwningCharacter();
}


void ATx_PlayerCamera::InitSetUp()
{
	GameInstanceRef = Cast<UTx_GameInstace>(GetGameInstance());
	if(IsValid(GameInstanceRef))
	{
		//Using This Funtion For consitency in multiplayer 
		PlayerCtr = Cast<ATx_PlayerCtr>(GameInstanceRef->GetFirstLocalPlayerController());
	}


}

void ATx_PlayerCamera::OnRep_OwningCharacterRef()
{

	if(!HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
	FString::Printf(TEXT("Change state asdasd : x: %s"),*this->GetName() ));
		
		CurrentSelectedCharacter = OwningCharacterRef;
	}
	
}

void ATx_PlayerCamera::OnRep_ControllerType()
{

	if(!HasAuthority())
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));	
	}
	
}


void ATx_PlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void ATx_PlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATx_PlayerCamera::MoveOwnedCharacterToLocation(const FVector NewLocation)
{
	if(IsValid(OwningCharacterRef) && IsValid(OwningCharacterRef->GetAiController()))
	{
		OwningCharacterRef->SetCurrentActorTarget(nullptr);
		OwningCharacterRef->GetAiController()->MoveActorToLocation(NewLocation);
	}
}

void ATx_PlayerCamera::MoveOwnedCharacterToLocation(ATx_Base_Character* NewTarget)
{
	if(IsValid(OwningCharacterRef) && IsValid(OwningCharacterRef->GetAiController()) && IsValid(NewTarget))
	{
		OwningCharacterRef->SetCurrentActorTarget(NewTarget);

		OwningCharacterRef->CheckDistanceToAttack();
		
		OwningCharacterRef->GetAiController()->MoveActorToTarget(NewTarget);
		
	}
}

void ATx_PlayerCamera::StopMovementAllActions() const
{
	if(HasAuthority() && OwningCharacterRef)
	{
		OwningCharacterRef->StopAllActionByPlayer();
	}
}

void ATx_PlayerCamera::SetOwningCharacterAbilityConfirm() const
{
	if(HasAuthority() && OwningCharacterRef)
	{
		OwningCharacterRef->StopAllActionByPlayer();
	}
}


void ATx_PlayerCamera::SpawnOwningCharacter()
{
	if(HasAuthority() && IsValid(OwningCharacterToSpawn))
	{
		const FActorSpawnParameters SpawnParams;
		
		OwningCharacterRef = GetWorld()->SpawnActor<ATx_Base_Character>(OwningCharacterToSpawn,GetActorLocation(),FRotator::ZeroRotator,SpawnParams);

		CurrentSelectedCharacter = OwningCharacterRef;
		
		OwningCharacterRef->SetOwningPlayerBaseRef(this);
	}
}






