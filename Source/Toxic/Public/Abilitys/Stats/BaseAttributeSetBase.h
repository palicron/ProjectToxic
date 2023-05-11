// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "BaseAttributeSetBase.generated.h"

/**
 * 
 */


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
	
	UPROPERTY(ReplicatedUsing = OnRep_Health, EditAnywhere,BlueprintReadWrite,Category="Attribute Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,Health)
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UPROPERTY(ReplicatedUsing = OnRep_CurrentLevel, EditAnywhere,BlueprintReadWrite,Category="Attribute Level")
	FGameplayAttributeData CurrentLevel;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,CurrentLevel)
	UFUNCTION()
	virtual void OnRep_CurrentLevel(const FGameplayAttributeData& OldCurrentLevel);

	UPROPERTY(ReplicatedUsing = OnRep_BaseHealth, EditAnywhere,BlueprintReadWrite,Category="Attribute Health")
	FGameplayAttributeData BaseHealth;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,BaseHealth)
	UFUNCTION()
	virtual void OnRep_BaseHealth(const FGameplayAttributeData& OldBaseHealth);
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth,EditAnywhere,BlueprintReadWrite,Category="Attribute Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,MaxHealth)
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UPROPERTY(ReplicatedUsing = OnRep_Mana,EditAnywhere,BlueprintReadWrite,Category="Attribute Mana")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,Mana)
	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);
	
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxMana,EditAnywhere,BlueprintReadWrite,Category="Attribute Mana")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,MaxMana)
	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	
	UPROPERTY(ReplicatedUsing = OnRep_BaseMana,EditAnywhere,BlueprintReadWrite,Category="Attribute Mana")
	FGameplayAttributeData BaseMana;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,BaseMana)
	UFUNCTION()
	virtual void OnRep_BaseMana(const FGameplayAttributeData& OldBaseMana);

	UPROPERTY(ReplicatedUsing = OnRep_MovementSpeed,EditAnywhere,BlueprintReadWrite,Category="Attribute Movement")
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,MovementSpeed)
	UFUNCTION()
	virtual void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed);
	
	
	/**Strength Relatet Attributes */

	UPROPERTY(ReplicatedUsing = OnRep_BaseStrength,EditAnywhere,BlueprintReadWrite,Category="Attribute Strength ")
	FGameplayAttributeData BaseStrength;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,BaseStrength)
	UFUNCTION()
	virtual void OnRep_BaseStrength(const FGameplayAttributeData& OldBaseStrength);

	UPROPERTY(ReplicatedUsing = OnRep_BonusStrength,EditAnywhere,BlueprintReadWrite,Category="Attribute Strength ")
	FGameplayAttributeData BonusStrength;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,BonusStrength)
	UFUNCTION()
	virtual void OnRep_BonusStrength(const FGameplayAttributeData& OldBonusStrength);
	
	UPROPERTY(ReplicatedUsing = OnRep_StrengthGain,EditAnywhere,BlueprintReadWrite,Category="Attribute Strength ")
	FGameplayAttributeData StrengthGain;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,StrengthGain)
	UFUNCTION()
	virtual void OnRep_StrengthGain(const FGameplayAttributeData& OldStrengthGain);
	
	UPROPERTY(ReplicatedUsing = OnRep_StrengthMultiplier,EditAnywhere,BlueprintReadWrite,Category="Attribute Strength")
	FGameplayAttributeData StrengthMultiplier;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,StrengthMultiplier)


	/**Intillegence Relatet Attributes */

	
	UFUNCTION()
	virtual void OnRep_StrengthMultiplier(const FGameplayAttributeData& OldStrengthMultiplier);
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
	
	
};
