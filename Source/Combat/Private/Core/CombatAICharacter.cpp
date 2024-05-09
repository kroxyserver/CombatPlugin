// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Core/CombatAICharacter.h"

#include "Core/CombatAIController.h"

#include "GameFramework/CharacterMovementComponent.h"

ACombatAICharacter::ACombatAICharacter()
{
	// Default variables
	AIControllerClass = ACombatAIController::StaticClass();
	CurrentPhase = PhaseOne;
	LastPhase = PhaseOne;

	// Character Movement
	GetCharacterMovement()->bRequestedMoveUseAcceleration = true;
	//GetCharacterMovement()->bUseAccelerationForPathFollowing = true; // can only be set in blueprints so make sure to enable this boolean
}

void ACombatAICharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACombatAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

FHitResult ACombatAICharacter::GetHitResultFromLookAtRotation()
{
	//TODO: Define GetHitResultFromLookAtRotation in CombatAICharacter

	return FHitResult();
}

bool ACombatAICharacter::TransitionToNextPhase_Implementation()
{
	if (CurrentPhase == LastPhase) return false;

	CurrentPhase = static_cast<ECombat_Phase>(static_cast<int>(CurrentPhase) + 1);

	return true;
}