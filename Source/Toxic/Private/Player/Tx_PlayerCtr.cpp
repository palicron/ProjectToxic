// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Tx_PlayerCtr.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Character/Base/Tx_Base_Character.h"
#include "Player/Tx_PlayerCamera.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

ATx_PlayerCtr::ATx_PlayerCtr()
{
	CurrentScreenSize = FVector2D::ZeroVector;
	ScreenSafeZoneValue = 50.f;
	bCanPlayerMoveCamera = true;
	bCanFocusOwnedCharacter = true;
	bOngoingFocusDistance = false;
}

void ATx_PlayerCtr::BeginPlay()
{
	Super::BeginPlay();

	if(IsLocalController())
	{
		SetUpInitValues();
	}
	
}


void ATx_PlayerCtr::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATx_PlayerCtr::OnClickEnd);
		EnhancedInputComponent->BindAction(SetFocusActionInput, ETriggerEvent::Triggered, this, &ATx_PlayerCtr::OnFocusTrigger);
		EnhancedInputComponent->BindAction(SetFocusActionInput, ETriggerEvent::Completed, this, &ATx_PlayerCtr::ResetOnFocusFlag);
	}
}

void ATx_PlayerCtr::OnClickEnd()
{

	if(!bCanPlayerMoveCamera) return;
	
	FHitResult Hit;
	
	const bool bHitSuccessful  = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bHitSuccessful && IsValid(ControllerPlayer))
	{
		ServerMoveOwningCharacter(Hit.Location);
	}

}

void ATx_PlayerCtr::OnFocusTrigger()
{
	if(bCanFocusOwnedCharacter)
	{
		bCanFocusOwnedCharacter = false;
		bCanPlayerMoveCamera = false;
		bOngoingFocusDistance = true;
		GetWorld()->GetTimerManager().ClearTimer(FocusCameraTimerHandle);
		
		GetWorld()->GetTimerManager().SetTimer(FocusCameraTimerHandle,
			this,&ThisClass::MoveCameraToOwnCharacter,0.0001f,true); 
	
	}
}


void ATx_PlayerCtr::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(IsValid(InPawn) && HasAuthority())
	{
		ControllerPlayer = Cast<ATx_PlayerCamera>(InPawn);
	}
}


void ATx_PlayerCtr::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsValid(ControllerPlayer) && ControllerPlayer->IsLocallyControlled())
	{
		CurrentScreenSize = GetScreenCurrentSize();
	
		UpdateMousePosition();
	
		if(CheckMouseOnTheEdge() && bCanPlayerMoveCamera)
		{
			MoveCameraToTargetLocation();
		}
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

	SpeedScaleFactor = 1.f;
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
			
			ControllerPlayer->AddMovementInput(WorldDirection, CameraMaxSpeed * SpeedScaleFactor, true);
			
		}
	
	}
}


void ATx_PlayerCtr::ServerMoveOwningCharacter_Implementation(const FVector TargetLocation)
{
	if( IsValid(ControllerPlayer))
	{
		ControllerPlayer->MoveOwnedCharacterToLocation(TargetLocation);
	}
	
}

void ATx_PlayerCtr::MoveCameraToOwnCharacter()
{
	if(IsValid(ControllerPlayer) && IsValid(ControllerPlayer->GetOwningCharacter()))
	{
	
		FVector CameraPosition = ControllerPlayer->GetActorLocation();
		CameraPosition.Z = 0;
		FVector PlayerPosition = ControllerPlayer->GetOwningCharacter()->GetActorLocation();
		PlayerPosition.Z = 0;
		
		if( FVector::Distance(CameraPosition,PlayerPosition)>CameraFocusAcceptanceRadius)
		{
	
			ControllerPlayer->AddMovementInput((ControllerPlayer->GetOwningCharacter()->GetActorLocation()
				- ControllerPlayer->GetActorLocation()).GetSafeNormal()
				, CameraFocusMaxSpeed, true);
			return;
		}
		else
		{
			ControllerPlayer->GetMovementComponent()->StopMovementImmediately();
			ControllerPlayer->SetActorLocation(ControllerPlayer->GetOwningCharacter()->GetActorLocation());
		}
	 
	}

		bCanFocusOwnedCharacter = true;
		bCanPlayerMoveCamera = true;
		bOngoingFocusDistance = false;
	
		GetWorld()->GetTimerManager().ClearTimer(FocusCameraTimerHandle);
}


void ATx_PlayerCtr::SetUpInitValues()
{
	ControllerPlayer = Cast<ATx_PlayerCamera>(GetPawn());
		
	if(IsValid(ControllerPlayer) && ControllerPlayer->IsLocallyControlled())
	{
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
}