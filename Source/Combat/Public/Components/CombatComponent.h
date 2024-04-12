// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class UCombatCharacterData;

UENUM(BlueprintType)
enum ECombat_AttackType : uint8
{
	None				UMETA(DisplayName = "NONE"),
	LightAttack			UMETA(DisplayName = "LightAttack"),
	HeavyAttack			UMETA(DisplayName = "HeavyAttack")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBAT_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

#pragma region Functions
public:
	void ComboSaveLightAttack();

	void ResetLightAttackCombo();

	void ComboSaveHeavyAttack();

	void ResetHeavyAttackCombo();

	UFUNCTION()
	void Evade();

	UFUNCTION()
	void Block_Start();

	UFUNCTION()
	void Block_Hold();

	UFUNCTION()
	void Block_Stop();

	UFUNCTION()
	void LightAttack_Start();

	UFUNCTION()
	void LightAttack_Hold();

	UFUNCTION()
	void LightAttack_Stop();

	void LightAttackAnimation();

	UFUNCTION()
	void HeavyAttack_Start();

	UFUNCTION()
	void HeavyAttack_Hold();

	UFUNCTION()
	void HeavyAttack_Stop();

	void HeavyAttackAnimation();

	UFUNCTION()
	void Ability_Start();

	UFUNCTION()
	void Ability_Hold();

	UFUNCTION()
	void Ability_Stop();

	void AbilityAnimation();

	UFUNCTION()
	void UltimateAbility_Start();

	UFUNCTION()
	void UltimateAbility_Hold();

	UFUNCTION()
	void UltimateAbility_Stop();

	void UltimateAbilityAnimation();

#pragma endregion



#pragma region Variables

public:
	UPROPERTY(BlueprintReadOnly, Category = "+Combat|References")
	UCombatCharacterData* CharacterData = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|References")
	ACharacter* OwningCharacterRef = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat")
	float AttackSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat")
	bool bCanBlock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat")
	bool bIsBlocking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat")
	bool bIsStaggered;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|LightAttack")
	bool bIsPerformingLightAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|LightAttack")
	bool bSaveLightAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|LightAttack")
	int32 LightAttackCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|HeavyAttack")
	bool bIsPerformingHeavyAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|HeavyAttack")
	bool bSaveHeavyAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|HeavyAttack")
	int32 HeavyAttackCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Ability")
	bool bIsAbilityBeingUsed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Ability")
	bool bIsAbilityOnCooldown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|UltimateAbility")
	bool bIsUltimateAbilityBeingUsed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|UltimateAbility")
	bool bIsUltimateAbilityOnCooldown;

#pragma endregion
};