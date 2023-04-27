// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilitys/GameplayAbility_ClickTarget.h"

#include "Character/Base/Tx_Base_Character.h"

bool UGameplayAbility_ClickTarget::IsTargetInRage(const FVector& TargetLocation)  
{

	if(IsValid(GetOwningBaseCharacter()))
	{
		return (FVector::Dist(OwningCharacterRef->GetActorLocation(),TargetLocation)<=AbilityRange);
	}
	
	return false;
}

bool UGameplayAbility_ClickTarget::IsTargetInRangeOfActor(const AActor* ActorLocation)
{
	if(IsValid(GetOwningBaseCharacter()))
	{
		return (FVector::Dist(OwningCharacterRef->GetActorLocation(),ActorLocation->GetActorLocation())<=AbilityRange);
	}
	
	return false;

}
