// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilitys/Targets/GATargetActorTracerLocation.h"

#include "Abilities/GameplayAbility.h"
#include "Character/Base/Tx_Base_Character.h"
#include "Player/Tx_PlayerCamera.h"
#include "Player/Tx_PlayerCtr.h"

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

void AGATargetActorTracerLocation::ConfirmTargetingAndContinue()
{
	if(IsValid(PrimaryPC))
	{
		FHitResult Hit;
		
		PrimaryPC->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1,true, Hit);
		
		FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromHitResult(CurrentAbility,Hit);

		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1,
				15.0f, FColor::Yellow,
				FString::Printf(TEXT("(World delta for current frame equals %s)"), *Hit.ImpactPoint.ToString()));
		
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
		
	
}

void AGATargetActorTracerLocation::CancelTargeting()
{
	Super::CancelTargeting();
}
