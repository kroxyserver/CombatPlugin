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
	UPROPERTY(EditDefaultsOnly, Category = "+Combat|CharacterData|Capsule")
	float CapsuleHalfHeight;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|CharacterData|Capsule")
	float CapsuleRadius;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|CharacterData|Mesh")
	USkeletalMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|CharacterData|Mesh")
	FTransform MeshTransform;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|CharacterData|Animation")
	UAnimBlueprint* AnimationBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|CharacterData|Animation")
	UAnimMontage* BlockingMontage;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|CharacterData|Animation")
	TArray<UAnimMontage*> LightAttackMontages;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|CharacterData|Animation")
	TArray<UAnimMontage*> HeavyAttackMontages;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|CharacterData|Animation")
	UAnimMontage* AbilityMontage;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|CharacterData|Animation")
	UAnimMontage* UltimateAbilityMontage;
};