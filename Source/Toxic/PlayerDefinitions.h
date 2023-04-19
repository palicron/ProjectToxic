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
	Cs_Channeling UMETA(DisplayName = "Channeling")
};