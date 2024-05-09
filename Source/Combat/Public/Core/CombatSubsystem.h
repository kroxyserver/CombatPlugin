// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CombatSubsystem.generated.h"

class ACombatCharacter;

UCLASS()
class COMBAT_API UCombatSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
#pragma region Functions

public:
	UFUNCTION(BlueprintCallable, Category = "+Combat|Subsystem")
	void SpawnProjectile(ACombatCharacter* CombatCharacter, TSubclassOf<AActor> ProjectileClass, TEnumAsByte<ECombat_AttackType> AttackType, TEnumAsByte<ECombat_ProjectileSpawnPointType> HandType);

#pragma endregion

#pragma region Variables



#pragma endregion

};