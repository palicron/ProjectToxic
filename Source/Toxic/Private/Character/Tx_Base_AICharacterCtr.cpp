// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Tx_Base_AICharacterCtr.h"

#include "Character/Base/Tx_Base_Character.h"

void ATx_Base_AICharacterCtr::BeginPlay()
{
	Super::BeginPlay();


}

void ATx_Base_AICharacterCtr::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ControlledCharacterRef = Cast<ATx_Base_Character>(InPawn);

	if(IsValid(ControlledCharacterRef))
	{
		ControlledCharacterRef->SetAiController(this);
	}
}

void ATx_Base_AICharacterCtr::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));	
}

void ATx_Base_AICharacterCtr::MoveActorToLocation(const FVector Location)
{
	MoveToLocation(Location,25.f);
}
