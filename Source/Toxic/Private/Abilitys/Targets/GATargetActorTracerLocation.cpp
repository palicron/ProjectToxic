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

	ATx_Base_Character* CurrentActor =  Cast<ATx_Base_Character>(Ability->GetOwningActorFromActorInfo());

	if(IsValid(CurrentActor))
	{
		PrimaryPC = Cast<APlayerController>(CurrentActor->OwningPlayerRef->PlayerCtr);
	}
	
}

void AGATargetActorTracerLocation::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION(AGATargetActorTracerLocation,CurrentTargetData,COND_OwnerOnly);
	
}

void AGATargetActorTracerLocation::ConfirmTargetingAndContinue()
{
	if(IsValid(PrimaryPC))
	{
		FHitResult Hit;

		FVector LocationToUse = Cast<ATx_PlayerCtr>(PrimaryPC)->GetControllerPLayer()->LAsCLickTest;

		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
				FString::Printf(TEXT("(World delta for current frame equals %ls)"),
					*LocationToUse.ToString()));
		
		PrimaryPC->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1,true, Hit);

		Hit.Location = LocationToUse;
		CurrentTargetData = StartLocation.MakeTargetDataHandleFromHitResult(CurrentAbility,Hit);
		
		
		TargetDataReadyDelegate.Broadcast(CurrentTargetData);	
		
	}
	
}


void AGATargetActorTracerLocation::OnRep_CurrenTargetData()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("ON sssssssssssssssss Stats"));
	TargetDataReadyDelegate.Broadcast(CurrentTargetData);	
}

void AGATargetActorTracerLocation::CancelTargeting()
{
	Super::CancelTargeting();
}


