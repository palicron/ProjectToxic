// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "BaseAttributeSetBase.generated.h"

/**
 * 
 */

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthPercetageChangeDelegate,float,CurrentHealth,float , MaxHealth);

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class TOXIC_API UBaseAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()


private:
	
	UBaseAttributeSetBase();


public:

	UPROPERTY(ReplicatedUsing = OnRep_Health, EditAnywhere,BlueprintReadWrite,Category="Attribute base")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,Health)
	
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);


	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attribute base")
	FGameplayAttributeData MaxHealth;

//	UPROPERTY(BlueprintAssignable)
//	FHealthPercetageChangeDelegate OnHealthChange;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
