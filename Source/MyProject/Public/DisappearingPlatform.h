#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DisappearingPlatform.generated.h"

UCLASS()
class MYPROJECT_API ADisappearingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ADisappearingPlatform();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	UStaticMeshComponent* StaticMeshComp;
	
	FTimerHandle ToggleTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Timer")
	float ToggleInterval;

	bool bIsVisible;

	void TogglePlatform();


};
