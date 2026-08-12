#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RotatingPlatform.generated.h"

UCLASS()
class MYPROJECT_API ARotatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	virtual void Tick(float DeltaTime) override;
	ARotatingPlatform();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Rotation")
	FRotator RotationSpeed;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
