// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/CombatCharacter.h"
#include "CombatPlayerCharacter.generated.h"

class ACombatPlayerController;

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class COMBAT_API ACombatPlayerCharacter : public ACombatCharacter
{
	GENERATED_BODY()

	/*Spring Arm Component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|PlayerCharacter", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	/*Camera Component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|PlayerCharacter", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

public:
	ACombatPlayerCharacter();

	FORCEINLINE class USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

#pragma region Functions



#pragma endregion


#pragma region Variables

public:
	UPROPERTY(BlueprintReadOnly, Category = "+Combat|PlayerCharacter|References")
	ACombatPlayerController* PlayerControllerRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|PlayerCharacter")
	float MinTargetArmLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|PlayerCharacter")
	float MaxTargetArmLength;

#pragma endregion
};