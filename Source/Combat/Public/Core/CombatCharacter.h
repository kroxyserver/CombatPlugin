// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/CombatComponent.h"

#include "GameFramework/Character.h"
#include "CombatCharacter.generated.h"

class UCombatCharacterData;

UENUM(BlueprintType)
enum class ECombat_ProjectileSpawnPointType : uint8
{
	Default		UMETA(DisplayName = "Default"),
	Left		UMETA(DisplayName = "Left"),
	Right		UMETA(DisplayName = "Right")
};

UCLASS()
class COMBAT_API ACombatCharacter : public ACharacter
{
	GENERATED_BODY()

	/*Combat Component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Character", meta = (AllowPrivateAccess = "true"))
	UCombatComponent* CombatComponent;

	/*Projectile Spawn Point Light Attack*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Character", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint_LightAttack;

	/*Projectile Spawn Point Light Attack Left*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Character", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint_LightAttack_Left;

	/*Projectile Spawn Point Light Attack Right*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Character", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint_LightAttack_Right;

	/*Projectile Spawn Point Heavy Attack*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Character", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint_HeavyAttack;

	/*Projectile Spawn Point Heavy Attack Left*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Character", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint_HeavyAttack_Left;

	/*Projectile Spawn Point Heavy Attack Right*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Character", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint_HeavyAttack_Right;

	/*Projectile Spawn Point Ability*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Character", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint_Ability;

	/*Projectile Spawn Point Ability Left*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Character", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint_Ability_Left;

	/*Projectile Spawn Point Ability Right*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Character", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint_Ability_Right;

	/*Projectile Spawn Point Ultimate Ability*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Character", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint_UltimateAbility;

	/*Projectile Spawn Point Ultimate Ability Left*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Character", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint_UltimateAbility_Left;

	/*Projectile Spawn Point Ultimate Ability Right*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Character", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint_UltimateAbility_Right;

public:
	ACombatCharacter();

	FORCEINLINE UCombatComponent* GetCombatComponent() const { return CombatComponent; }

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

#pragma region Functions

public:
	UFUNCTION(BlueprintCallable, Category = "+Combat|Character")
	virtual void UpdateCharacterData(UCombatCharacterData* NewCharacterData);
	
	UFUNCTION(BlueprintCallable, Category = "+Combat|Character")
	USceneComponent* GetProjectileSpawnPoint(ECombat_AttackType AttackType, ECombat_ProjectileSpawnPointType HandType);

	UFUNCTION(BlueprintCallable, Category = "+Combat|Character")
	virtual FHitResult GetHitResultFromLookAtRotation();

#pragma endregion

#pragma region Variables

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|Character|References")
	UCombatCharacterData* CharacterData = nullptr;

#pragma endregion
};