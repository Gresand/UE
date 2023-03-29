#include "AmmoBox.h"
#include "Components/StaticMeshComponent.h"
#include "Cannon.h"
#include "SecondCannon.h"
#include "TamkPawn.h"

// Sets default values
AAmmoBox::AAmmoBox()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;

	AmmoMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
	AmmoMesh->SetupAttachment(SceneComp);
	AmmoMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AmmoMesh->SetCollisionProfileName("OverlapAll");
	AmmoMesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnMeshOverlapBegin);
}

void AAmmoBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATamkPawn* TankPawn = Cast<ATamkPawn>(OtherActor);
	if (TankPawn)
	{
		TankPawn->SetupSecondCannon(SecondCannonClass);
		TankPawn->AmmoPickup();
		Destroy();
	}
}

