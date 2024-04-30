// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CombatPlayerInputData.generated.h"

class UInputAction;
class UInputMappingContext;

UENUM(BlueprintType)
enum ECombat_InputType : uint8
{
	Press				UMETA(DisplayName = "Press"),
	Hold				UMETA(DisplayName = "Hold"),
	Release				UMETA(DisplayName = "Release"),
	PressAndHold		UMETA(DisplayName = "Press & Hold"),
	PressAndRelease		UMETA(DisplayName = "Press & Release"),
	HoldAndRelease		UMETA(DisplayName = "Hold & Release"),
	PressHoldRelease	UMETA(DisplayName = "Press, Hold & Release")
};

USTRUCT(BlueprintType)
struct FCombat_InputActionAndType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* InputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ECombat_InputType> InputType;

	bool IsValid() const { return InputAction != nullptr; }
};

UCLASS()
class COMBAT_API UCombatPlayerInputData : public UDataAsset
{
	GENERATED_BODY()

public:
	UCombatPlayerInputData();

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|PlayerInputData")
	UInputMappingContext* CombatPlayerInputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|PlayerInputData")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|PlayerInputData")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|PlayerInputData")
	UInputAction* EvadeAction;




	UPROPERTY(EditDefaultsOnly, Category = "+Combat|PlayerInputData")
	FCombat_InputActionAndType BlockAction;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|PlayerInputData")
	FCombat_InputActionAndType LightAttackAction;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|PlayerInputData")
	FCombat_InputActionAndType HeavyAttackAction;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|PlayerInputData")
	FCombat_InputActionAndType AbilityAction;

	UPROPERTY(EditDefaultsOnly, Category = "+Combat|PlayerInputData")
	FCombat_InputActionAndType UltimateAbilityAction;
};