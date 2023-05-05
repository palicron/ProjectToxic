// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilitys/Stats/BaseAttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "Net/UnrealNetwork.h"

UBaseAttributeSetBase::UBaseAttributeSetBase():Health(100.f)
{
	MaxHealth = Health;
}




void UBaseAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if(Data.EvaluatedData.Attribute.GetUProperty() ==
		FindFieldChecked<FProperty>(UBaseAttributeSetBase::StaticClass(),GET_MEMBER_NAME_CHECKED(UBaseAttributeSetBase,Health)))
	{
		UE_LOG(LogTemp,Warning,TEXT("healt %f"),MaxHealth.GetCurrentValue());
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(),0.f,MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(),0.f,MaxHealth.GetCurrentValue()));
		UE_LOG(LogTemp,Warning,TEXT("DAmage take healt %f"),Health.GetCurrentValue());
		
		//OnHealthChange.Broadcast(Health.GetCurrentValue(),MaxHealth.GetCurrentValue());
	}
}

void UBaseAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSetBase, Health, COND_None, REPNOTIFY_Always);
}

void UBaseAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSetBase, Health, OldHealth);
}