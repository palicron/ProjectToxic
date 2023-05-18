#pragma once
#include "PlayerDefinitions.generated.h"

UENUM(BlueprintType)
enum class  CharacterState: uint8
{
	Cs_Idle UMETA(DisplayName = "Idle"),
	Cs_MovingToLocation UMETA(DisplayName = "Moving To Location"),
	Cs_MovingToTarget UMETA(DisplayName = "Moving To Target"),
	Cs_Attacking UMETA(DisplayName = "Attacking"),
	Cs_Stunned UMETA(DisplayName = "Stunned"),
	Cs_Dead UMETA(DisplayName = "Dead"),
	Cs_Channeling UMETA(DisplayName = "Channeling"),
	Cs_Targeting UMETA(DisplayName = "Targeting")
};

UENUM(BlueprintType)
enum class  ControllerType: uint8
{
	Ct_Normal UMETA(DisplayName = "normal"),
	Ct_Targeting UMETA(DisplayName = "Targeting"),
	Ct_DisableMovement UMETA(DisplayName = "Disalbe Movement")
};

UENUM(BlueprintType)
enum class  HookStates: uint8
{
	Hook_Traveling UMETA(DisplayName = "Traveling"),
	Hook_Retriving UMETA(DisplayName = "Retriving")
};

UENUM(BlueprintType)
enum class  AbilityType: uint8
{
	AT_MeleeAttack UMETA(DisplayName = "Melee Attack"),
	AT_RangeAttack UMETA(DisplayName = "Range Attack"),
	AT_TargetAbility UMETA(DisplayName = "Target Ability"),
	AT_ToggleAbility UMETA(DisplayName = "Toggle Ability"),
	AT_ChannelAbility UMETA(DisplayName = "Channel Ability"),
	
};

UENUM(BlueprintType)
enum class EAbilityCostType : uint8
{
	Health UMETA(DisplayName = "Health"),
	Mana UMETA(DisplayName = "Mana")
	
};

USTRUCT(BlueprintType)
struct FGamePlayAbilityInfo
{

	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability Info")
	float CoolDownDuration = 0.0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability Info")
	float Cost;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability Info")
	EAbilityCostType CostType;

	FGamePlayAbilityInfo(): CoolDownDuration(0.0), Cost(0.0), CostType(EAbilityCostType::Mana)
	{
	}

	FGamePlayAbilityInfo(float InCoolDown,float InCost, const EAbilityCostType InType)
	{
		CoolDownDuration = InCoolDown;

		Cost = InCost;

		CostType = InType;
	}
};

UENUM(BlueprintType)
enum class  StatusType: uint8
{
	ST_BaseStrength UMETA(DisplayName = "Base strength"),
	ST_BonusStrength UMETA(DisplayName = "Bonus strength"),
	ST_BaseAgility UMETA(DisplayName = "Base agility"),
	ST_BonusAgility UMETA(DisplayName = "bonus Agility"),
	ST_BaseIntelligence UMETA(DisplayName = "Base Intelligence"),
	ST_BonusIntelligence UMETA(DisplayName = "bonus Intelligence")

	
};