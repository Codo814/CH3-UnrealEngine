#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MovingPlatform.generated.h"

UCLASS()
class MYPROJECT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AMovingPlatform();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Platform|Movement")
	FVector StartLocation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Platform|Movement")
	float MoveSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Platform|Movement")
	float MaxRange;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Platform|Movement")
	FVector MoveDirection;

	bool bMovingForward;

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
