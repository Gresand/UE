#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TamkPawn.generated.h"

class UStaticMeshComponent;
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
protected:
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float RotationSpeed = 100.0f;

	float targetForwardAxisValue = 0.0f;
	float targetRightAxisValue = 0.0f;
};
