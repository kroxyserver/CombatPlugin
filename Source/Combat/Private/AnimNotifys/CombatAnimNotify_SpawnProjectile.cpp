// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "AnimNotifys/CombatAnimNotify_SpawnProjectile.h"

#include "Core/CombatCharacter.h"
#include "Core/CombatSubsystem.h"
#include "Miscellaneous/Projectiles/CombatProjectile.h"

#include "Kismet/GameplayStatics.h"

UCombatAnimNotify_SpawnProjectile::UCombatAnimNotify_SpawnProjectile()
{
	NotifyName = "Specify Attack Type";
	ProjectileClass = ACombatProjectile::StaticClass();
	AttackType = ECombat_AttackType::None;
	HandType = ECombat_HandType::Left;
}

#if WITH_EDITOR
void UCombatAnimNotify_SpawnProjectile::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	switch (AttackType)
	{
		case None:
			NotifyName = "Specify Attack Type";
			break;
		case LightAttack:
			NotifyName = (HandType == Left) ? "Spawn Projectile Light Attack Left" : "Spawn Projectile Light Attack Right";
			break;
		case HeavyAttack:
			NotifyName = (HandType == Left) ? "Spawn Projectile Heavy Attack Left" : "Spawn Projectile Heavy Attack Right";
			break;
		case Ability:
			NotifyName = (HandType == Left) ? "Spawn Projectile Ability Left" : "Spawn Projectile Ability Right";
			break;
		case UltimateAbility:
			NotifyName = (HandType == Left) ? "Spawn Projectile Ultimate Ability Left" : "Spawn Projectile Ultimate Ability Right";
			break;
		default:
			break;
	}
}
#endif

void UCombatAnimNotify_SpawnProjectile::BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotify(BranchingPointPayload);

	CombatCharacter = Cast<ACombatCharacter>(BranchingPointPayload.SkelMeshComponent->GetOwner());
	if (!CombatCharacter) return;

	CombatSubsystem = UGameplayStatics::GetGameInstance(CombatCharacter)->GetSubsystem<UCombatSubsystem>();
	if (!CombatSubsystem) return;

	SpawnProjectile();
}

void UCombatAnimNotify_SpawnProjectile::SpawnProjectile()
{
	CombatSubsystem->SpawnProjectile(CombatCharacter, ProjectileClass, AttackType, HandType);
}