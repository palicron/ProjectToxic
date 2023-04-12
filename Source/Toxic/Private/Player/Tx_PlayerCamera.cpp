
#include "Player/Tx_PlayerCamera.h"

#include "Camera/CameraComponent.h"
#include "Core/Tx_GameInstace.h"
#include "GameFramework/HUD.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
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

}


void ATx_PlayerCamera::BeginPlay()
{
	Super::BeginPlay();
	
	InitSetUp();
}


void ATx_PlayerCamera::InitSetUp()
{
	GameInstanceRef = Cast<UTx_GameInstace>(GetGameInstance());
	if(IsValid(GameInstanceRef))
	{
		//Using This Funtion For consitency in multiplayer 
		PlayerCtr = Cast<ATx_PlayerCtr>(GameInstanceRef->GetFirstLocalPlayerController());
	}
	//Set Mouse
	if(IsValid(PlayerCtr))
	{
	
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



