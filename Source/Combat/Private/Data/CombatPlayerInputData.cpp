// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Data/CombatPlayerInputData.h"

#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/InputAction.h"

UCombatPlayerInputData::UCombatPlayerInputData()
{
	/*Default values*/

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> CombatPlayerInputMappingContextAsset(TEXT("/Script/EnhancedInput.InputMappingContext'/Combat/Input/IMC_Combat.IMC_Combat'"));
	if (CombatPlayerInputMappingContextAsset.Succeeded()) CombatPlayerInputMappingContext = CombatPlayerInputMappingContextAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionAsset(TEXT("/Script/EnhancedInput.InputAction'/Combat/Input/IA_Combat_Move.IA_Combat_Move'"));
	if (MoveActionAsset.Succeeded()) MoveAction = MoveActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionAsset(TEXT("/Script/EnhancedInput.InputAction'/Combat/Input/IA_Combat_Look.IA_Combat_Look'"));
	if (LookActionAsset.Succeeded()) LookAction = LookActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> EvadeActionAsset(TEXT("/Script/EnhancedInput.InputAction'/Combat/Input/IA_Combat_Evade.IA_Combat_Evade'"));
	if (EvadeActionAsset.Succeeded()) EvadeAction = EvadeActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> SprintActionAsset(TEXT("/Script/EnhancedInput.InputAction'/Combat/Input/IA_Combat_Sprint.IA_Combat_Sprint'"));
	if (SprintActionAsset.Succeeded()) SprintAction.InputAction = SprintActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> BlockActionAsset(TEXT("/Script/EnhancedInput.InputAction'/Combat/Input/IA_Combat_Block.IA_Combat_Block'"));
	if (BlockActionAsset.Succeeded()) BlockAction.InputAction = BlockActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> LightAttackActionAsset(TEXT("/Script/EnhancedInput.InputAction'/Combat/Input/IA_Combat_LightAttack.IA_Combat_LightAttack'"));
	if (LightAttackActionAsset.Succeeded()) LightAttackAction.InputAction = LightAttackActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> HeavyAttackActionAsset(TEXT("/Script/EnhancedInput.InputAction'/Combat/Input/IA_Combat_HeavyAttack.IA_Combat_HeavyAttack'"));
	if (HeavyAttackActionAsset.Succeeded()) HeavyAttackAction.InputAction = HeavyAttackActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> AbilityActionAsset(TEXT("/Script/EnhancedInput.InputAction'/Combat/Input/IA_Combat_Ability.IA_Combat_Ability'"));
	if (AbilityActionAsset.Succeeded()) AbilityAction.InputAction = AbilityActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> UltimateAbilityActionAsset(TEXT("/Script/EnhancedInput.InputAction'/Combat/Input/IA_Combat_UltimateAbility.IA_Combat_UltimateAbility'"));
	if (UltimateAbilityActionAsset.Succeeded()) UltimateAbilityAction.InputAction = UltimateAbilityActionAsset.Object;

	SprintAction.InputType = ECombat_InputType::PressAndRelease;
	BlockAction.InputType = ECombat_InputType::PressHoldRelease;
	LightAttackAction.InputType = ECombat_InputType::Press;
	HeavyAttackAction.InputType = ECombat_InputType::Press;
	AbilityAction.InputType = ECombat_InputType::Press;
	UltimateAbilityAction.InputType = ECombat_InputType::Press;
}