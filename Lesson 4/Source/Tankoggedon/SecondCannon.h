#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStruct.h"
#include "SecondProjectile.h"
#include "SecondCannon.generated.h"

UCLASS()
class TANKOGGEDON_API ASecondCannon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASecondCannon();

	void Fire();
	bool IsReadyToFire();
	void Reload();

	void AmmoPickup();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* CannonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	ECannonRocket CannonType = ECannonRocket::Rocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	TSubclassOf<class ASecondProjectile> SecondProjectileClass;

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
