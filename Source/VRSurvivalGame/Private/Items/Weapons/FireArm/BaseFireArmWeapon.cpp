// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#include "Items/Weapons/FireArm/BaseFireArmWeapon.h"

void ABaseFireArmWeapon::UseActor(bool UseActor)
{
	UseActor ? FireStart() : FireStop();
}

void ABaseFireArmWeapon::FireStart()
{
	GetWorldTimerManager().SetTimer(ShootTimer, this, &ABaseFireArmWeapon::MakeShot, ShootRate, true, 0.01f);
}

void ABaseFireArmWeapon::FireStop() { GetWorldTimerManager().ClearTimer(ShootTimer); }

void ABaseFireArmWeapon::MakeShot() 
{
	FVector TraceStart, TraceEnd;

	GetTraceData(TraceStart, TraceEnd);

	FHitResult HitResult;

	if(!MakeTrace(HitResult, TraceStart, TraceEnd)) return;

	if (HitResult.bBlockingHit)
	{
		ApplyDamage(HitResult);
	}
}

void ABaseFireArmWeapon::ApplyDamage(const FHitResult& HitResult)
{
	const auto Actor = HitResult.GetActor();
	if (!Actor) return;

	FPointDamageEvent PointDamageEvent;

	PointDamageEvent.HitInfo = HitResult;

	Actor->TakeDamage(Damage, PointDamageEvent, GetController(), this);
}

void ABaseFireArmWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
{
	FRotator TraceRotation;

	SkeletalMesh->GetSocketWorldLocationAndRotation(MuzzleSocket, TraceStart, TraceRotation);

	TraceEnd = TraceStart + TraceRotation.Vector() * ShootDistance;
}

bool ABaseFireArmWeapon::MakeTrace(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return false;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 5.0f);

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

	return true;
}

AController* ABaseFireArmWeapon::GetController()
{
	const auto PlayerPawn = Cast<APawn>(GetOwner());
	return PlayerPawn ? PlayerPawn->GetController() : nullptr;
}

