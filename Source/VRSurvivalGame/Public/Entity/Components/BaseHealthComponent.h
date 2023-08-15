// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRSURVIVALGAME_API UBaseHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBaseHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth() const { return Health; }

	UPROPERTY(BlueprintCallable, Category = "Health")
	FOnHealthChanged OnHealthChanged;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);
		
	virtual void SetHealth(float HealthValue);

	void TakeDamage(float DamageAmount);
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float MaxHealth = 100.0f;

private:
	float Health;

};
