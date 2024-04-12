// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Core/CombatCharacter.h"

#include "Components/CombatComponent.h"
#include "Data/CombatCharacterData.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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

	CharacterData = NewCharacterData;

	// Capsules
	GetCapsuleComponent()->InitCapsuleSize(NewCharacterData->CapsuleRadius, NewCharacterData->CapsuleHalfHeight);

	// Mesh
	if (NewCharacterData->Mesh) GetMesh()->SetSkeletalMeshAsset(NewCharacterData->Mesh);
	GetMesh()->SetRelativeTransform(NewCharacterData->MeshTransform);
	if (NewCharacterData->AnimationBlueprint) GetMesh()->SetAnimClass(NewCharacterData->AnimationBlueprint->GeneratedClass);

	CombatComponent->CharacterData = NewCharacterData;
}