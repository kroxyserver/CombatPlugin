// Copyright Kunal Patil (kroxyserver). All Rights Reserved.

#include "Core/CombatPlayerCharacter.h"

#include "Components/CombatComponent.h"
#include "Core/CombatPlayerController.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ACombatPlayerCharacter::ACombatPlayerCharacter()
{
	// Default variable values
	MinTargetArmLength = 180.f;
	MaxTargetArmLength = 240.f;

	// Spring Arm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = MinTargetArmLength;
	SpringArmComponent->SocketOffset = FVector(0.f, 60.f, 0.f);
	SpringArmComponent->TargetOffset = FVector(0.f, 0.f, 60.f);
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

	PlayerControllerRef = Cast<ACombatPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PlayerControllerRef) return GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.f, FColor::Red, "PlayerControllerRef invalid. CombatPlayerCharacter.cpp, BeginPlay()");

	PlayerControllerRef->BindInputToCombatComponent(GetCombatComponent());
}