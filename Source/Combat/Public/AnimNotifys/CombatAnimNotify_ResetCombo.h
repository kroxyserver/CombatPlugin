// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/CombatComponent.h"

#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"

#include "CombatAnimNotify_ResetCombo.generated.h"

UCLASS()
class COMBAT_API UCombatAnimNotify_ResetCombo : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()
	
#pragma region Functions

public:
	UCombatAnimNotify_ResetCombo();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	virtual void BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload) override;

#pragma endregion



#pragma region Variables

public:
	UPROPERTY(EditAnywhere, Category = "+Combat")
	ECombat_AttackType AttackType;

#pragma endregion
};