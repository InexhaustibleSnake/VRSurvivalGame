// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#include "Entity/Zombie/BaseZombie.h"
#include "Entity/Components/BaseHealthComponent.h"
#include "AIController.h"
#include "BrainComponent.h"

void ABaseZombie::OnDeath()
{
	Super::OnDeath();

    const auto AIController = Cast<AAIController>(Controller);
    if (AIController && AIController->BrainComponent)
    {
        AIController->BrainComponent->Cleanup();
    }
}
