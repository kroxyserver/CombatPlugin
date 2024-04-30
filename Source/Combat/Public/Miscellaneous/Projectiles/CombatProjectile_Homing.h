// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Miscellaneous/Projectiles/CombatProjectile.h"
#include "CombatProjectile_Homing.generated.h"

UCLASS()
class COMBAT_API ACombatProjectile_Homing : public ACombatProjectile
{
	GENERATED_BODY()
	
public:
	ACombatProjectile_Homing();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void BeginPlay() override;

#pragma region Functions

public:
	virtual void LaunchProjectile_Implementation() override;

#pragma endregion

#pragma region Variables

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|Projectile")
	float HomingAccelerationMagnitude;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|Projectile")
	AActor* HomingTarget = nullptr;

#pragma endregion
};