#pragma once


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