// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/CombatComponent.h"
#include "Core/CombatCharacter.h"

#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "CombatAnimNotify_SpawnProjectile.generated.h"

class UCombatSubsystem;

UCLASS()
class COMBAT_API UCombatAnimNotify_SpawnProjectile : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()

public:
	UCombatAnimNotify_SpawnProjectile();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	virtual void BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload) override;

#pragma region Functions

public:
	virtual void SpawnProjectile();

#pragma endregion

#pragma region Variables

public:
	UPROPERTY(BlueprintReadOnly, Category = "+Combat|References")
	UCombatSubsystem* CombatSubsystem;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|References")
	ACombatCharacter* CombatCharacter;

	UPROPERTY(EditAnywhere, Category = "+Combat", meta = (AllowedClasses = "/Script/Combat.CombatProjectile"))
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "+Combat")
	ECombat_AttackType AttackType;

	UPROPERTY(EditAnywhere, Category = "+Combat")
	ECombat_ProjectileSpawnPointType HandType;

#pragma endregion
};