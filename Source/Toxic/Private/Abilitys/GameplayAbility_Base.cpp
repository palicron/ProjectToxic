// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilitys/GameplayAbility_Base.h"

#include "Character/Tx_Base_AICharacterCtr.h"
#include "Character/Base/Tx_Base_Character.h"

ATx_Base_Character* UGameplayAbility_Base::GetOwningBaseCharacter()
{
	if(IsValid(OwningCharacterRef))
	{
		return OwningCharacterRef;
	}

	OwningCharacterRef = Cast<ATx_Base_Character>(GetOwningActorFromActorInfo());
	
	return OwningCharacterRef;
}

ATx_Base_AICharacterCtr* UGameplayAbility_Base::GetOwningBaseCharacterCtr()
{
	if(IsValid(OwningCharacterCtrRef))
	{
		return OwningCharacterCtrRef;
	}

	if(IsValid(OwningCharacterRef))
	{
		OwningCharacterCtrRef = OwningCharacterRef->GetAiController();
		return OwningCharacterCtrRef;
	}
	
	OwningCharacterCtrRef = GetOwningBaseCharacter()->GetAiController();
	
	return OwningCharacterCtrRef;
}
