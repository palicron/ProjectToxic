// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilitys/Stats/BaseAttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
UBaseAttributeSetBase::UBaseAttributeSetBase():Health(200.f)
{
	
}

void UBaseAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

		
	if(Data.EvaluatedData.Attribute.GetUProperty() ==
		FindFieldChecked<FProperty>(UBaseAttributeSetBase::StaticClass(),GET_MEMBER_NAME_CHECKED(UBaseAttributeSetBase,Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(),0.f,MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(),0.f,MaxHealth.GetCurrentValue()));
		UE_LOG(LogTemp,Warning,TEXT("DAmage take healt %f"),Health.GetCurrentValue());
		OnHealthChange.Broadcast(Health.GetCurrentValue(),MaxHealth.GetCurrentValue());
	}
}
