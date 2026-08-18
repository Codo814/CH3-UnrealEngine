#include "MyGameMode.h"
#include "MyCharacter.h"
#include "SonPlayerController.h"

AMyGameMode::AMyGameMode() {

	DefaultPawnClass = AMyCharacter::StaticClass();
	PlayerControllerClass = ASonPlayerController::StaticClass();
}