// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Miscellaneous/Projectiles/CombatProjectile.h"
#include "CombatProjectile_Linear.generated.h"

UCLASS()
class COMBAT_API ACombatProjectile_Linear : public ACombatProjectile
{
	GENERATED_BODY()

public:
	ACombatProjectile_Linear();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

#pragma region Functions

public:
	virtual void LaunchProjectile_Implementation() override;

#pragma endregion

#pragma region Variables



#pragma endregion
};