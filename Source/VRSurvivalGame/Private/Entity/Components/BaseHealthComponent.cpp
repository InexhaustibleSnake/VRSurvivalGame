// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#include "Entity/Components/BaseHealthComponent.h"

UBaseHealthComponent::UBaseHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UBaseHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakePointDamage.AddDynamic(this, &UBaseHealthComponent::OnTakePointDamage);

	Health = MaxHealth;
}

void UBaseHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	TakeDamage(Damage);
}

void UBaseHealthComponent::SetHealth(float HealthValue)
{
	Health = HealthValue;
	OnHealthChanged.Broadcast(Health);
}

void UBaseHealthComponent::TakeDamage(float DamageAmount)
{
	float NewHealth = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);

	SetHealth(NewHealth);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}
