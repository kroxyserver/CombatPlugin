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
	HandType = ECombat_ProjectileSpawnPointType::Default;
}

#if WITH_EDITOR
void UCombatAnimNotify_SpawnProjectile::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	switch (AttackType)
	{
		case ECombat_AttackType::None:
			NotifyName = "Specify Attack Type";
			break;
		case ECombat_AttackType::LightAttack:
			NotifyName = (HandType == ECombat_ProjectileSpawnPointType::Default) ? "Spawn Projectile Light Attack" : (HandType == ECombat_ProjectileSpawnPointType::Left) ? "Spawn Projectile Light Attack Left" : "Spawn Projectile Light Attack Right";
			break;
		case ECombat_AttackType::HeavyAttack:
			NotifyName = (HandType == ECombat_ProjectileSpawnPointType::Default) ? "Spawn Projectile Heavy Attack" : (HandType == ECombat_ProjectileSpawnPointType::Left) ? "Spawn Projectile Heavy Attack Left" : "Spawn Projectile Heavy Attack Right";
			break;
		case ECombat_AttackType::Ability:
			NotifyName = (HandType == ECombat_ProjectileSpawnPointType::Default) ? "Spawn Projectile Ability" : (HandType == ECombat_ProjectileSpawnPointType::Left) ? "Spawn Projectile Ability Left" : "Spawn Projectile Ability Right";
			break;
		case ECombat_AttackType::UltimateAbility:
			NotifyName = (HandType == ECombat_ProjectileSpawnPointType::Default) ? "Spawn Projectile Ultimate Ability" : (HandType == ECombat_ProjectileSpawnPointType::Left) ? "Spawn Projectile Ultimate Ability Left" : "Spawn Projectile Ultimate Ability Right";
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