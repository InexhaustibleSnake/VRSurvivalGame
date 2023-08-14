// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#include "Entity/Player/PlayerCharacter.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "Entity/Player/Input/PlayerInputData.h"
#include "Entity/Player/Components/HandSkeletalMesh.h"

APlayerCharacter::APlayerCharacter()
{
	MainCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	MainCamera->SetupAttachment(GetRootComponent());

	RightHandMC = CreateDefaultSubobject<UMotionControllerComponent>("RightHandMC");
	LeftHandMC = CreateDefaultSubobject<UMotionControllerComponent>("LeftHandMC");

	RightHandMC->SetupAttachment(GetRootComponent());
	LeftHandMC->SetupAttachment(GetRootComponent());

	RightHand = CreateDefaultSubobject<UHandSkeletalMesh>("RightHand");
	LeftHand = CreateDefaultSubobject<UHandSkeletalMesh>("LeftHand");

	RightHand->SetupAttachment(RightHandMC);
	LeftHand->SetupAttachment(LeftHandMC);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* PlayerEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	PlayerEnhancedInput->BindAction(InputActions->Movement, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	PlayerEnhancedInput->BindAction(InputActions->Turn, ETriggerEvent::Triggered, this, &APlayerCharacter::Rotate);
	PlayerEnhancedInput->BindAction(InputActions->RightHandGrab, ETriggerEvent::Started, RightHand, &UHandSkeletalMesh::GrabObject);
	PlayerEnhancedInput->BindAction(InputActions->LeftHandGrab, ETriggerEvent::Started, LeftHand, &UHandSkeletalMesh::GrabObject);
}

void APlayerCharacter::Move(const FInputActionValue& Amount)
{
	AddMovementInput(MainCamera->GetForwardVector(), Amount.Get<FVector2D>().X);
	AddMovementInput(GetActorRightVector(), Amount.Get<FVector2D>().Y);
}

void APlayerCharacter::Rotate(const FInputActionValue& Amount)
{
	float RotationScale = 2.0f;
	FRotator Rotation(0.0f, Amount.Get<FVector2D>().X * RotationScale, 0.0f);
	AddActorWorldRotation(Rotation, false, nullptr, ETeleportType::None);
}
