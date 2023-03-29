#include "TamkPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Cannon.h"
#include "SecondCannon.h"
#include <Components/ArrowComponent.h>



// Sets default values
ATamkPawn::ATamkPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxCollision;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(BoxCollision);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BoxCollision);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->SetupAttachment(TurretMesh);
}

void ATamkPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Движение
	Move(DeltaTime);

	//Вращение
	float yawRotation = RotationSpeed * targetRotationRight * DeltaTime;
	FRotator currentRotation = GetActorRotation();
	yawRotation += currentRotation.Yaw;
	FRotator newRotator = FRotator(0.0f, yawRotation, 0.0f);
	SetActorRotation(newRotator);

	//Поворот башни
	if (TankController)
	{
		FVector mousePos = TankController->GetMousePosition();
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePos);
		FRotator TurretRotation = TurretMesh->GetComponentRotation();
		targetRotation.Pitch = TurretRotation.Pitch;
		targetRotation.Roll = TurretRotation.Roll;
		TurretMesh->SetWorldRotation(FMath::Lerp(TurretRotation, targetRotation, TurretRotationInterpolationKey));

	}
}

void ATamkPawn::MoveForward(float Value)
{
	targetForwardAxisValue = Value;
}

void ATamkPawn::MoveRight(float Value)
{
	targetRightAxisValue = Value;
}

void ATamkPawn::Move(float DeltaTime)
{
	FVector CurrentPosition = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector RightVector = GetActorRightVector();
	FVector ForwardMove = ForwardVector * MoveSpeed * targetForwardAxisValue * DeltaTime;
	FVector RightMove = RightVector * MoveSpeed * targetRightAxisValue * DeltaTime;
	FVector Move = CurrentPosition + ForwardMove + RightMove;
	SetActorLocation(Move, true);
}

void ATamkPawn::RotateRight(float Value)
{
	targetRotationRight = Value;
}

void ATamkPawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
	else if (SecondCannon)
	{
		SecondCannon->Fire();
	}
}

void ATamkPawn::FireSpecial()
{
	if (Cannon)
	{
		Cannon->FireSpecial();
	}
}

void ATamkPawn::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	if (!newCannonClass)
	{
		return;
	}
	if (Cannon)
	{
		Cannon->Destroy();
	}

	FActorSpawnParameters spawnParams;
	spawnParams.Instigator = this;
	spawnParams.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(newCannonClass, spawnParams);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void ATamkPawn::SetupSecondCannon(TSubclassOf<ASecondCannon> newCannonClass)
{
	if (!newCannonClass)
	{
		return;
	}
	if (SecondCannon)
	{
		SecondCannon->Destroy();
	}

	FActorSpawnParameters spawnParams;
	spawnParams.Instigator = this;
	spawnParams.Owner = this;

	SecondCannon = GetWorld()->SpawnActor<ASecondCannon>(newCannonClass, spawnParams);
	SecondCannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void ATamkPawn::ChangeCannon()
{
	if (SecondCannon)
	{
		SetupCannon(CannonClass);
	}
	else if (Cannon)
	{
		SetupSecondCannon(SecondCannonClass);
	}
}

void ATamkPawn::AmmoPickup()
{
	if (SecondCannon)
	{
		SecondCannon->AmmoPickup();
	}
	else if (Cannon)
	{
		Cannon->AmmoPickup();
	}
}

void ATamkPawn::BeginPlay()
{
	Super::BeginPlay();
	TankController = Cast<ATankPlayerController>(GetController());
	SetupCannon(CannonClass);
}
