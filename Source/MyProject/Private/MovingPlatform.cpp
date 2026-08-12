#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;
	MoveSpeed = 300.0f;
	MaxRange = 500.0f;
	MoveDirection = FVector(1.0f, 0.0f, 0.0f);
	bMovingForward = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	float DirectionSign = bMovingForward ? 1.0f : -1.0f;

	FVector NormalizedDirection = MoveDirection.GetSafeNormal();

	FVector Movement =
		NormalizedDirection * MoveSpeed * DirectionSign * DeltaTime;

	AddActorWorldOffset(Movement);

	FVector CurrentOffset = GetActorLocation() - StartLocation;

	float DistanceAlongDirection =
		FVector::DotProduct(CurrentOffset, NormalizedDirection);

	if (bMovingForward && DistanceAlongDirection >= MaxRange)
	{
		bMovingForward = false;
	}
	else if (!bMovingForward && DistanceAlongDirection <= 0.0f)
	{
		bMovingForward = true;
	}
}