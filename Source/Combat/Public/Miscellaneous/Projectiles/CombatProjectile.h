// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "CombatProjectile.generated.h"

class UParticleSystem;
class UProjectileMovementComponent;
class USphereComponent;

UENUM(BlueprintType)
enum ECombat_ProjectileType : uint8
{
	Linear			UMETA(DisplayName = "Linear"),
	Homing			UMETA(DisplayName = "Homing"),
	Arc				UMETA(DisplayName = "Arc")
};

UCLASS()
class COMBAT_API ACombatProjectile : public AActor
{
	GENERATED_BODY()

	/*Collision Component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Projectile", meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;

	/*Projectile Movement Component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Projectile", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovementComponent;

public:	
	ACombatProjectile();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	FORCEINLINE USphereComponent* GetcollisionComponent() const { return CollisionComponent; }
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

#pragma region Functions

public:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent, Category = "+Combat|Projectile")
	void LaunchProjectile();

	UFUNCTION(BlueprintNativeEvent, Category = "+Combat|Projectile")
	void SpawnHitEffect(FHitResult HitResult);

#pragma endregion

#pragma region Variables

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "+Combat|Projectile")
	TEnumAsByte<ECombat_ProjectileType> ProjectileType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|Projectile")
	float InitialProjectileSpeed;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|Projectile")
	float MaxProjectileSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|Projectile")
	float ProjectileSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|Projectile")
	UParticleSystem* HitEffect = nullptr;

#pragma endregion
};