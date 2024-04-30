// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "AnimNotifys/CombatAnimNotify_SaveAttackCombo.h"

#include "Core/CombatCharacter.h"

UCombatAnimNotify_SaveAttackCombo::UCombatAnimNotify_SaveAttackCombo()
{
	AttackType = ECombat_AttackType::None;
	NotifyName = "SpecifyAttackType...";
}

#if WITH_EDITOR
void UCombatAnimNotify_SaveAttackCombo::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	switch (AttackType)
	{
		case ECombat_AttackType::None:
			NotifyName = "SpecifyAttackType...";
			break;
		case ECombat_AttackType::LightAttack:
			NotifyName = "SaveLightAttackCombo";
			break;
		case ECombat_AttackType::HeavyAttack:
			NotifyName = "SaveHeavyAttackCombo";
			break;
		default:
			break;
	}
}
#endif

void UCombatAnimNotify_SaveAttackCombo::BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotify(BranchingPointPayload);

	ACombatCharacter* CombatCharacter = Cast<ACombatCharacter>(BranchingPointPayload.SkelMeshComponent->GetOwner());
	if (!CombatCharacter) return;

	switch (AttackType)
	{
		case ECombat_AttackType::None:
			break;
		case ECombat_AttackType::LightAttack:
			CombatCharacter->GetCombatComponent()->ComboSaveLightAttack();
			break;
		case ECombat_AttackType::HeavyAttack:
			CombatCharacter->GetCombatComponent()->ComboSaveHeavyAttack();
			break;
		default:
			break;
	}
}