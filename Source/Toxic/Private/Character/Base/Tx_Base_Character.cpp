// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Base/Tx_Base_Character.h"


#include "Character/Tx_Base_AICharacterCtr.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATx_Base_Character::ATx_Base_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NetUpdateFrequency = 66.f;
	MinNetUpdateFrequency = 33.f;

	CurrentCharacterState = CharacterState::Cs_Idle;

}

void ATx_Base_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATx_Base_Character,CurrentCharacterState);
}


// Called when the game starts or when spawned
void ATx_Base_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATx_Base_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATx_Base_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATx_Base_Character::OnRep_CharacterState(CharacterState LastState)
{
	
/**	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		FString::Printf(TEXT("Change state Character : x: %s"),*this->GetName() ));*/
	
	
}
