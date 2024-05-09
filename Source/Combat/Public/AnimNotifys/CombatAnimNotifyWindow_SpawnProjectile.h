// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/CombatComponent.h"

#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "CombatAnimNotifyWindow_SpawnProjectile.generated.h"

class ACombatCharacter;
class UCombatSubsystem;

UCLASS()
class COMBAT_API UCombatAnimNotifyWindow_SpawnProjectile : public UAnimNotify_PlayMontageNotifyWindow
{
	GENERATED_BODY()
	
public:
	UCombatAnimNotifyWindow_SpawnProjectile();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	virtual void BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload) override;
	
	virtual void BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload) override;

#pragma region Functions

	void StartSpawningProjectiles();

	void StopSpawningProjectiles();

#pragma endregion

#pragma region Variables

public:
	FTimerHandle TimerHandle_SpawnProjectile;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|References")
	UCombatSubsystem* CombatSubsystem;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|References")
	ACombatCharacter* CombatCharacter;

	UPROPERTY(EditAnywhere, Category = "+Combat", meta = (AllowedClasses = "/Script/Combat.CombatProjectile"))
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "+Combat")
	TEnumAsByte<ECombat_AttackType> AttackType;

	UPROPERTY(EditAnywhere, Category = "+Combat")
	TEnumAsByte<ECombat_ProjectileSpawnPointType> HandType;

	UPROPERTY(EditAnywhere, Category = "+Combat")
	float DelayBetweenProjectileSpawns;

	UPROPERTY(EditAnywhere, Category = "+Combat")
	float InitialDelay;

#pragma endregion
};