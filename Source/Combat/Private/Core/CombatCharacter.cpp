// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Core/CombatCharacter.h"

#include "Data/CombatCharacterData.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

constexpr auto ProjectileSpawnPointSocketName_LightAttack = "ProjectileSpawnPoint_LightAttack";
constexpr auto ProjectileSpawnPointSocketName_LightAttack_Left = "ProjectileSpawnPoint_LightAttack_Left";
constexpr auto ProjectileSpawnPointSocketName_LightAttack_Right = "ProjectileSpawnPoint_LightAttack_Right";

constexpr auto ProjectileSpawnPointSocketName_HeavyAttack = "ProjectileSpawnPoint_HeavyAttack";
constexpr auto ProjectileSpawnPointSocketName_HeavyAttack_Left = "ProjectileSpawnPoint_HeavyAttack_Left";
constexpr auto ProjectileSpawnPointSocketName_HeavyAttack_Right = "ProjectileSpawnPoint_HeavyAttack_Right";

constexpr auto ProjectileSpawnPointSocketName_Ability = "ProjectileSpawnPoint_Ability";
constexpr auto ProjectileSpawnPointSocketName_Ability_Left = "ProjectileSpawnPoint_Ability_Left";
constexpr auto ProjectileSpawnPointSocketName_Ability_Right = "ProjectileSpawnPoint_Ability_Right";

constexpr auto ProjectileSpawnPointSocketName_UltimateAbility = "ProjectileSpawnPoint_UltimateAbility";
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
	//GetCharacterMovement()->MaxWalkSpeed = 360.f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 200.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->bCanWalkOffLedges = false;
	GetCharacterMovement()->bCanWalkOffLedgesWhenCrouching = false;

	// Combat Component
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));

	// Projectile Spawn Point Light Attack
	ProjectileSpawnPoint_LightAttack = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_LightAttack"));
	ProjectileSpawnPoint_LightAttack->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_LightAttack);

	// Projectile Spawn Point Light Attack Left
	ProjectileSpawnPoint_LightAttack_Left = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_LightAttack_Left"));
	ProjectileSpawnPoint_LightAttack_Left->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_LightAttack_Left);

	// Projectile Spawn Point Light Attack Right
	ProjectileSpawnPoint_LightAttack_Right = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_LightAttack_Right"));
	ProjectileSpawnPoint_LightAttack_Right->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_LightAttack_Right);

	// Projectile Spawn Point Heavy Attack
	ProjectileSpawnPoint_HeavyAttack = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_HeavyAttack"));
	ProjectileSpawnPoint_HeavyAttack->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_HeavyAttack);

	// Projectile Spawn Point Heavy Attack Left
	ProjectileSpawnPoint_HeavyAttack_Left = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_HeavyAttack_Left"));
	ProjectileSpawnPoint_HeavyAttack_Left->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_HeavyAttack_Left);

	// Projectile Spawn Point Heavy Attack Right
	ProjectileSpawnPoint_HeavyAttack_Right = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_HeavyAttack_Right"));
	ProjectileSpawnPoint_HeavyAttack_Right->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_HeavyAttack_Right);

	// Projectile Spawn Point Ability
	ProjectileSpawnPoint_Ability = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_Ability"));
	ProjectileSpawnPoint_Ability->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_Ability);

	// Projectile Spawn Point Ability Left
	ProjectileSpawnPoint_Ability_Left = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_Ability_Left"));
	ProjectileSpawnPoint_Ability_Left->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_Ability_Left);

	// Projectile Spawn Point Ability Right
	ProjectileSpawnPoint_Ability_Right = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_Ability_Right"));
	ProjectileSpawnPoint_Ability_Right->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_Ability_Right);

	// Projectile Spawn Point Ultimate Ability
	ProjectileSpawnPoint_UltimateAbility = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint_UltimateAbility"));
	ProjectileSpawnPoint_UltimateAbility->SetupAttachment(GetMesh(), ProjectileSpawnPointSocketName_UltimateAbility);

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
}

void ACombatCharacter::UpdateCharacterData(UCombatCharacterData* NewCharacterData)
{
	if (!NewCharacterData) return;

	// Capsules
	GetCapsuleComponent()->InitCapsuleSize(NewCharacterData->CapsuleRadius, NewCharacterData->CapsuleHalfHeight);

	// Movement
	GetCharacterMovement()->MaxWalkSpeed = NewCharacterData->WalkSpeed;

	// Mesh
	if (NewCharacterData->Mesh) GetMesh()->SetSkeletalMeshAsset(NewCharacterData->Mesh);
	GetMesh()->SetRelativeTransform(NewCharacterData->MeshTransform);
	if (NewCharacterData->AnimationBlueprintClass) GetMesh()->SetAnimInstanceClass(NewCharacterData->AnimationBlueprintClass);

	CharacterData = NewCharacterData;
	CombatComponent->CharacterData = NewCharacterData;
}

USceneComponent* ACombatCharacter::GetProjectileSpawnPoint(ECombat_AttackType AttackType, ECombat_ProjectileSpawnPointType HandType)
{
	switch (AttackType)
	{
		case ECombat_AttackType::None:
			break;
		case ECombat_AttackType::LightAttack:
			return (HandType == ECombat_ProjectileSpawnPointType::Default) ? ProjectileSpawnPoint_LightAttack : (HandType == ECombat_ProjectileSpawnPointType::Left) ? ProjectileSpawnPoint_LightAttack_Left : ProjectileSpawnPoint_LightAttack_Right;
			break;
		case ECombat_AttackType::HeavyAttack:
			return (HandType == ECombat_ProjectileSpawnPointType::Default) ? ProjectileSpawnPoint_HeavyAttack : (HandType == ECombat_ProjectileSpawnPointType::Left) ? ProjectileSpawnPoint_HeavyAttack_Left : ProjectileSpawnPoint_HeavyAttack_Right;
			break;
		case ECombat_AttackType::Ability:
			return (HandType == ECombat_ProjectileSpawnPointType::Default) ? ProjectileSpawnPoint_Ability : (HandType == ECombat_ProjectileSpawnPointType::Left) ? ProjectileSpawnPoint_Ability_Left : ProjectileSpawnPoint_Ability_Right;
			break;
		case ECombat_AttackType::UltimateAbility:
			return (HandType == ECombat_ProjectileSpawnPointType::Default) ? ProjectileSpawnPoint_UltimateAbility : (HandType == ECombat_ProjectileSpawnPointType::Left) ? ProjectileSpawnPoint_UltimateAbility_Left : ProjectileSpawnPoint_UltimateAbility_Right;
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
