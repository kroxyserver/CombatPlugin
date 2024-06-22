// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Miscellaneous/Projectiles/CombatProjectile_Arc.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

ACombatProjectile_Arc::ACombatProjectile_Arc()
{
	// Default variables
	ProjectileType = ECombat_ProjectileType::Arc;

	GetProjectileMovementComponent()->bRotationRemainsVertical = true;
	GetProjectileMovementComponent()->ProjectileGravityScale = 1.f;
}

#if WITH_EDITOR
void ACombatProjectile_Arc::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void ACombatProjectile_Arc::BeginPlay()
{
	Super::BeginPlay();
}

void ACombatProjectile_Arc::LaunchProjectile_Implementation()
{
	GetProjectileMovementComponent()->Velocity = LaunchVelocity;
}