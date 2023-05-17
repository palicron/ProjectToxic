// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilitys/Targets/GATargetActorTracerLocation.h"

#include "Abilities/GameplayAbility.h"
#include "Character/Base/Tx_Base_Character.h"
#include "Core/Tx_PlayerStateBase.h"
#include "Net/UnrealNetwork.h"
#include "Player/Tx_PlayerCamera.h"
#include "Player/Tx_PlayerCtr.h"

AGATargetActorTracerLocation::AGATargetActorTracerLocation()
{
	
	ShouldProduceTargetDataOnServer = false;
}


void AGATargetActorTracerLocation::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);

	CurrentAbility  = Ability;

	CurrentActor =  Cast<ATx_Base_Character>(Ability->GetOwningActorFromActorInfo());

	if(IsValid(CurrentActor))
	{
		CurrentActor->OnTargetConfirmLocationDelegate.AddDynamic(this,&AGATargetActorTracerLocation::AGATargetActorTracerLocation::ConfirmTargetLocation);
		
		PrimaryPC = Cast<APlayerController>(CurrentActor->OwningPlayerRef->PlayerCtr);
	}
	
}

void AGATargetActorTracerLocation::ConfirmTargetingAndContinue()
{

		FHitResult Hit;

		Hit.bBlockingHit = true;

		Hit.Location = TargetLocation;
		
		CurrentTargetData = StartLocation.MakeTargetDataHandleFromHitResult(CurrentAbility,Hit);
		
		TargetDataReadyDelegate.Broadcast(CurrentTargetData);	

}



void AGATargetActorTracerLocation::CancelTargeting()
{
	Super::CancelTargeting();
}

void AGATargetActorTracerLocation::ConfirmTargetLocation(FVector& NewTargetLocation)
{
	TargetLocation = NewTargetLocation;
	
	if(IsValid(CurrentActor))
	{
		CurrentActor->OnTargetConfirmLocationDelegate.RemoveDynamic(this,&AGATargetActorTracerLocation::AGATargetActorTracerLocation::ConfirmTargetLocation);
	}
	
	ConfirmTargetingAndContinue();
}


