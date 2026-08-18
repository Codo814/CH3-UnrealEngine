#include "SonPlayerController.h"
#include "EnhancedInputSubsystems.h"

ASonPlayerController::ASonPlayerController()
	: InputMappingContext(nullptr),
	  MoveAction(nullptr),
	  JumpAction(nullptr),
	  LookAction(nullptr),
	  SprintAction(nullptr)

{

}

void ASonPlayerController::BeginPlay() {
	Super::BeginPlay();

	//현재 PlayerController에 연결된 Local Player 객체를 가져옴
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer()) {

		//Local Player에서 EnhancedInputLocalPlayerSubsystem 획득
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) 
		{
			if (InputMappingContext) {
				//Subsystem을 통해 할당한 IMC를 활성화
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}