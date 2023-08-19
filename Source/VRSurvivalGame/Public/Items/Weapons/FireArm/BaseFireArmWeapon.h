// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/BaseWeapon.h"
#include "BaseFireArmWeapon.generated.h"

UENUM(BlueprintType)
enum class EShootTypes : uint8
{
	SingleShot,
	Automatic
};

UCLASS()
class VRSURVIVALGAME_API ABaseFireArmWeapon : public ABaseWeapon
{
	GENERATED_BODY()
	
public:
	virtual void UseActor(bool UseActor) override;

protected:
	virtual void FireStart();
	virtual void FireStop();

	virtual void MakeShot();

	void ApplyDamage(const FHitResult& HitResult);

	void GetTraceData(FVector& TraceStart, FVector& TraceEnd);
	bool MakeTrace(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	AController* GetController();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Socket")
		float ShootDistance = 3000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Socket")
		float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Socket")
		float ShootRate = 0.15f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Socket")
		float FirstShotDelay = 0.01f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Socket")
		FName MuzzleSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Socket")
	    EShootTypes ShootType;

private:
	FTimerHandle ShootTimer;

};
