// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Miscellaneous/Projectiles/CombatProjectile_Homing.h"

#include "GameFramework/ProjectileMovementComponent.h"

ACombatProjectile_Homing::ACombatProjectile_Homing()
{
	// Default variables
	ProjectileType = ECombat_ProjectileType::Homing;
	HomingAccelerationMagnitude = 1000.f;

	// Projectile Movement Component
	GetProjectileMovementComponent()->bInitialVelocityInLocalSpace = true;
	GetProjectileMovementComponent()->bIsHomingProjectile = true;
	GetProjectileMovementComponent()->HomingAccelerationMagnitude = HomingAccelerationMagnitude;
}

#if WITH_EDITOR
void ACombatProjectile_Homing::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	GetProjectileMovementComponent()->HomingAccelerationMagnitude = HomingAccelerationMagnitude;
}
#endif

void ACombatProjectile_Homing::BeginPlay()
{
	Super::BeginPlay();
}

void ACombatProjectile_Homing::LaunchProjectile_Implementation()
{
	if (HomingTarget)
	{
		GetProjectileMovementComponent()->HomingTargetComponent = HomingTarget->GetRootComponent();
	}
	else
	{
		GetProjectileMovementComponent()->bIsHomingProjectile = false;
		GetProjectileMovementComponent()->SetVelocityInLocalSpace(FVector::ForwardVector * ProjectileSpeed);
	}
}