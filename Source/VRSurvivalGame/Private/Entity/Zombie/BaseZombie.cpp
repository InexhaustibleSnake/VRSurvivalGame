// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#include "Entity/Zombie/BaseZombie.h"
#include "Entity/Components/BaseHealthComponent.h"

ABaseZombie::ABaseZombie()
{
	HealthComponent = CreateDefaultSubobject<UBaseHealthComponent>("HealthComponent");
}
