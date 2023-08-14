// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#include "Items/BaseGrabActor.h"

ABaseGrabActor::ABaseGrabActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetupAttachment(GetRootComponent());
}

void ABaseGrabActor::SetGrabbedActorData(bool Grabbed)
{
	SkeletalMesh->SetSimulatePhysics(!Grabbed);
}

void ABaseGrabActor::UseActor(bool UseActor) {}
