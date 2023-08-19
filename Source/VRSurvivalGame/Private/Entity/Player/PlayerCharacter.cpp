// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#include "Entity/Player/PlayerCharacter.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "Entity/Player/Input/PlayerInputData.h"
#include "Entity/Player/Components/HandSkeletalMesh.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerCharacter, All, All);

APlayerCharacter::APlayerCharacter()
{
	VRCameraPointComponent = CreateDefaultSubobject<USceneComponent>("VRCameraPointComponent");
	VRCameraPointComponent->SetupAttachment(GetRootComponent());
	
	MainCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	MainCamera->SetupAttachment(VRCameraPointComponent);

	RightHandMC = CreateDefaultSubobject<UMotionControllerComponent>("RightHandMC");
	LeftHandMC = CreateDefaultSubobject<UMotionControllerComponent>("LeftHandMC");

	RightHandMC->SetupAttachment(VRCameraPointComponent);
	LeftHandMC->SetupAttachment(VRCameraPointComponent);

	RightHand = CreateDefaultSubobject<UHandSkeletalMesh>("RightHand");
	LeftHand = CreateDefaultSubobject<UHandSkeletalMesh>("LeftHand");

	RightHand->SetupAttachment(RightHandMC);
	LeftHand->SetupAttachment(LeftHandMC);

	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (!PlayerController)
	{
		UE_LOG(LogPlayerCharacter, Display, TEXT("Player %s PlayerController pointer is nullptr in SetupPlayerInputComponent"), *GetName());
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	if (!EnhancedInputSubsystem)
	{
		UE_LOG(LogPlayerCharacter, Display, TEXT("Player %s EnhancedInputSubsystem pointer is nullptr in SetupPlayerInputComponent"), *GetName());
		return;
	}

	EnhancedInputSubsystem->ClearAllMappings();
	EnhancedInputSubsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* PlayerEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!PlayerEnhancedInput)
	{
		UE_LOG(LogPlayerCharacter, Display, TEXT("Player %s PlayerEnhancedInput pointer is nullptr in SetupPlayerInputComponent"), *GetName());
		return;
	}

	PlayerEnhancedInput->BindAction(InputActions->Movement, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	PlayerEnhancedInput->BindAction(InputActions->Turn, ETriggerEvent::Triggered, this, &APlayerCharacter::Rotate);

	PlayerEnhancedInput->BindAction(InputActions->RightHandGrab, ETriggerEvent::Started, RightHand, &UHandSkeletalMesh::GrabObject);
	PlayerEnhancedInput->BindAction(InputActions->LeftHandGrab, ETriggerEvent::Started, LeftHand, &UHandSkeletalMesh::GrabObject);

	PlayerEnhancedInput->BindAction(InputActions->RightHandUse, ETriggerEvent::Started, RightHand, &UHandSkeletalMesh::UseObject);
	PlayerEnhancedInput->BindAction(InputActions->RightHandUse, ETriggerEvent::Completed, RightHand, &UHandSkeletalMesh::UseObject);

	PlayerEnhancedInput->BindAction(InputActions->LeftHandUse, ETriggerEvent::Started, LeftHand, &UHandSkeletalMesh::UseObject);
	PlayerEnhancedInput->BindAction(InputActions->LeftHandUse, ETriggerEvent::Completed, LeftHand, &UHandSkeletalMesh::UseObject);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(VRCameraPointComponent);
	check(RightHandMC);
	check(LeftHandMC);
	check(RightHand);
	check(LeftHand);
	check(MainCamera);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateLocationBasedOnHMD();
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
	AddActorWorldRotation(Rotation);
}

void APlayerCharacter::UpdateLocationBasedOnHMD() //If the player is moving in real life, we want to move the character in the game
{
	if (!MainCamera || !GetCapsuleComponent()) return;

	FVector CameraLocation = MainCamera->GetComponentLocation();
	FVector CapsuleLocation = GetMesh()->GetComponentLocation();

	FVector LocationDelta = CameraLocation - CapsuleLocation;

	LocationDelta.Z = 0.0f; //We do not want to change the location of the character in height
	
	AddActorWorldOffset(LocationDelta);

	VRCameraPointComponent->AddWorldOffset(UKismetMathLibrary::NegateVector(LocationDelta), false);
}
