// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Core/CombatPlayerController.h"

#include "Components/CombatComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"

ACombatPlayerController::ACombatPlayerController()
{
	// Default variable values
	bCanMove = true;
	BaseLookupRate = 45.f;
	BaseTurnRate = 45.f;

	static ConstructorHelpers::FObjectFinder<UCombatPlayerInputData> CombatPlayerInputDataAsset(TEXT("/Script/Combat.CombatPlayerInputData'/Combat/Data/DA_CombatPlayerInputData.DA_CombatPlayerInputData'"));
	if (CombatPlayerInputDataAsset.Succeeded()) CombatPlayerInputData = CombatPlayerInputDataAsset.Object;
}

void ACombatPlayerController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (CombatPlayerInputData) UpdatePlayerInputData(CombatPlayerInputData);
}

void ACombatPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ACombatPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACombatPlayerController::Move);

		// Look
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACombatPlayerController::Look);

		// Evade
		EnhancedInputComponent->BindAction(EvadeAction, ETriggerEvent::Started, this, &ACombatPlayerController::Evade);

		// Sprinting
		switch (SprintAction.InputType)
		{
			case Press:
				EnhancedInputComponent->BindAction(SprintAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::Sprint_Start);
				break;
			case Hold:
				EnhancedInputComponent->BindAction(SprintAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Sprint_Hold);
				break;
			case Release:
				EnhancedInputComponent->BindAction(SprintAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Sprint_Stop);
				break;
			case PressAndHold:
				EnhancedInputComponent->BindAction(SprintAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::Sprint_Start);
				EnhancedInputComponent->BindAction(SprintAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Sprint_Hold);
				break;
			case PressAndRelease:
				EnhancedInputComponent->BindAction(SprintAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::Sprint_Start);
				EnhancedInputComponent->BindAction(SprintAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Sprint_Stop);
				break;
			case HoldAndRelease:
				EnhancedInputComponent->BindAction(SprintAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::Sprint_Hold);
				EnhancedInputComponent->BindAction(SprintAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Sprint_Stop);
				break;
			case PressHoldRelease:
				EnhancedInputComponent->BindAction(SprintAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::Sprint_Start);
				EnhancedInputComponent->BindAction(SprintAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Sprint_Hold);
				EnhancedInputComponent->BindAction(SprintAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Sprint_Stop);
				break;
			default:
				break;
		}

		// Blocking
		switch (BlockAction.InputType)
		{
			case Press:
				EnhancedInputComponent->BindAction(BlockAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::Block_Start);
				break;
			case Hold:
				EnhancedInputComponent->BindAction(BlockAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Block_Hold);
				break;
			case Release:
				EnhancedInputComponent->BindAction(BlockAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Block_Stop);
				break;
			case PressAndHold:
				EnhancedInputComponent->BindAction(BlockAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::Block_Start);
				EnhancedInputComponent->BindAction(BlockAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Block_Hold);
				break;
			case PressAndRelease:
				EnhancedInputComponent->BindAction(BlockAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::Block_Start);
				EnhancedInputComponent->BindAction(BlockAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Block_Stop);
				break;
			case HoldAndRelease:
				EnhancedInputComponent->BindAction(BlockAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::Block_Hold);
				EnhancedInputComponent->BindAction(BlockAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Block_Stop);
				break;
			case PressHoldRelease:
				EnhancedInputComponent->BindAction(BlockAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::Block_Start);
				EnhancedInputComponent->BindAction(BlockAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Block_Hold);
				EnhancedInputComponent->BindAction(BlockAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Block_Stop);
				break;
			default:
				break;
		}

		// Light Attack
		switch (LightAttackAction.InputType)
		{
			case Press:
				EnhancedInputComponent->BindAction(LightAttackAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::LightAttack_Start);
				break;
			case Hold:
				EnhancedInputComponent->BindAction(LightAttackAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::LightAttack_Hold);
				break;
			case Release:
				EnhancedInputComponent->BindAction(LightAttackAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::LightAttack_Stop);
				break;
			case PressAndHold:
				EnhancedInputComponent->BindAction(LightAttackAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::LightAttack_Start);
				EnhancedInputComponent->BindAction(LightAttackAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::LightAttack_Hold);
				break;
			case PressAndRelease:
				EnhancedInputComponent->BindAction(LightAttackAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::LightAttack_Start);
				EnhancedInputComponent->BindAction(LightAttackAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::LightAttack_Stop);
				break;
			case HoldAndRelease:
				EnhancedInputComponent->BindAction(LightAttackAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::LightAttack_Hold);
				EnhancedInputComponent->BindAction(LightAttackAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::LightAttack_Stop);
				break;
			case PressHoldRelease:
				EnhancedInputComponent->BindAction(LightAttackAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::LightAttack_Start);
				EnhancedInputComponent->BindAction(LightAttackAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::LightAttack_Hold);
				EnhancedInputComponent->BindAction(LightAttackAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::LightAttack_Stop);
				break;
			default:
				break;
		}

		// Heavy Attack
		switch (HeavyAttackAction.InputType)
		{
			case Press:
				EnhancedInputComponent->BindAction(HeavyAttackAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::HeavyAttack_Start);
				break;
			case Hold:
				EnhancedInputComponent->BindAction(HeavyAttackAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::HeavyAttack_Hold);
				break;
			case Release:
				EnhancedInputComponent->BindAction(HeavyAttackAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::HeavyAttack_Stop);
				break;
			case PressAndHold:
				EnhancedInputComponent->BindAction(HeavyAttackAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::HeavyAttack_Start);
				EnhancedInputComponent->BindAction(HeavyAttackAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::HeavyAttack_Hold);
				break;
			case PressAndRelease:
				EnhancedInputComponent->BindAction(HeavyAttackAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::HeavyAttack_Start);
				EnhancedInputComponent->BindAction(HeavyAttackAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::HeavyAttack_Stop);
				break;
			case HoldAndRelease:
				EnhancedInputComponent->BindAction(HeavyAttackAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::HeavyAttack_Hold);
				EnhancedInputComponent->BindAction(HeavyAttackAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::HeavyAttack_Stop);
				break;
			case PressHoldRelease:
				EnhancedInputComponent->BindAction(HeavyAttackAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::HeavyAttack_Start);
				EnhancedInputComponent->BindAction(HeavyAttackAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::HeavyAttack_Hold);
				EnhancedInputComponent->BindAction(HeavyAttackAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::HeavyAttack_Stop);
				break;
			default:
				break;
		}

		// Ability
		switch (AbilityAction.InputType)
		{
			case Press:
				EnhancedInputComponent->BindAction(AbilityAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::Ability_Start);
				break;
			case Hold:
				EnhancedInputComponent->BindAction(AbilityAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Ability_Hold);
				break;
			case Release:
				EnhancedInputComponent->BindAction(AbilityAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Ability_Stop);
				break;
			case PressAndHold:
				EnhancedInputComponent->BindAction(AbilityAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::Ability_Start);
				EnhancedInputComponent->BindAction(AbilityAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Ability_Hold);
				break;
			case PressAndRelease:
				EnhancedInputComponent->BindAction(AbilityAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::Ability_Start);
				EnhancedInputComponent->BindAction(AbilityAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Ability_Stop);
				break;
			case HoldAndRelease:
				EnhancedInputComponent->BindAction(AbilityAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::Ability_Hold);
				EnhancedInputComponent->BindAction(AbilityAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Ability_Stop);
				break;
			case PressHoldRelease:
				EnhancedInputComponent->BindAction(AbilityAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::Ability_Start);
				EnhancedInputComponent->BindAction(AbilityAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Ability_Hold);
				EnhancedInputComponent->BindAction(AbilityAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::Ability_Stop);
				break;
			default:
				break;
		}

		// Ultimate Ability
		switch (UltimateAbilityAction.InputType)
		{
			case Press:
				EnhancedInputComponent->BindAction(UltimateAbilityAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::UltimateAbility_Start);
				break;
			case Hold:
				EnhancedInputComponent->BindAction(UltimateAbilityAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::UltimateAbility_Hold);
				break;
			case Release:
				EnhancedInputComponent->BindAction(UltimateAbilityAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::UltimateAbility_Stop);
				break;
			case PressAndHold:
				EnhancedInputComponent->BindAction(UltimateAbilityAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::UltimateAbility_Start);
				EnhancedInputComponent->BindAction(UltimateAbilityAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::UltimateAbility_Hold);
				break;
			case PressAndRelease:
				EnhancedInputComponent->BindAction(UltimateAbilityAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::UltimateAbility_Start);
				EnhancedInputComponent->BindAction(UltimateAbilityAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::UltimateAbility_Stop);
				break;
			case HoldAndRelease:
				EnhancedInputComponent->BindAction(UltimateAbilityAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::UltimateAbility_Hold);
				EnhancedInputComponent->BindAction(UltimateAbilityAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::UltimateAbility_Stop);
				break;
			case PressHoldRelease:
				EnhancedInputComponent->BindAction(UltimateAbilityAction.InputAction, ETriggerEvent::Started, this, &ACombatPlayerController::UltimateAbility_Start);
				EnhancedInputComponent->BindAction(UltimateAbilityAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::UltimateAbility_Hold);
				EnhancedInputComponent->BindAction(UltimateAbilityAction.InputAction, ETriggerEvent::Completed, this, &ACombatPlayerController::UltimateAbility_Stop);
				break;
			default:
				break;
		}
	}
}

