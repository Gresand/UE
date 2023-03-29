#include "SecondProjectile.h"
#include "Components/StaticMeshComponent.h"

ASecondProjectile::ASecondProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent = SceneComp;
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
    ProjectileMesh->SetupAttachment(SceneComp);
    ProjectileMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
    ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &ASecondProjectile::OnMeshOverlapBegin);

}

void ASecondProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MovementTimer, this, &ASecondProjectile::Move, MoveRate, true, 0.0f);
}

void ASecondProjectile::Move()
{
    FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
    SetActorLocation(nextPosition);
}

void ASecondProjectile::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("Projectile %s collided with %s. "), *GetName(), *OtherActor->GetName());
        OtherActor->Destroy();
        Destroy();
    }
}

