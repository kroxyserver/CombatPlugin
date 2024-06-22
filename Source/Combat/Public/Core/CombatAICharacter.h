// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/CombatCharacter.h"
#include "CombatAICharacter.generated.h"

class UBehaviorTree;

UENUM(BlueprintType)
enum class ECombat_Phase : uint8
{
	PhaseOne		UMETA(DisplayName = "PhaseOne"),
	PhaseTwo		UMETA(DisplayName = "PhaseTwo"),
	PhaseThree		UMETA(DisplayName = "PhaseThree"),
	PhaseFour		UMETA(DisplayName = "PhaseFour"),
	PhaseFive		UMETA(DisplayName = "PhaseFive"),
	PhaseSix		UMETA(DisplayName = "PhaseSix"),
	PhaseSeven		UMETA(DisplayName = "PhaseSeven"),
	PhaseEight		UMETA(DisplayName = "PhaseEight"),
	PhaseNine		UMETA(DisplayName = "PhaseNine")
};

UCLASS()
class COMBAT_API ACombatAICharacter : public ACombatCharacter
{
	GENERATED_BODY()
	
public:
	ACombatAICharacter();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

#pragma region Functions

public:
	virtual FHitResult GetHitResultFromLookAtRotation() override;

	/*Returns true if Current phase is not the last phase, false otherwise*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "+Combat|AICharacter")
	bool TransitionToNextPhase();

#pragma endregion


#pragma region Variables

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|AICharacter")
	UBehaviorTree* BehaviourTree = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "+Combat|AICharacter")
	ECombat_Phase CurrentPhase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|AICharacter")
	ECombat_Phase LastPhase;

#pragma endregion
};