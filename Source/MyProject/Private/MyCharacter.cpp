#include "MyCharacter.h"
#include "SonPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.5f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}


void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Enhanced InputComponent로 캐스팅
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		//IA를 가져오기 위해 현재 소유중인 컨트롤러를 SonPlayerController로 캐스팅
		if (ASonPlayerController* PlayerController = Cast<ASonPlayerController>(GetController())) {
			if (PlayerController->MoveAction) {
				//IA_Move 키를 누르고 있는동안 Move 호출
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
			}
			if (PlayerController->JumpAction) {
				//IA_Jump키를 누르고 있는동안 Jump 호출
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::StartJump);
				//IA_Jump키를 뗀 순간 StopJump호출
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::StopJump);
			}
			if (PlayerController->LookAction) {
				//IA_Look 마우스가 움직일 때 Look 호출
				EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
			}
			if (PlayerController->SprintAction) {
				//IA_Sprint키를 누르고 있는 동안 StartSprint 호출
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Triggered, this, &AMyCharacter::StartSprint);
				//IA_Sprint 키를 뗀 순간 StopSprint호출
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Completed, this, &AMyCharacter::StopSprint);
			}
		}
	}
}

void AMyCharacter::Move(const FInputActionValue& value)
{
	//컨트롤러가 있어야 방향 계산가능
	if (!Controller) return;

	//Value는 Axis2D로 설정된 IA_Move의 입력값(WASD)를 담고있음
	//예) (X=1, Y=0) → 전진 / (X=-1, Y=0) → 후진 / (X=0, Y=1) → 오른쪽 / (X=0, Y=-1) → 왼쪽
	const FVector2D MoveInput = value.Get<FVector2D>();
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		//캐릭터가 바라보는 방향(정면)으로 x축 이동
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y)) {
		//캐릭터의 오른쪽 방향으로 Y축 이동
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void AMyCharacter::StartJump(const FInputActionValue& value)
{
	//Jump함수는 Character가 기본 제공
	if (value.Get<bool>()) {
		Jump();
	}
}

void AMyCharacter::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>()) {
		StopJumping();
	}
}

void AMyCharacter::Look(const FInputActionValue& value)
{
	//마우스의 X,Y움직임을 2D축으로 가져옴
	FVector2D LookInput = value.Get<FVector2D>();

	//X는 좌우회전(Yaw), Y는 상하회전(Pitch)
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}
void AMyCharacter::StartSprint(const FInputActionValue& value)
{
	//Shift키를 누른 순간 이 함수가 호출된다고 가정. 스프린트 속도를 적용
	if (GetCharacterMovement()) {
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}
void AMyCharacter::StopSprint(const FInputActionValue& value)
{
	//Shift키를 뗀 순간 함수 호출. 기본 걷기속도로 복귀
	if (GetCharacterMovement()) {
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}