// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Tx_PlayerCtr.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"


ATx_PlayerCtr::ATx_PlayerCtr()
{
	
}

void ATx_PlayerCtr::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		InputSubsystemRef = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

		if(IsValid(InputSubsystemRef) && IsValid(DefaultMappingContext))
		{
			InputSubsystemRef->AddMappingContext(DefaultMappingContext,0);
		}
	}
	
}
