#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SonPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class MYPROJECT_API ASonPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASonPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SprintAction;
	
protected:
	virtual void BeginPlay() override;
};
