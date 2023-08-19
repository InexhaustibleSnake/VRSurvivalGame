// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Entity/BaseCharacter.h"
#include "BaseZombie.generated.h"

UCLASS()
class VRSURVIVALGAME_API ABaseZombie : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	virtual void OnDeath() override;

};
