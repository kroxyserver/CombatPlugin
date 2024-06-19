// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CombatCharacterData.generated.h"

UCLASS()
class COMBAT_API UCombatCharacterData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|General")
	float EvadeLaunchVelocityPower = 2000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Capsule")
	float CapsuleHalfHeight = 90.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Capsule")
	float CapsuleRadius = 30.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Movement")
	float WalkSpeed = 250.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Movement")
	float SprintSpeed = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Mesh")
	USkeletalMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Mesh")
	FTransform MeshTransform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Animation")
	TSubclassOf<UAnimInstance> AnimationBlueprintClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Animation")
	UAnimMontage* SpawnMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Animation|Evade")
	UAnimMontage* EvadeForwardMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Animation|Evade")
	UAnimMontage* EvadeBackwardMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Animation|Evade")
	UAnimMontage* EvadeRightMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Animation|Evade")
	UAnimMontage* EvadeLeftMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Animation")
	UAnimMontage* BlockingMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Animation")
	TArray<UAnimMontage*> LightAttackMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Animation")
	TArray<UAnimMontage*> HeavyAttackMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Animation")
	UAnimMontage* AbilityMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|CharacterData|Animation")
	UAnimMontage* UltimateAbilityMontage;
};