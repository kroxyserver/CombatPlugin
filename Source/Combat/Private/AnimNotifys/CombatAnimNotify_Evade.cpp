// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "AnimNotifys/CombatAnimNotify_Evade.h"

#include "Core/CombatCharacter.h"
#include "Data/CombatCharacterData.h"

#include "Kismet/KismetMathLibrary.h"

UCombatAnimNotify_Evade::UCombatAnimNotify_Evade()
{
	NotifyName = "Evade";
}

#if WITH_EDITOR
void UCombatAnimNotify_Evade::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void UCombatAnimNotify_Evade::BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotify(BranchingPointPayload);

	ACombatCharacter* CombatCharacter = Cast<ACombatCharacter>(BranchingPointPayload.SkelMeshComponent->GetOwner());
	if (!CombatCharacter) return;

	if (CombatCharacter->CharacterData == nullptr) return;

	FVector NormalizedVelocity = UKismetMathLibrary::Vector_NormalUnsafe(CombatCharacter->GetVelocity());
	FVector LaunchVelocity = UKismetMathLibrary::Multiply_VectorFloat(NormalizedVelocity, CombatCharacter->CharacterData->EvadeLaunchVelocityPower);

	CombatCharacter->LaunchCharacter(LaunchVelocity, true, true);
}