void ACombatPlayerController::Move(const FInputActionValue& Value)
{
	if (!GetCharacter()) return;

	if (!bCanMove) return;

	FVector2D MovementVector = Value.Get<FVector2D>();

	// Find out which way is Forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// Get Forward Vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// Get Right Vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	GetCharacter()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetCharacter()->AddMovementInput(RightDirection, MovementVector.X);
}

void ACombatPlayerController::Look(const FInputActionValue& Value)
{
	if (!bCanMove) return;

	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// add yaw and pitch input to controller
	AddYawInput(LookAxisVector.X * BaseLookupRate * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()));
	AddPitchInput(LookAxisVector.Y * BaseTurnRate * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()));
}

void ACombatPlayerController::Evade(const FInputActionValue& Value)
{
	OnEvade.ExecuteIfBound();
}

void ACombatPlayerController::Sprint_Start(const FInputActionValue& Value)
{
	OnSprint_Start.ExecuteIfBound();
}

void ACombatPlayerController::Sprint_Hold(const FInputActionValue& Value)
{
	OnSprint_Hold.ExecuteIfBound();
}

void ACombatPlayerController::Sprint_Stop(const FInputActionValue& Value)
{
	OnSprint_Stop.ExecuteIfBound();
}

void ACombatPlayerController::Block_Start(const FInputActionValue& Value)
{
	OnBlock_Start.ExecuteIfBound();
}

