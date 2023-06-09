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

	if(IsValid(ControlledCharacterRef) && HasAuthority())
	{
		ControlledCharacterRef->SetCurrentCharacterState(CharacterState::Cs_Idle);
	}
	
}

void ATx_Base_AICharacterCtr::MoveActorToLocation(const FVector Location)
{
	if(IsValid(ControlledCharacterRef) && HasAuthority())
	{
		ControlledCharacterRef->SetCurrentCharacterState(CharacterState::Cs_MovingToLocation);
		
		MoveToLocation(Location,100.f);
	}
	
}

void ATx_Base_AICharacterCtr::MoveActorToTarget(ATx_Base_Character* Target)
{
	if(IsValid(ControlledCharacterRef) && HasAuthority())
	{
		ControlledCharacterRef->SetCurrentCharacterState(CharacterState::Cs_MovingToTarget);
		
		MoveToActor(Target,100.f);
	}
}
