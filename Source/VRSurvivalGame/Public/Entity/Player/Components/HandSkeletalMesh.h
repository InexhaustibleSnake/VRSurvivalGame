// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "InputActionValue.h"
#include "HandSkeletalMesh.generated.h"

class ABaseGrabActor;

UCLASS()
class VRSURVIVALGAME_API UHandSkeletalMesh : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Grab")
	void GrabObject();

	void UseObject(const FInputActionValue& Value);

protected:
	void GetSocketData(FVector& TraceStart, FRotator& TraceRotation) const;

	void MakeTrace(FHitResult& HitResult, const FVector& TraceStart, const FRotator& TraceRotation);

	void ReleaseObject();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Grab")
		FName HandGrabSocket = "ObjectGrabSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Grab")
		FName MeleeWeaponSocket = "MeleeWeaponSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Grab")
		float TraceRadius = 5.0f;

	UPROPERTY()
		ABaseGrabActor* GrabbedObject = nullptr;
};
