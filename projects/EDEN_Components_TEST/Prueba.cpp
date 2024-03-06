#include "Prueba.h"
#include "InputManager.h"
#include "Entity.h"
#include "Transform.h"

const std::string eden_ec::CPrueba::_id = "PRUEBA";

void eden_ec::CPrueba::InitComponent() {
	inputManager = eden_input::InputManager::Instance();
	transform = (eden_ec::CTransform*)_ent->GetComponent("TRASNFORM");
}

void eden_ec::CPrueba::HandleInput() {

}

void eden_ec::CPrueba::Update(float dt) {

	if (inputManager->IsKeyDown('a')) {
		transform->Translate(eden_utils::Vector3(-1, 0, 0));
		keyPressed = true;
		if (!keyPressed) {
			//ANIMATION
		}

	}
	else if (inputManager->IsKeyDown('w')) {
		transform->Translate(eden_utils::Vector3(0, 0, 1));
		keyPressed = true;
		if (!keyPressed) {
			//ANIMATION
		}
	}
	else if (inputManager->IsKeyDown('s')) {
		transform->Translate(eden_utils::Vector3(0, 0, -1));
		keyPressed = true;
		if (!keyPressed) {
			//ANIMATION
		}
	}
	else if (inputManager->IsKeyDown('d')) {
		transform->Translate(eden_utils::Vector3(1, 0, 0));
		keyPressed = true;
		if (!keyPressed) {
			//ANIMATION
		}
	}
	else {
		if(keyPressed) //ANIMACION IDLE
		keyPressed = false;
	}

}