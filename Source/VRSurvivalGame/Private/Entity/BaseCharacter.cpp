// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

#include "Entity/BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ABaseCharacter::BeginPlay()
{
    check(GetCharacterMovement());
    check(GetCapsuleComponent());
    check(GetMesh());
}
