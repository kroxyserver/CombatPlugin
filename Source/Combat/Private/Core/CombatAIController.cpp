// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Core/CombatAIController.h"

#include "Core/CombatAICharacter.h"

ACombatAIController::ACombatAIController()
{
}

void ACombatAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	CombatAICharacter = Cast<ACombatAICharacter>(InPawn);
	if (!CombatAICharacter) return;

	RunBehaviorTree(CombatAICharacter->BehaviourTree);
}
