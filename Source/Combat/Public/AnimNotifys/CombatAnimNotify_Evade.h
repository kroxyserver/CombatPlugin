// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "CombatAnimNotify_Evade.generated.h"

UCLASS()
class COMBAT_API UCombatAnimNotify_Evade : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()
	
#pragma region Functions

public:
	UCombatAnimNotify_Evade();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	virtual void BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload) override;

#pragma endregion



#pragma region Variables



#pragma endregion
};