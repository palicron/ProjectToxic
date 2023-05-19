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

	UFUNCTION()
	virtual void OnRep_StrengthMultiplier(const FGameplayAttributeData& OldStrengthMultiplier);
	/**Intillegence Relatet Attributes */

	UPROPERTY(ReplicatedUsing = OnRep_BaseIntelligence,EditAnywhere,BlueprintReadWrite,Category="Attribute Intelligence ")
	FGameplayAttributeData BaseIntelligence;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,BaseIntelligence)
	UFUNCTION()
	virtual void OnRep_BaseIntelligence(const FGameplayAttributeData& OldBaseIntelligence);

	UPROPERTY(ReplicatedUsing = OnRep_BonusStrength,EditAnywhere,BlueprintReadWrite,Category="Attribute Intelligence ")
	FGameplayAttributeData BonusIntelligence;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,BonusIntelligence)
	UFUNCTION()
	virtual void OnRep_BonusIntelligence(const FGameplayAttributeData& OldBonusIntelligence);
	
	UPROPERTY(ReplicatedUsing = OnRep_StrengthGain,EditAnywhere,BlueprintReadWrite,Category="Attribute Intelligence ")
	FGameplayAttributeData IntelligenceGain;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,IntelligenceGain)
	UFUNCTION()
	virtual void OnRep_IntelligenceGain(const FGameplayAttributeData& OldIntelligenceGain);
	
	UPROPERTY(ReplicatedUsing = OnRep_IntelligenceMultiplier,EditAnywhere,BlueprintReadWrite,Category="Attribute Intelligence")
	FGameplayAttributeData IntelligenceMultiplier;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,IntelligenceMultiplier)
	UFUNCTION()
	virtual void OnRep_IntelligenceMultiplier(const FGameplayAttributeData& OldIntelligenceMultiplier);



	////Regen///

	UPROPERTY(ReplicatedUsing = OnRep_HealthRegen,EditAnywhere,BlueprintReadWrite,Category="Health Regen ")
	FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,HealthRegen)
	UFUNCTION()
	virtual void OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen);

	UPROPERTY(ReplicatedUsing = OnRep_BaseHealthRegen,EditAnywhere,BlueprintReadWrite,Category="Health Regen ")
	FGameplayAttributeData BaseHealthRegen;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,BaseHealthRegen)
	UFUNCTION()
	virtual void OnRep_BaseHealthRegen(const FGameplayAttributeData& OldBaseHealthRegen);

	UPROPERTY(ReplicatedUsing = OnRep_BonusHealthRegen,EditAnywhere,BlueprintReadWrite,Category="Health Regen ")
	FGameplayAttributeData BonusHealthRegen;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,BonusHealthRegen)
	UFUNCTION()
	virtual void OnRep_BonusHealthRegen(const FGameplayAttributeData& OldBonusHealthRegen);
	
	UPROPERTY(ReplicatedUsing = OnRep_RegainPerStrg,EditAnywhere,BlueprintReadWrite,Category="Health Regen ")
	FGameplayAttributeData RegainPerStrg;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,RegainPerStrg)
	UFUNCTION()
	virtual void OnRep_RegainPerStrg(const FGameplayAttributeData& OldRegainPerStrg);

	
	UPROPERTY(ReplicatedUsing = OnRep_ManaRegen,EditAnywhere,BlueprintReadWrite,Category="Mana Regen ")
	FGameplayAttributeData ManaRegen;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,ManaRegen)
	UFUNCTION()
	virtual void OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen);

	UPROPERTY(ReplicatedUsing = OnRep_BaseManaRegen,EditAnywhere,BlueprintReadWrite,Category="Mana Regen ")
	FGameplayAttributeData BaseManaRegen;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,BaseManaRegen)
	UFUNCTION()
	virtual void OnRep_BaseManaRegen(const FGameplayAttributeData& OldBaseManaRegen);

	UPROPERTY(ReplicatedUsing = OnRep_BonusManaRegen,EditAnywhere,BlueprintReadWrite,Category="Mana Regen ")
	FGameplayAttributeData BonusManaRegen;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,BonusManaRegen)
	UFUNCTION()
	virtual void OnRep_BonusManaRegen(const FGameplayAttributeData& OldBonusManaRegen);

	UPROPERTY(ReplicatedUsing = OnRep_RegainPerInt,EditAnywhere,BlueprintReadWrite,Category="Mana Regen ")
	FGameplayAttributeData RegainPerInt;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSetBase,RegainPerInt)
	UFUNCTION()
	virtual void OnRep_RegainPerInt(const FGameplayAttributeData& OldRegainPerInt);

	

	
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
	
	
};
