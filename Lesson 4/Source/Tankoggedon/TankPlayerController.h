#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKOGGEDON_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	class ATamkPawn* TankPawn;

	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	FVector GetMousePosition() { return MousePos; }
protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void RotateRight(float Value);

	void FireSpecial();
	void Fire();

	void ChangeCannon();
	FVector MousePos; 
};
