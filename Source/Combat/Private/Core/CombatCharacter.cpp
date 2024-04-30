// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Core/CombatCharacter.h"

#include "Data/CombatCharacterData.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

constexpr auto ProjectileSpawnPointSocketName_LightAttack_Left = "ProjectileSpawnPoint_LightAttack_Left";
constexpr auto ProjectileSpawnPointSocketName_LightAttack_Right = "ProjectileSpawnPoint_LightAttack_Right";

constexpr auto ProjectileSpawnPointSocketName_HeavyAttack_Left = "ProjectileSpawnPoint_HeavyAttack_Left";
constexpr auto ProjectileSpawnPointSocketName_HeavyAttack_Right = "ProjectileSpawnPoint_HeavyAttack_Right";

constexpr auto ProjectileSpawnPointSocketName_Ability_Left = "ProjectileSpawnPoint_Ability_Left";
constexpr auto ProjectileSpawnPointSocketName_Ability_Right = "ProjectileSpawnPoint_Ability_Right";

constexpr auto ProjectileSpawnPointSocketName_UltimateAbility_Left = "ProjectileSpawnPoint_UltimateAbility_Left";
constexpr auto ProjectileSpawnPointSocketName_UltimateAbility_Right = "ProjectileSpawnPoint_UltimateAbility_Right";

ACombatCharacter::ACombatCharacter()
{
	static ConstructorHelpers::FObjectFinder<UCombatCharacterData> CharacterDataAsset(TEXT("/Script/Combat.CombatCharacterData'/Combat/Data/DA_CombatCharacterData.DA_CombatCharacterData'"));
	if (CharacterDataAsset.Succeeded()) CharacterData = CharacterDataAsset.Object;

	// Don't rotate character when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Character Movement
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 350.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 360.f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 200.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Combat Component
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));

	// Projectile Spawn Point Light Attack Left
	ProjectileSpawnPoint_LightAttack_Left = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_LightAttack_Left"));
	ProjectileSpawnPoint_LightAttack_Left->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_LightAttack_Left);

	// Projectile Spawn Point Light Attack Right
	ProjectileSpawnPoint_LightAttack_Right = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_LightAttack_Right"));
	ProjectileSpawnPoint_LightAttack_Right->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_LightAttack_Right);

	// Projectile Spawn Point Heavy Attack Left
	ProjectileSpawnPoint_HeavyAttack_Left = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_HeavyAttack_Left"));
	ProjectileSpawnPoint_HeavyAttack_Left->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_HeavyAttack_Left);

	// Projectile Spawn Point Heavy Attack Right
	ProjectileSpawnPoint_HeavyAttack_Right = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_HeavyAttack_Right"));
	ProjectileSpawnPoint_HeavyAttack_Right->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_HeavyAttack_Right);

	// Projectile Spawn Point Ability Left
	ProjectileSpawnPoint_Ability_Left = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_Ability_Left"));
	ProjectileSpawnPoint_Ability_Left->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_Ability_Left);

	// Projectile Spawn Point Ability Right
	ProjectileSpawnPoint_Ability_Right = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_Ability_Right"));
	ProjectileSpawnPoint_Ability_Right->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_Ability_Right);

	// Projectile Spawn Point Ultimate Ability Left
	ProjectileSpawnPoint_UltimateAbility_Left = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_UltimateAbility_Left"));
	ProjectileSpawnPoint_UltimateAbility_Left->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_UltimateAbility_Left);

	// Projectile Spawn Point Ultimate Ability Right
	ProjectileSpawnPoint_UltimateAbility_Right = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_UltimateAbility_Right"));
	ProjectileSpawnPoint_UltimateAbility_Right->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_UltimateAbility_Right);
}

void ACombatCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (CharacterData) UpdateCharacterData(CharacterData);
}

void ACombatCharacter::BeginPlay()
{
	Super::BeginPlay();

	//if (CharacterData) UpdateCharacterData(CharacterData);
}

void ACombatCharacter::UpdateCharacterData(UCombatCharacterData* NewCharacterData)
{
	if (!NewCharacterData) return;

	// Capsules
	GetCapsuleComponent()->InitCapsuleSize(NewCharacterData->CapsuleRadius, NewCharacterData->CapsuleHalfHeight);

	// Mesh
	if (NewCharacterData->Mesh) GetMesh()->SetSkeletalMeshAsset(NewCharacterData->Mesh);
	GetMesh()->SetRelativeTransform(NewCharacterData->MeshTransform);
	if (NewCharacterData->AnimationBlueprintClass) GetMesh()->SetAnimInstanceClass(NewCharacterData->AnimationBlueprintClass);

	CharacterData = NewCharacterData;
	CombatComponent->CharacterData = NewCharacterData;
}

USceneComponent* ACombatCharacter::GetProjectileSpawnPoint(TEnumAsByte<ECombat_AttackType> AttackType, TEnumAsByte<ECombat_HandType> HandType)
{
	switch (AttackType)
	{
		case None:
			break;
		case LightAttack:
			return (HandType == Left) ? ProjectileSpawnPoint_LightAttack_Left : ProjectileSpawnPoint_LightAttack_Right;
			break;
		case HeavyAttack:
			return (HandType == Left) ? ProjectileSpawnPoint_HeavyAttack_Left : ProjectileSpawnPoint_HeavyAttack_Right;
			break;
		case Ability:
			return (HandType == Left) ? ProjectileSpawnPoint_Ability_Left : ProjectileSpawnPoint_Ability_Right;
			break;
		case UltimateAbility:
			return (HandType == Left) ? ProjectileSpawnPoint_UltimateAbility_Left : ProjectileSpawnPoint_UltimateAbility_Right;
			break;
		default:
			break;
	}

	return nullptr;
}

FHitResult ACombatCharacter::GetHitResultFromLookAtRotation()
{
	// Define in child classes

	return FHitResult();
}
