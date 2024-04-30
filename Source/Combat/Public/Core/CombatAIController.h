// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CombatAIController.generated.h"

class ACombatAICharacter;

UCLASS()
class COMBAT_API ACombatAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACombatAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

#pragma region Functions



#pragma endregion



#pragma region Variables

public:
	UPROPERTY(BlueprintReadOnly, Category = "+Combat|AIController")
	ACombatAICharacter* CombatAICharacter = nullptr;

#pragma endregion

};