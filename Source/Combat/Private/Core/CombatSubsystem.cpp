// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Core/CombatSubsystem.h"

#include "Core/CombatCharacter.h"
#include "Miscellaneous/Projectiles/CombatProjectile.h"
#include "Miscellaneous/Projectiles/CombatProjectile_Arc.h"
#include "Miscellaneous/Projectiles/CombatProjectile_Homing.h"
#include "Miscellaneous/Projectiles/CombatProjectile_Linear.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UCombatSubsystem::SpawnProjectile(ACombatCharacter* CombatCharacter, TSubclassOf<AActor> ProjectileClass, TEnumAsByte<ECombat_AttackType> AttackType, TEnumAsByte<ECombat_HandType> HandType)
{
	FTransform SpawnTransform = FTransform();
	ACombatProjectile_Homing* HomingProjectile;
	ACombatProjectile_Arc* ArcProjectile;

	ACombatProjectile* Projectile = Cast<ACombatProjectile>(UGameplayStatics::BeginDeferredActorSpawnFromClass(
		CombatCharacter,
		ProjectileClass,
		SpawnTransform,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
		CombatCharacter
	));

	if (Projectile)
	{
		USceneComponent* ProjectileSpawnPoint = CombatCharacter->GetProjectileSpawnPoint(AttackType, HandType);
		FHitResult HitResult = CombatCharacter->GetHitResultFromLookAtRotation();

		// Override SpawnTransform if needed based on ProjectileType
		SpawnTransform.SetLocation(ProjectileSpawnPoint->GetComponentLocation());
		SpawnTransform.SetRotation(FQuat(ProjectileSpawnPoint->GetComponentRotation()));

		switch (Projectile->ProjectileType)
		{
		case Linear:
			SpawnTransform.SetRotation(FQuat(UKismetMathLibrary::FindLookAtRotation(SpawnTransform.GetLocation(), HitResult.Location)));
			break;

		case Homing:
			HomingProjectile = Cast<ACombatProjectile_Homing>(Projectile);
			if (HomingProjectile)
			{
				HomingProjectile->HomingTarget = HitResult.GetActor();
			}
			break;

		case Arc:
			ArcProjectile = Cast<ACombatProjectile_Arc>(Projectile);
			if (ArcProjectile)
			{
				FVector LaunchVelocity;
				UGameplayStatics::SuggestProjectileVelocity_CustomArc(
					CombatCharacter,
					LaunchVelocity,
					ProjectileSpawnPoint->GetComponentLocation(),
					HitResult.Location,
					0.f,
					ArcProjectile->ArcParam
				);

				ArcProjectile->LaunchVelocity = LaunchVelocity;
			}
			break;

		default:
			break;
		}

		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
	}
}