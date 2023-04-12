// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Tx_PlayerCtr.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Player/Tx_PlayerCamera.h"


ATx_PlayerCtr::ATx_PlayerCtr()
{
	CurrentScreenSize = FVector2D::ZeroVector;
	ScreenSafeZoneValue = 50.f;
}



void ATx_PlayerCtr::BeginPlay()
{
	Super::BeginPlay();

	
		InputSubsystemRef = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

		if(IsValid(InputSubsystemRef) && IsValid(DefaultMappingContext))
		{
			InputSubsystemRef->AddMappingContext(DefaultMappingContext,0);
		}
	
		CurrentScreenSize = GetScreenCurrentSize();
	
		SetShowMouseCursor(true);
		
		const FInputModeGameAndUI InputType ;
		
		SetInputMode(InputType);
	
	
}

void ATx_PlayerCtr::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	CurrentScreenSize = GetScreenCurrentSize();
	
	UpdateMousePosition();
	
	
	if(CheckMouseOnTheEdge())
	{
		MoveCameraToTargetLocation();
	}
	
}



FVector2D ATx_PlayerCtr::GetScreenCurrentSize() const
{
	int32 XPos = CurrentScreenSize.X;

	int32 YPos = CurrentScreenSize.Y;
	
	GetViewportSize(XPos,YPos);
	
	return FVector2D(XPos,YPos);
}



void ATx_PlayerCtr::UpdateMousePosition()
{
	GetMousePosition(CurrentMousePosition.X,CurrentMousePosition.Y);
}

bool ATx_PlayerCtr::CheckMouseOnTheEdge()
{
	const float MiddlePointX = CurrentScreenSize.X/2;
	
	const float MoveZoneX = MiddlePointX - ScreenSafeZoneValue;

	const float MiddlePointY = CurrentScreenSize.Y/2;

	const float MoveZoneY = MiddlePointY - ScreenSafeZoneValue;


	if((FMath::Abs(CurrentMousePosition.X-MiddlePointX)>MoveZoneX)
		|| (FMath::Abs(CurrentMousePosition.Y-MiddlePointY)>MoveZoneY))
	{
		return true;
	}

	return false;
}
void ATx_PlayerCtr::MoveCameraToTargetLocation()
{
	FHitResult Hit;

	const bool bHitSuccessful  = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bHitSuccessful)
	{
		if (ControllerPlayer != nullptr)
		{
			FVector WorldDirection = (Hit.Location - ControllerPlayer->GetActorLocation()).GetSafeNormal();
			ControllerPlayer->AddMovementInput(WorldDirection, 50.0, false);
		}
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, .1f, FColor::Yellow, TEXT("Some debug message!"));
	}
}
