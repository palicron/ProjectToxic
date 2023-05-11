// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilitys/GameplayAbility_Base.h"

#include "Abilitys/Stats/BaseAttributeSetBase.h"
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

void UGameplayAbility_Base::ChangeOwningCharacterState(CharacterState NewState)
{
	if(IsValid(OwningCharacterRef))
	{
		OwningCharacterRef->SetCurrentCharacterState(NewState);
		return;
	}

	GetOwningBaseCharacter()->SetCurrentCharacterState(NewState);
	
}

FGamePlayAbilityInfo UGameplayAbility_Base::GetAbilityInfo() const
{
	UGameplayEffect* CoolDownEffect = GetCooldownGameplayEffect();
	UGameplayEffect* CostEffect = GetCostGameplayEffect();

	if(CoolDownEffect && CostEffect)
	{
		float CoolDownDuration = 0;
		CoolDownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1,CoolDownDuration);
		
		float CostDownDuration = 0;
		EAbilityCostType CostType = EAbilityCostType::Health;

		if(CostEffect->Modifiers.Num()>0)
		{
			FGameplayModifierInfo ModifyInfo = CostEffect->Modifiers[0];
			ModifyInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1,CostDownDuration);
			FGameplayAttribute CostAttr = ModifyInfo.Attribute;
			FString AttributeName = CostAttr.AttributeName;
			if(AttributeName == "Health")
			{
				CostType = EAbilityCostType::Health;
			}
			else 
			{
				CostType = EAbilityCostType::Mana;
			}
		}

		return FGamePlayAbilityInfo(CoolDownDuration,CostDownDuration,CostType);
	}

	return FGamePlayAbilityInfo();
}

bool UGameplayAbility_Base::CanCastAbility() const
{
	FGamePlayAbilityInfo CurrentInfo = GetAbilityInfo();

	
	ATx_Base_Character* Character = Cast<ATx_Base_Character>(GetOwningActorFromActorInfo());
	if(IsValid(Character))
	{
		float CurrentResource = Character->GetAbilitySystemComp()
		->GetNumericAttribute(CurrentInfo.CostType == EAbilityCostType::Health?
			UBaseAttributeSetBase::GetHealthAttribute():UBaseAttributeSetBase::GetManaAttribute());

		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
				FString::Printf(TEXT("CurrentLife %f"), CurrentResource));
		
		return CurrentResource > FMath::Abs(CurrentInfo.Cost) ;
	}

	return false;
}
