#include "SecondCannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"

ASecondCannon::ASecondCannon()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(SceneComp);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}

void ASecondCannon::Fire()
{
	if (!bReadyToFire && Ammo <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Can't shooting");
		return;
	}
	if (CannonType == ECannonRocket::Rocket)
	{
		Shoot();
		Ammo -= 1;
	}
	else if (CannonType == ECannonRocket::Laser)
	{
		Shoot();
		Ammo -= 1;
	}
	//bReadyToFire = false;
	if (Ammo <= 0)
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ASecondCannon::Reload, FireRate, false);

}

bool ASecondCannon::IsReadyToFire()
{
	return nextShoot ? bReadyToFire = true : bReadyToFire = false;
}

void ASecondCannon::Reload()
{
	bReadyToFire = true;
	if (Ammo <= 0)
		Ammo = 30;
}

void ASecondCannon::AmmoPickup()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("Ammo pickup: %d"), Ammo));
	Ammo += 30;
}

void ASecondCannon::BeginPlay()
{
	Super::BeginPlay();

	bReadyToFire = true;
	Ammo = 30;
}

void ASecondCannon::Shoot()
{
	if (CannonType == ECannonRocket::Rocket)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Ammo: %d Rocket"), Ammo));

		ASecondProjectile* Projectile = GetWorld()->SpawnActor<ASecondProjectile>(SecondProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		if (Projectile)
		{
			Projectile->Start();
		}
	}
	if (CannonType == ECannonRocket::Laser)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("Ammo: %d Laser"), Ammo));

		FHitResult hitResult;
		FCollisionQueryParams traceParams = FCollisionQueryParams();
		traceParams.AddIgnoredActor(this);
		traceParams.bReturnPhysicalMaterial = false;

		FVector Start = ProjectileSpawnPoint->GetComponentLocation();
		FVector End = Start + ProjectileSpawnPoint->GetForwardVector() * FireRange;

		if (GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECollisionChannel::ECC_Visibility, traceParams))
		{
			DrawDebugLine(GetWorld(), Start, hitResult.Location, FColor::Purple, false, 1.0f, 0, 5);
			if (hitResult.GetActor())
			{
				AActor* OverlappedActor = hitResult.GetActor();
				UE_LOG(LogTemp, Warning, TEXT("Actor %s. "), *OverlappedActor->GetName());
				OverlappedActor->Destroy();
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, 1.0f, 0, 5);
		}
	}
}

