// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class ACombatPlayerController;
class UCombatCharacterData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetCanMove, bool, bTrue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayLightAttackAnimation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayHeavyAttackAnimation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayAbilityAnimation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayUltimateAbilityAnimation);

UENUM(BlueprintType)
enum ECombat_AttackType : uint8
{
	None				UMETA(DisplayName = "NONE"),
	LightAttack			UMETA(DisplayName = "LightAttack"),
	HeavyAttack			UMETA(DisplayName = "HeavyAttack"),
	Ability				UMETA(DisplayName = "Ability"),
	UltimateAbility		UMETA(DisplayName = "UltimateAbility")
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

	void SetIsEvading(bool bTrue);

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

	UFUNCTION(BlueprintCallable, Category = "+Combat")
	float LightAttackAnimation(FName SectionName = NAME_None);

	UFUNCTION()
	void HeavyAttack_Start();

	UFUNCTION()
	void HeavyAttack_Hold();

	UFUNCTION()
	void HeavyAttack_Stop();

	UFUNCTION(BlueprintCallable, Category = "+Combat")
	float HeavyAttackAnimation(FName SectionName = NAME_None);

	UFUNCTION()
	void Ability_Start();

	UFUNCTION()
	void Ability_Hold();

	UFUNCTION()
	void Ability_Stop();

	UFUNCTION(BlueprintCallable, Category = "+Combat")
	float AbilityAnimation(FName SectionName = NAME_None);

	UFUNCTION()
	void UltimateAbility_Start();

	UFUNCTION()
	void UltimateAbility_Hold();

	UFUNCTION()
	void UltimateAbility_Stop();

	UFUNCTION(BlueprintCallable, Category = "+Combat")
	float UltimateAbilityAnimation(FName SectionName = NAME_None);

	/*All probabilities should be between 0 and 1*/
	UFUNCTION(BlueprintCallable, Category = "Combat")
	ECombat_AttackType GetRandomAttackType(float LightAttackProbability, float HeavyAttackProbability, float AbilityProbability, float UltimateAbilityProbability) const;


#pragma endregion



#pragma region Variables

public:
	UPROPERTY(BlueprintReadOnly, Category = "+Combat|References")
	UCombatCharacterData* CharacterData = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|References")
	ACharacter* OwningCharacterRef = nullptr;

	UPROPERTY(BlueprintAssignable, Category = "+Combat")
	FSetCanMove SetCanMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat")
	float AttackSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat")
	bool bCanBlock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat")
	bool bIsBlocking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat")
	bool bIsEvading;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat")
	bool bIsStaggered;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|LightAttack")
	bool bIsPerformingLightAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|LightAttack")
	bool bSaveLightAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|LightAttack")
	int32 LightAttackCount;

	UPROPERTY(BlueprintAssignable, Category = "+Combat|LightAttack")
	FOnPlayLightAttackAnimation OnPlayLightAttackAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|HeavyAttack")
	bool bIsPerformingHeavyAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|HeavyAttack")
	bool bSaveHeavyAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|HeavyAttack")
	int32 HeavyAttackCount;

	UPROPERTY(BlueprintAssignable, Category = "+Combat|HeavyAttack")
	FOnPlayHeavyAttackAnimation OnPlayHeavyAttackAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Ability")
	bool bIsAbilityBeingUsed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Ability")
	bool bIsAbilityOnCooldown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|Ability")
	float AbilityCooldown;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|Ability")
	FTimerHandle TimerHandle_AbilityCooldown;

	UPROPERTY(BlueprintAssignable, Category = "+Combat|Ability")
	FOnPlayAbilityAnimation OnPlayAbilityAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|UltimateAbility")
	bool bIsUltimateAbilityBeingUsed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|UltimateAbility")
	bool bIsUltimateAbilityOnCooldown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|UltimateAbility")
	float UltimateAbilityCooldown;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|UltimateAbility")
	FTimerHandle TimerHandle_UltimateAbilityCooldown;

	UPROPERTY(BlueprintAssignable, Category = "+Combat|UltimateAbility")
	FOnPlayUltimateAbilityAnimation OnPlayUltimateAbilityAnimation;

#pragma endregion
};