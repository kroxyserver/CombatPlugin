// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Components/CombatComponent.h"

#include "Data/CombatCharacterData.h"

#include "GameFramework/Character.h"

#define IsAnAbilityBeingUsed bIsAbilityBeingUsed || bIsUltimateAbilityBeingUsed

UCombatComponent::UCombatComponent()
{
	// Default variable values
	AttackSpeed = 1.f;
	bCanBlock = true;
	bIsBlocking = false;
	bIsStaggered = false;

	bIsPerformingLightAttack = false;
	LightAttackCount = 0;
	bSaveLightAttack = false;

	bIsPerformingHeavyAttack = false;
	HeavyAttackCount = 0;
	bSaveHeavyAttack = false;

	bIsAbilityBeingUsed = false;
	bIsAbilityOnCooldown = false;
	bIsUltimateAbilityBeingUsed = false;
	bIsUltimateAbilityOnCooldown = false;
	
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningCharacterRef = Cast<ACharacter>(GetOwner());
	if (!OwningCharacterRef) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.f, FColor::Red, "OwningCharacterRef invalid. CombatComponent.cpp, BeginPlay()");
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComponent::ComboSaveLightAttack()
{
	if (bSaveLightAttack)
	{
		bSaveLightAttack = false;
		bIsPerformingLightAttack = true;
		LightAttackAnimation();
	}
}

void UCombatComponent::ResetLightAttackCombo()
{
	LightAttackCount = 0;
	bSaveLightAttack = false;
	bIsPerformingLightAttack = false;

	if (bSaveHeavyAttack) ComboSaveHeavyAttack();
}

void UCombatComponent::ComboSaveHeavyAttack()
{
	if (bSaveHeavyAttack)
	{
		bSaveHeavyAttack = false;
		bIsPerformingHeavyAttack = true;
		HeavyAttackAnimation();
	}
}

void UCombatComponent::ResetHeavyAttackCombo()
{
	HeavyAttackCount = 0;
	bSaveHeavyAttack = false;
	bIsPerformingHeavyAttack = false;

	if (bSaveLightAttack) ComboSaveLightAttack();
}

void UCombatComponent::Evade()
{
	// TODO : Write evade code here
}

void UCombatComponent::Block_Start()
{
	if (!bCanBlock) return;

	if (bIsPerformingLightAttack || bIsPerformingHeavyAttack)
	{
		OwningCharacterRef->StopAnimMontage();
		ResetLightAttackCombo();
		ResetHeavyAttackCombo();
	}

	bIsBlocking = true;
	Block_Hold();
}

void UCombatComponent::Block_Hold()
{
	if (!bCanBlock) return;
}

void UCombatComponent::Block_Stop()
{
	if (!bCanBlock) return;
	bIsBlocking = false;
}

void UCombatComponent::LightAttack_Start()
{
	if (bSaveHeavyAttack || bIsBlocking || bIsStaggered || IsAnAbilityBeingUsed) return;

	if (bIsPerformingLightAttack || bIsPerformingHeavyAttack)
	{
		bSaveLightAttack = true;
	}
	else
	{
		bIsPerformingLightAttack = true;
		LightAttackAnimation();
	}
}

void UCombatComponent::LightAttack_Hold()
{
}

void UCombatComponent::LightAttack_Stop()
{
}

void UCombatComponent::LightAttackAnimation()
{
	if (CharacterData->LightAttackMontages.IsValidIndex(LightAttackCount)) OwningCharacterRef->PlayAnimMontage(CharacterData->LightAttackMontages[LightAttackCount], AttackSpeed);

	if (++LightAttackCount >= CharacterData->LightAttackMontages.Num()) LightAttackCount = 0;
}

void UCombatComponent::HeavyAttack_Start()
{
	if (bSaveLightAttack || bIsBlocking || bIsStaggered || IsAnAbilityBeingUsed) return;

	if (bIsPerformingLightAttack || bIsPerformingHeavyAttack)
	{
		bSaveHeavyAttack = true;
	}
	else
	{
		bIsPerformingHeavyAttack = true;
		HeavyAttackAnimation();
	}
}

void UCombatComponent::HeavyAttack_Hold()
{
}

void UCombatComponent::HeavyAttack_Stop()
{
}

void UCombatComponent::HeavyAttackAnimation()
{
	if (CharacterData->HeavyAttackMontages.IsValidIndex(HeavyAttackCount)) OwningCharacterRef->PlayAnimMontage(CharacterData->HeavyAttackMontages[HeavyAttackCount], AttackSpeed);

	if (++HeavyAttackCount >= CharacterData->HeavyAttackMontages.Num()) HeavyAttackCount = 0;
}

void UCombatComponent::Ability_Start()
{
	if (bIsStaggered || bIsAbilityOnCooldown || IsAnAbilityBeingUsed) return;

	AbilityAnimation();
}

void UCombatComponent::Ability_Hold()
{
}

void UCombatComponent::Ability_Stop()
{
}

void UCombatComponent::AbilityAnimation()
{
	if (CharacterData->AbilityMontage)
	{
		bIsAbilityBeingUsed = true;

		float AnimDuration = OwningCharacterRef->PlayAnimMontage(CharacterData->AbilityMontage, 1.f);

		FTimerHandle TimerHandle_AbilityDuration;
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_AbilityDuration,
			[this]() { bIsAbilityBeingUsed = false; },
			AnimDuration,
			false
		);
	}
}

void UCombatComponent::UltimateAbility_Start()
{
	if (bIsStaggered || bIsUltimateAbilityOnCooldown || IsAnAbilityBeingUsed) return;

	UltimateAbilityAnimation();
}

void UCombatComponent::UltimateAbility_Hold()
{
}

void UCombatComponent::UltimateAbility_Stop()
{
}

void UCombatComponent::UltimateAbilityAnimation()
{
	if (CharacterData->UltimateAbilityMontage)
	{
		bIsUltimateAbilityBeingUsed = true;

		float AnimDuration = OwningCharacterRef->PlayAnimMontage(CharacterData->UltimateAbilityMontage, 1.f);

		FTimerHandle TimerHandle_UltimateAbilityDuration;
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_UltimateAbilityDuration,
			[this]() { bIsUltimateAbilityBeingUsed = false; },
			AnimDuration,
			false
		);
	}
}