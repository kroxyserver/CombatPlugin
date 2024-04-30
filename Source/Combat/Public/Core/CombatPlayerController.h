// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Data/CombatPlayerInputData.h"

#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "CombatPlayerController.generated.h"

class UCombatComponent;

class UEnhancedInputComponent;
class UInputAction;
class UInputMappingContext;

DECLARE_DYNAMIC_DELEGATE(FOnEvade);
DECLARE_DYNAMIC_DELEGATE(FOnBlock_Start);
DECLARE_DYNAMIC_DELEGATE(FOnBlock_Hold);
DECLARE_DYNAMIC_DELEGATE(FOnBlock_Stop);
DECLARE_DYNAMIC_DELEGATE(FOnLightAttack_Start);
DECLARE_DYNAMIC_DELEGATE(FOnLightAttack_Hold);
DECLARE_DYNAMIC_DELEGATE(FOnLightAttack_Stop);
DECLARE_DYNAMIC_DELEGATE(FOnHeavyAttack_Start);
DECLARE_DYNAMIC_DELEGATE(FOnHeavyAttack_Hold);
DECLARE_DYNAMIC_DELEGATE(FOnHeavyAttack_Stop);
DECLARE_DYNAMIC_DELEGATE(FOnUseAbility_Start);
DECLARE_DYNAMIC_DELEGATE(FOnUseAbility_Hold);
DECLARE_DYNAMIC_DELEGATE(FOnUseAbility_Stop);
DECLARE_DYNAMIC_DELEGATE(FOnUseUltimateAbility_Start);
DECLARE_DYNAMIC_DELEGATE(FOnUseUltimateAbility_Hold);
DECLARE_DYNAMIC_DELEGATE(FOnUseUltimateAbility_Stop);

UCLASS()
class COMBAT_API ACombatPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACombatPlayerController();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

#pragma region Functions

protected:
	virtual void Move(const FInputActionValue& Value);

	virtual void Look(const FInputActionValue& Value);

	virtual void Evade(const FInputActionValue& Value);
	
	virtual void Block_Start(const FInputActionValue& Value);

	virtual void Block_Hold(const FInputActionValue& Value);

	virtual void Block_Stop(const FInputActionValue& Value);

	virtual void LightAttack_Start(const FInputActionValue& Value);

	virtual void LightAttack_Hold(const FInputActionValue& Value);

	virtual void LightAttack_Stop(const FInputActionValue& Value);

	virtual void HeavyAttack_Start(const FInputActionValue& Value);

	virtual void HeavyAttack_Hold(const FInputActionValue& Value);

	virtual void HeavyAttack_Stop(const FInputActionValue& Value);
	
	virtual void Ability_Start(const FInputActionValue& Value);

	virtual void Ability_Hold(const FInputActionValue& Value);

	virtual void Ability_Stop(const FInputActionValue& Value);

	virtual void UltimateAbility_Start(const FInputActionValue& Value);

	virtual void UltimateAbility_Hold(const FInputActionValue& Value);

	virtual void UltimateAbility_Stop(const FInputActionValue& Value);

public:
	void BindInputToCombatComponent(UCombatComponent* CombatComponent);

	UFUNCTION(BlueprintCallable, Category = "+Combat|PlayerController")
	void EnableMovement(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "+Combat|PlayerController")
	void UpdatePlayerInputData(UCombatPlayerInputData* NewPlayerInputData);

//private:
//	void BindInputAction(
//		UEnhancedInputComponent* EnhancedInputComponent,
//		FCombat_InputActionAndType InputActionAndType,
//		void(ACombatPlayerController::*BindToFunction)(const FInputActionValue&)
//	) {}

#pragma endregion



#pragma region Variables

public:
	/*Player Input Data*/
	UPROPERTY(EditDefaultsOnly, Category = "+Combat|PlayerController|Input")
	UCombatPlayerInputData* CombatPlayerInputData;

	
	/*Mapping Context*/
	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Input")
	UInputMappingContext* DefaultMappingContext;

	
	/*Input Actions*/
	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Input")
	UInputAction* MoveAction;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Input")
	UInputAction* LookAction;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Input")
	UInputAction* EvadeAction;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Input")
	FCombat_InputActionAndType BlockAction;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Input")
	FCombat_InputActionAndType LightAttackAction;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Input")
	FCombat_InputActionAndType HeavyAttackAction;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Input")
	FCombat_InputActionAndType AbilityAction;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Input")
	FCombat_InputActionAndType UltimateAbilityAction;



	/* Delegates */
	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|Evade")
	FOnEvade OnEvade;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|Block")
	FOnBlock_Start OnBlock_Start;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|Block")
	FOnBlock_Hold OnBlock_Hold;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|Block")
	FOnBlock_Stop OnBlock_Stop;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|LightAttack")
	FOnLightAttack_Start OnLightAttack_Start;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|LightAttack")
	FOnLightAttack_Hold OnLightAttack_Hold;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|LightAttack")
	FOnLightAttack_Stop OnLightAttack_Stop;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|HeavyAttack")
	FOnHeavyAttack_Start OnHeavyAttack_Start;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|HeavyAttack")
	FOnHeavyAttack_Hold OnHeavyAttack_Hold;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|HeavyAttack")
	FOnHeavyAttack_Stop OnHeavyAttack_Stop;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|Ability")
	FOnUseAbility_Start OnUseAbility_Start;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|Ability")
	FOnUseAbility_Hold OnUseAbility_Hold;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|Ability")
	FOnUseAbility_Stop OnUseAbility_Stop;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|UltimateAbility")
	FOnUseUltimateAbility_Start OnUseUltimateAbility_Start;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|UltimateAbility")
	FOnUseUltimateAbility_Hold OnUseUltimateAbility_Hold;

	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerController|Delegates|UltimateAbility")
	FOnUseUltimateAbility_Stop OnUseUltimateAbility_Stop;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|PlayerController")
	uint8 bCanMove : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|PlayerController")
	float BaseLookupRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|PlayerController")
	float BaseTurnRate;

#pragma endregion
};