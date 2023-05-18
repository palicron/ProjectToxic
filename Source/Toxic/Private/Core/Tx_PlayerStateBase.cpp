// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Tx_PlayerStateBase.h"

#include "Net/UnrealNetwork.h"

ATx_PlayerStateBase::ATx_PlayerStateBase()
{
	bReplicates = true;
}

void ATx_PlayerStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
}


void ATx_PlayerStateBase::ServerLastClickTarget_Implementation(FVector_NetQuantize NewClickTarget)
{
	LastClickTarget = NewClickTarget;
	
}
