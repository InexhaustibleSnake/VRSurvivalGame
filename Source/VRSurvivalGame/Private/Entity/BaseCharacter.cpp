// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#include "Entity/BaseCharacter.h"
#include "Entity/Components/BaseHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

ABaseCharacter::ABaseCharacter()
{
    HealthComponent = CreateDefaultSubobject<UBaseHealthComponent>("HealthComponent");

	PrimaryActorTick.bCanEverTick = false;
}

void ABaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    check(GetCharacterMovement());
    check(GetCapsuleComponent());
    check(GetMesh());
    check(HealthComponent);

    HealthComponent->OnDeath.AddDynamic(this, &ABaseCharacter::OnDeath);
}

void ABaseCharacter::OnDeath()
{
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(LifeSpanOnDeath);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}
