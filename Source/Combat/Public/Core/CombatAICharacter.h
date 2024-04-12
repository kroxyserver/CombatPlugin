// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/CombatCharacter.h"
#include "CombatAICharacter.generated.h"

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



#pragma endregion


#pragma region Variables



#pragma endregion
};