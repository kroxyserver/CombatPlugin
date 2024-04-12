// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "AnimNotifys/CombatAnimNotify_ResetCombo.h"

#include "Core/CombatCharacter.h"

UCombatAnimNotify_ResetCombo::UCombatAnimNotify_ResetCombo()
{
	AttackType = ECombat_AttackType::None;
	NotifyName = "SpecifyAttackType...";
}

void UCombatAnimNotify_ResetCombo::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	switch (AttackType)
	{
	case ECombat_AttackType::None:
		NotifyName = "SpecifyAttackType...";
		break;
	case ECombat_AttackType::LightAttack:
		NotifyName = "ResetLightAttackCombo";
		break;
	case ECombat_AttackType::HeavyAttack:
		NotifyName = "ResetHeavyAttackCombo";
		break;
	default:
		break;
	}
}

void UCombatAnimNotify_ResetCombo::BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotify(BranchingPointPayload);

	ACombatCharacter* CombatCharacter = Cast<ACombatCharacter>(BranchingPointPayload.SkelMeshComponent->GetOwner());
	if (!CombatCharacter) return;
	
	switch (AttackType)
	{
		case ECombat_AttackType::None:
			break;
		case ECombat_AttackType::LightAttack:
			CombatCharacter->GetCombatComponent()->ResetLightAttackCombo();
			break;
		case ECombat_AttackType::HeavyAttack:
			CombatCharacter->GetCombatComponent()->ResetHeavyAttackCombo();
			break;
		default:
			break;
	}
}