// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Miscellaneous/Projectiles/CombatProjectile_Linear.h"

#include "GameFramework/ProjectileMovementComponent.h"

ACombatProjectile_Linear::ACombatProjectile_Linear()
{
	// Default Variables
	ProjectileType = Linear;
}

#if WITH_EDITOR
void ACombatProjectile_Linear::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void ACombatProjectile_Linear::LaunchProjectile_Implementation()
{
	if (ProjectileSpeed > 0.f) GetProjectileMovementComponent()->SetVelocityInLocalSpace(FVector::ForwardVector * ProjectileSpeed);
	else Destroy();
}