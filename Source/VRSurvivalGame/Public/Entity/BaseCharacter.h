// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UBaseHealthComponent;

UCLASS()
class VRSURVIVALGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnDeath();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBaseHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LifeSpan")
	float LifeSpanOnDeath = 30.0f;
};
