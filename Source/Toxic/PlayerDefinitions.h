#pragma once


UENUM(BlueprintType)
enum class  CharacterState: uint8
{
	Cs_Idle UMETA(DisplayName = "Idle"),
	Cs_Moving UMETA(DisplayName = "Moving"),
	Cs_Attacking UMETA(DisplayName = "Attacking"),
	Cs_Stunned UMETA(DisplayName = "Stunned"),
	Cs_Dead UMETA(DisplayName = "Dead"),
	Cs_Channeling UMETA(DisplayName = "Channeling")
};
