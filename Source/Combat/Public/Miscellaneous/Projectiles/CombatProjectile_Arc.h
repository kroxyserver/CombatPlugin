// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Miscellaneous/Projectiles/CombatProjectile.h"
#include "CombatProjectile_Arc.generated.h"

UCLASS()
class COMBAT_API ACombatProjectile_Arc : public ACombatProjectile
{
	GENERATED_BODY()
	
public:
	ACombatProjectile_Arc();

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
	// Between 0-1, Closer to 0 = Higher Arc & Closer to 1 = Lower Arc
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|Projectile", meta = (ClampMin = 0.f, ClampMax = 1.f, UIMin = 0.f, UIMax = 1.f))
	float ArcParam = .8f;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|Projectile")
	FVector LaunchVelocity;

#pragma endregion
};