#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
//Enhanced Input에서 액션 값을 받을 때 사용하는 구조체
struct FInputActionValue;

UCLASS()
class MYPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//이동속도 관련 프로퍼티
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float NormalSpeed;//기본 걷기 속도

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeedMultiplier;//기본속도 대비 몇배로 빠르게 달릴지 결정
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed; //스프린트 속도

	//IA_Move와 IA_Jump등을 처리할 함수 원형
	//Enhanced Input에서 액션 값은 FInputActionValue로 전달함
	UFUNCTION() void Move(const FInputActionValue& value);
	UFUNCTION() void StartJump(const FInputActionValue& value);
	UFUNCTION() void StopJump(const FInputActionValue& value);
	UFUNCTION() void Look(const FInputActionValue& value);
	UFUNCTION() void StartSprint(const FInputActionValue& value);
	UFUNCTION() void StopSprint(const FInputActionValue& value);
};