void ACombatPlayerController::Block_Hold(const FInputActionValue& Value)
{
	OnBlock_Hold.ExecuteIfBound();
}

void ACombatPlayerController::Block_Stop(const FInputActionValue& Value)
{
	OnBlock_Stop.ExecuteIfBound();
}

void ACombatPlayerController::LightAttack_Start(const FInputActionValue& Value)
{
	OnLightAttack_Start.ExecuteIfBound();
}

void ACombatPlayerController::LightAttack_Hold(const FInputActionValue& Value)
{
	OnLightAttack_Hold.ExecuteIfBound();
}

void ACombatPlayerController::LightAttack_Stop(const FInputActionValue& Value)
{
	OnLightAttack_Stop.ExecuteIfBound();
}

void ACombatPlayerController::HeavyAttack_Start(const FInputActionValue& Value)
{
	OnHeavyAttack_Start.ExecuteIfBound();
}

void ACombatPlayerController::HeavyAttack_Hold(const FInputActionValue& Value)
{
	OnHeavyAttack_Hold.ExecuteIfBound();
}

void ACombatPlayerController::HeavyAttack_Stop(const FInputActionValue& Value)
{
	OnHeavyAttack_Stop.ExecuteIfBound();
}

void ACombatPlayerController::Ability_Start(const FInputActionValue& Value)
{
	OnUseAbility_Start.ExecuteIfBound();
}

void ACombatPlayerController::Ability_Hold(const FInputActionValue& Value)
{
	OnUseAbility_Hold.ExecuteIfBound();
}

void ACombatPlayerController::Ability_Stop(const FInputActionValue& Value)
{
	OnUseAbility_Stop.ExecuteIfBound();
}

