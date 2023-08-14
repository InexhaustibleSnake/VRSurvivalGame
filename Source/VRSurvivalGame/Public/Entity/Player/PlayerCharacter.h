// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Entity/BaseCharacter.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UMotionControllerComponent;
class UCameraComponent;
class UInputMappingContext;
class UPlayerInputData;
class UHandSkeletalMesh;

UCLASS()
class VRSURVIVALGAME_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Move(const FInputActionValue& Amount);
	void Rotate(const FInputActionValue& Amount);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UMotionControllerComponent* RightHandMC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UMotionControllerComponent* LeftHandMC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHandSkeletalMesh* RightHand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHandSkeletalMesh* LeftHand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* MainCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Control")
		UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Control")
		UPlayerInputData* InputActions;

};
