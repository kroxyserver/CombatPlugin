// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Core/CombatPlayerCharacter.h"

#include "Components/CombatComponent.h"
#include "Core/CombatPlayerController.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ACombatPlayerCharacter::ACombatPlayerCharacter()
{
	// Default variable values
	MinTargetArmLength = 180.f;
	MaxTargetArmLength = 240.f;

	// Spring Arm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = MinTargetArmLength;
	SpringArmComponent->SocketOffset = FVector(0.f, 70.f, 0.f);
	SpringArmComponent->TargetOffset = FVector(0.f, 0.f, 70.f);
	SpringArmComponent->bUsePawnControlRotation = true;

	// Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
}

void ACombatPlayerCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACombatPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<ACombatPlayerController>(Controller);
	if (!PlayerControllerRef) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.f, FColor::Red, "PlayerControllerRef Invalid. BeginPlay() CombatPlayerCharacter.cpp");

	PlayerControllerRef->BindInputToCombatComponent(GetCombatComponent());
	//GetCombatComponent()->SetCanMove.AddDynamic(PlayerControllerRef, &ACombatPlayerController::EnableMovement);
}

FHitResult ACombatPlayerCharacter::GetHitResultFromLookAtRotation()
{
	FVector StartLocation = CameraComponent->GetComponentLocation();
	FVector EndLocation = CameraComponent->GetComponentLocation() + CameraComponent->GetComponentRotation().Vector() * 10000;

	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		StartLocation,
		EndLocation,
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Camera),
		true,
		{},
		EDrawDebugTrace::None,
		HitResult,
		true
	);

	if (!HitResult.bBlockingHit) HitResult.Location = EndLocation;

	return HitResult;
}