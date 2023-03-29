#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SecondProjectile.generated.h"

UCLASS()
class TANKOGGEDON_API ASecondProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASecondProjectile();

	void Start();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MoveRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Damage = 1.0f;

	FTimerHandle MovementTimer;

	UFUNCTION()
		void Move();

	UFUNCTION()
	void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor*
		OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
		bFromSweep, const FHitResult& SweepResult);
};
