// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Entity/BaseCharacter.h"
#include "BaseZombie.generated.h"

class UBaseHealthComponent;

UCLASS()
class VRSURVIVALGAME_API ABaseZombie : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	ABaseZombie();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBaseHealthComponent* HealthComponent;

};
