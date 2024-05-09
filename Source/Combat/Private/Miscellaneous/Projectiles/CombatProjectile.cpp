// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Miscellaneous/Projectiles/CombatProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystem.h"

ACombatProjectile::ACombatProjectile()
{
	// Default Variables
	ProjectileType = Linear;
	InitialProjectileSpeed = 3000.f;
	MaxProjectileSpeed = 3000.f;
	ProjectileSpeed = 3000.f;
	ProjectileDamage = 1.f;

	PrimaryActorTick.bCanEverTick = true;

	// Collision Component
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->InitSphereRadius(5.f);
	CollisionComponent->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACombatProjectile::OnComponentBeginOverlap);


	// Projectile Movement Component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->UpdatedComponent = CollisionComponent;
	ProjectileMovementComponent->InitialSpeed = InitialProjectileSpeed;
	ProjectileMovementComponent->MaxSpeed = MaxProjectileSpeed;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

#if WITH_EDITOR
void ACombatProjectile::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	ProjectileMovementComponent->InitialSpeed = InitialProjectileSpeed;
	ProjectileMovementComponent->MaxSpeed = MaxProjectileSpeed;
}
#endif

void ACombatProjectile::BeginPlay()
{
	Super::BeginPlay();

	LaunchProjectile();
}

void ACombatProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACombatProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedComponent == CollisionComponent)
	{
		if (OtherActor == GetOwner() || Cast<ACombatProjectile>(OtherActor)) return;

		ApplyDamage(SweepResult);
		SpawnHitEffect(SweepResult);
	}
}

void ACombatProjectile::ApplyDamage_Implementation(FHitResult HitResult)
{
	if (HitEffect == nullptr || HitResult.GetActor() == this || HitResult.GetActor() == GetOwner()) return;

	UGameplayStatics::ApplyPointDamage(
		HitResult.GetActor(),
		ProjectileDamage,
		-HitResult.ImpactNormal,
		HitResult,
		GetOwner()->GetInstigatorController(),
		GetOwner(),
		UDamageType::StaticClass()
	);
}

void ACombatProjectile::LaunchProjectile_Implementation()
{
	// Define in child classes
}

void ACombatProjectile::SpawnHitEffect_Implementation(FHitResult HitResult)
{
	if (HitEffect == nullptr || HitResult.GetActor() == this || HitResult.GetActor() == GetOwner()) return;

	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		HitEffect,
		FTransform(UKismetMathLibrary::MakeRotFromX(HitResult.Normal), HitResult.Location)
	);

	Destroy();
}