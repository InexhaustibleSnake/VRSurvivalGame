// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#include "Entity/Zombie/BaseAIController.h"
#include "Perception/AIPerceptionComponent.h"

ABaseAIController::ABaseAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
	
	SetPerceptionComponent(*AIPerceptionComponent);
}
