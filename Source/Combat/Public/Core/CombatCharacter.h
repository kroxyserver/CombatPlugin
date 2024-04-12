// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CombatCharacter.generated.h"

class UCombatComponent;
class UCombatCharacterData;

UCLASS()
class COMBAT_API ACombatCharacter : public ACharacter
{
	GENERATED_BODY()

	/*Combat Component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "+Combat|Character", meta = (AllowPrivateAccess = "true"))
	UCombatComponent* CombatComponent;

public:
	ACombatCharacter();

	FORCEINLINE class UCombatComponent* GetCombatComponent() const { return CombatComponent; }

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

#pragma region Functions

public:
	UFUNCTION(BlueprintCallable, Category = "+Combat|Character")
	virtual void UpdateCharacterData(UCombatCharacterData* NewCharacterData);

#pragma endregion

#pragma region Variables

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "+Combat|Character|References")
	UCombatCharacterData* CharacterData;

#pragma endregion
};