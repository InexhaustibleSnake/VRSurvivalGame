// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#include "Entity/Player/Components/HandSkeletalMesh.h"
#include "Items/BaseGrabActor.h"

void UHandSkeletalMesh::GrabObject()
{
	if (GrabbedObject)
	{
		ReleaseObject();
		return;
	}

	FRotator TraceRotation;
	FVector TraceStart;

	GetSocketData(TraceStart, TraceRotation);

	FHitResult HitResult;
	MakeTrace(HitResult, TraceStart, TraceRotation);

	if (HitResult.bBlockingHit)
	{
		if (!HitResult.GetActor()) return;

		auto GrabActor = Cast<ABaseGrabActor>(HitResult.GetActor());
		if (!GrabActor)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Not Grabbable");
		}

		GrabActor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "MeleeWeaponSocket");

		GrabbedObject = GrabActor;
		
		GrabbedObject->SetGrabbedActorData(true);
	}
}

void UHandSkeletalMesh::GetSocketData(FVector& TraceStart, FRotator& TraceRotation) const
{
	GetSocketWorldLocationAndRotation(HandGrabSocket, TraceStart, TraceRotation);
}

void UHandSkeletalMesh::MakeTrace(FHitResult& HitResult, const FVector& TraceStart, const FRotator& TraceRotation)
{
	FCollisionQueryParams CollisionParams;

	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.AddIgnoredComponent(this);

	FCollisionShape CollisionShape;

	CollisionShape.SetSphere(TraceRadius);

	GetWorld()->SweepSingleByChannel(HitResult, TraceStart, TraceStart, FQuat::Identity, ECollisionChannel::ECC_Visibility, CollisionShape, CollisionParams);

	DrawDebugSphere(GetWorld(), TraceStart, TraceRadius, 16, FColor::Red, false, 5.0f);
}

void UHandSkeletalMesh::ReleaseObject()
{
	GrabbedObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	GrabbedObject->SetGrabbedActorData(false);

	GrabbedObject = nullptr;
}
