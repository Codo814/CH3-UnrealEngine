#include "DisappearingPlatform.h"
#include "TimerManager.h"

// Sets default values
ADisappearingPlatform::ADisappearingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SCENEROOT"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	ToggleInterval = 2.0f;
	bIsVisible = true;
}

// Called when the game starts or when spawned
void ADisappearingPlatform::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(
		ToggleTimerHandle,
		this,
		&ADisappearingPlatform::TogglePlatform,
		ToggleInterval,
		true);
}

void ADisappearingPlatform::TogglePlatform()
{
	bIsVisible = !bIsVisible;
	SetActorHiddenInGame(!bIsVisible);
	SetActorEnableCollision(bIsVisible);
}
