// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Core/CombatAIController.h"

#include "Core/CombatAICharacter.h"
#include "Data/CombatCharacterData.h"

ACombatAIController::ACombatAIController()
{
}

void ACombatAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	CombatAICharacter = Cast<ACombatAICharacter>(InPawn);
	if (!CombatAICharacter) return;

	FTimerHandle TimerHandle_BehaviourTreeInitialDelay;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_BehaviourTreeInitialDelay,
		[this] { RunBehaviorTree(CombatAICharacter->BehaviourTree); },
		CombatAICharacter->CharacterData->SpawnMontage->GetPlayLength(),
		false
	);
}
