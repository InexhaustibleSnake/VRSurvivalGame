// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGrabActor.generated.h"

UCLASS()
class VRSURVIVALGAME_API ABaseGrabActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseGrabActor();

	virtual void SetGrabbedActorData(bool Grabbed);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* SkeletalMesh;

};
