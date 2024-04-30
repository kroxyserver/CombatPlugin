// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Components/CombatComponent.h"

#include "Core/CombatPlayerController.h"
#include "Data/CombatCharacterData.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "KismetAnimationLibrary.h"

#define IsAnAbilityBeingUsed bIsAbilityBeingUsed || bIsUltimateAbilityBeingUsed

UCombatComponent::UCombatComponent()
{
	// Default variable values
	AttackSpeed = 1.f;
	bCanBlock = true;
	bIsBlocking = false;
	bIsEvading = false;
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

	PlayerControllerRef = Cast<ACombatPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PlayerControllerRef) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.f, FColor::Red, "PlayerControllerRef invalid. CombatComponent.cpp, BeginPlay(). The PlayerController specified in GameMode must be of type ACombatPlayerController.");

	if (!OwningCharacterRef || !PlayerControllerRef) return;

	PlayerControllerRef->BindInputToCombatComponent(this);
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
	if (bIsEvading || IsAnAbilityBeingUsed) return;

	// Don't Evade if character is not moving
	if (OwningCharacterRef->GetVelocity() == FVector::ZeroVector) return;

	if (bIsPerformingLightAttack || bIsPerformingHeavyAttack)
	{
		OwningCharacterRef->StopAnimMontage();
		ResetLightAttackCombo();
		ResetHeavyAttackCombo();
	}

	//  Get Movement Direction
	float DirectionAngle = UKismetAnimationLibrary::CalculateDirection(OwningCharacterRef->GetVelocity(), OwningCharacterRef->GetActorRotation());

	// Set is evading
	bIsEvading = true;

	// Play Evade Montage in that direction
	float AnimDuration = OwningCharacterRef->PlayAnimMontage(	
		(DirectionAngle < 45.f && DirectionAngle > -45.f) ? CharacterData->EvadeForwardMontage
		: (DirectionAngle <= -45.f && DirectionAngle >= -135.f) ? CharacterData->EvadeLeftMontage
		: (DirectionAngle <= 135.f && DirectionAngle >= 45.f) ? CharacterData->EvadeRightMontage
		: /*(DirectionAngle < -135.f && DirectionAngle > 135.f)*/ CharacterData->EvadeBackwardMontage
	);

	// Set is not evading after evade montage duration
	FTimerHandle TimerHandle_EvadeDuration;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_EvadeDuration,
		[this]() { bIsEvading = false; },
		AnimDuration,
		false
	);
}

void UCombatComponent::Block_Start()
{
	if (!bCanBlock || bIsEvading) return;

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
	if (!bCanBlock || bIsEvading) return;
}

void UCombatComponent::Block_Stop()
{
	if (!bCanBlock || bIsEvading) return;
	bIsBlocking = false;
}

void UCombatComponent::LightAttack_Start()
{
	if (bSaveHeavyAttack || bIsBlocking || bIsEvading || bIsStaggered || IsAnAbilityBeingUsed) return;

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

float UCombatComponent::LightAttackAnimation()
{
	float AnimDuration = 0.f;

	if (CharacterData->LightAttackMontages.IsValidIndex(LightAttackCount))
	{
		AnimDuration = OwningCharacterRef->PlayAnimMontage(CharacterData->LightAttackMontages[LightAttackCount], AttackSpeed);

		OnPlayLightAttackAnimation.Broadcast();
	}

	if (++LightAttackCount >= CharacterData->LightAttackMontages.Num()) LightAttackCount = 0;

	return AnimDuration;
}

void UCombatComponent::HeavyAttack_Start()
{
	if (bSaveLightAttack || bIsBlocking || bIsEvading || bIsStaggered || IsAnAbilityBeingUsed) return;

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

float UCombatComponent::HeavyAttackAnimation()
{
	float AnimDuration = 0.f;

	if (CharacterData->HeavyAttackMontages.IsValidIndex(HeavyAttackCount))
	{
		AnimDuration = OwningCharacterRef->PlayAnimMontage(CharacterData->HeavyAttackMontages[HeavyAttackCount], AttackSpeed);

		OnPlayHeavyAttackAnimation.Broadcast();
	}

	if (++HeavyAttackCount >= CharacterData->HeavyAttackMontages.Num()) HeavyAttackCount = 0;

	return AnimDuration;
}

void UCombatComponent::Ability_Start()
{
	if (bIsEvading || bIsStaggered || bIsAbilityOnCooldown || IsAnAbilityBeingUsed) return;

	AbilityAnimation();
}

void UCombatComponent::Ability_Hold()
{
}

void UCombatComponent::Ability_Stop()
{
}

float UCombatComponent::AbilityAnimation()
{
	float AnimDuration = 0.f;

	if (CharacterData->AbilityMontage)
	{
		bIsAbilityBeingUsed = true;

		AnimDuration = OwningCharacterRef->PlayAnimMontage(CharacterData->AbilityMontage, 1.f);

		OnPlayAbilityAnimation.Broadcast();

		FTimerHandle TimerHandle_AbilityDuration;
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_AbilityDuration,
			[this]() { bIsAbilityBeingUsed = false; },
			AnimDuration,
			false
		);
	}

	return AnimDuration;
}

void UCombatComponent::UltimateAbility_Start()
{
	if (bIsEvading || bIsStaggered || bIsUltimateAbilityOnCooldown || IsAnAbilityBeingUsed) return;

	UltimateAbilityAnimation();
}

void UCombatComponent::UltimateAbility_Hold()
{
}

void UCombatComponent::UltimateAbility_Stop()
{
}

float UCombatComponent::UltimateAbilityAnimation()
{
	float AnimDuration = 0.f;

	if (CharacterData->UltimateAbilityMontage)
	{
		bIsUltimateAbilityBeingUsed = true;

		AnimDuration = OwningCharacterRef->PlayAnimMontage(CharacterData->UltimateAbilityMontage, 1.f);

		OnPlayUltimateAbilityAnimation.Broadcast();

		FTimerHandle TimerHandle_UltimateAbilityDuration;
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_UltimateAbilityDuration,
			[this]() { bIsUltimateAbilityBeingUsed = false; },
			AnimDuration,
			false
		);
	}

	return AnimDuration;
}