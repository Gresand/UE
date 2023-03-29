#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SecondCannon.h"
#include "TamkPawn.generated.h"

class UStaticMeshComponent;
class ACannon;
UCLASS()
class TANKOGGEDON_API ATamkPawn : public APawn
{
	GENERATED_BODY()

public:
	ATamkPawn();

public:
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Move(float DeltaTime);
	void RotateRight(float Value);

	void Fire();
	void FireSpecial();

	void SetupCannon(TSubclassOf<ACannon> newCannonClass);
	void SetupSecondCannon(TSubclassOf<ASecondCannon> newCannonClass);
	void ChangeCannon();
	void AmmoPickup();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY()
	ACannon* Cannon;

	UPROPERTY()
	ASecondCannon* SecondCannon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
	TSubclassOf<ACannon> CannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
	TSubclassOf<ASecondCannon> SecondCannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
	class UArrowComponent* CannonSetupPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotationSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement | Rotation")
	float TurretRotationInterpolationKey = 0.1f;

	UPROPERTY()
	class ATankPlayerController* TankController;

	float targetForwardAxisValue = 0.0f;
	float targetRightAxisValue = 0.0f;
	float targetRotationRight = 0.0f;
};
