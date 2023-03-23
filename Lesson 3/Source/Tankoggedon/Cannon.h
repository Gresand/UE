#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStruct.h"
#include "Cannon.generated.h"

UCLASS()
class TANKOGGEDON_API ACannon : public AActor
{
	GENERATED_BODY()

public:	
	ACannon();

	void Fire();
	void FireSpecial();
	bool IsReadyToFire();
	void Reload();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* CannonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* ProjectileSpawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	ECannonType CannonType = ECannonType::FireProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	ECannonSpecialType CannonSpecialType = ECannonSpecialType::SpecialFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	float FireRange = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	float FireDanage = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int Ammo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	float QueueDelay = 0.2f;

	bool bReadyToFire = true;
	FTimerHandle ReloadTimer;
	FTimerHandle BurstShooting;

private:
	void Shoot();
	bool nextShoot = true;

};