void ACombatPlayerController::UltimateAbility_Start(const FInputActionValue& Value)
{
	OnUseUltimateAbility_Start.ExecuteIfBound();
}

void ACombatPlayerController::UltimateAbility_Hold(const FInputActionValue& Value)
{
	OnUseUltimateAbility_Hold.ExecuteIfBound();
}

void ACombatPlayerController::UltimateAbility_Stop(const FInputActionValue& Value)
{
	OnUseUltimateAbility_Stop.ExecuteIfBound();
}

void ACombatPlayerController::BindInputToCombatComponent(UCombatComponent* CombatComponent)
{
	if (!CombatComponent) return;

	OnEvade.BindUFunction(CombatComponent, "Evade");
	OnSprint_Start.BindUFunction(CombatComponent, "Sprint_Start");
	OnSprint_Hold.BindUFunction(CombatComponent, "Sprint_Hold");
	OnSprint_Stop.BindUFunction(CombatComponent, "Sprint_Stop");
	OnBlock_Start.BindUFunction(CombatComponent, "Block_Start");
	OnBlock_Hold.BindUFunction(CombatComponent, "Block_Hold");
	OnBlock_Stop.BindUFunction(CombatComponent, "Block_Stop");
	OnLightAttack_Start.BindUFunction(CombatComponent, "LightAttack_Start");
	OnLightAttack_Hold.BindUFunction(CombatComponent, "LightAttack_Hold");
	OnLightAttack_Stop.BindUFunction(CombatComponent, "LightAttack_Stop");
	OnHeavyAttack_Start.BindUFunction(CombatComponent, "HeavyAttack_Start");
	OnHeavyAttack_Hold.BindUFunction(CombatComponent, "HeavyAttack_Hold");
	OnHeavyAttack_Stop.BindUFunction(CombatComponent, "HeavyAttack_Stop");
	OnUseAbility_Start.BindUFunction(CombatComponent, "Ability_Start");
	OnUseAbility_Hold.BindUFunction(CombatComponent, "Ability_Hold");
	OnUseAbility_Stop.BindUFunction(CombatComponent, "Ability_Stop");
	OnUseUltimateAbility_Start.BindUFunction(CombatComponent, "UltimateAbility_Start");
	OnUseUltimateAbility_Hold.BindUFunction(CombatComponent, "UltimateAbility_Hold");
	OnUseUltimateAbility_Stop.BindUFunction(CombatComponent, "UltimateAbility_Stop");
}

void ACombatPlayerController::EnableMovement(bool bEnable)
{
	bCanMove = bEnable;
}

void ACombatPlayerController::UpdatePlayerInputData(UCombatPlayerInputData* NewPlayerInputData)
{
	if (!NewPlayerInputData) return;

	CombatPlayerInputData = NewPlayerInputData;

	if (CombatPlayerInputData->CombatPlayerInputMappingContext)		DefaultMappingContext = CombatPlayerInputData->CombatPlayerInputMappingContext;
	if (CombatPlayerInputData->MoveAction)							MoveAction = CombatPlayerInputData->MoveAction;
	if (CombatPlayerInputData->LookAction)							LookAction = CombatPlayerInputData->LookAction;
	if (CombatPlayerInputData->EvadeAction)							EvadeAction = CombatPlayerInputData->EvadeAction;
	if (CombatPlayerInputData->SprintAction.IsValid())				SprintAction = CombatPlayerInputData->SprintAction;
	if (CombatPlayerInputData->BlockAction.IsValid())				BlockAction = CombatPlayerInputData->BlockAction;
	if (CombatPlayerInputData->LightAttackAction.IsValid())			LightAttackAction = CombatPlayerInputData->LightAttackAction;
	if (CombatPlayerInputData->HeavyAttackAction.IsValid())			HeavyAttackAction = CombatPlayerInputData->HeavyAttackAction;
	if (CombatPlayerInputData->AbilityAction.IsValid())				AbilityAction = CombatPlayerInputData->AbilityAction;
	if (CombatPlayerInputData->UltimateAbilityAction.IsValid())		UltimateAbilityAction = CombatPlayerInputData->UltimateAbilityAction;
}