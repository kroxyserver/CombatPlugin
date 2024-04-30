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

	GetCharacterMovement()->bRequestedMoveUseAcceleration = true;
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