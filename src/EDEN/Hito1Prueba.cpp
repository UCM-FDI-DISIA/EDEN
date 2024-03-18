#include <lua.hpp>
#include <LuaBridge.h>

#include "Hito1Prueba.h"
#include <InputManager.h>
#include <ScriptManager.h>
#include <LuaManager.h>
#include <RenderManager.h>
#include "Entity.h"
#include "Transform.h"
#include "CAnimator.h"

const std::string eden_ec::Hito1Prueba::_id = "PRUEBA";

eden_ec::Hito1Prueba::Hito1Prueba() {

	////PRUEBA BOTON
	eden_script::ScriptManager::Instance()->GetLuaManager()->Regist(*this);
}
void eden_ec::Hito1Prueba::Init(eden_script::ComponentArguments* args) {
	inputManager = eden_input::InputManager::Instance();
}

void eden_ec::Hito1Prueba::Start() {
	transform = _ent->GetComponent<CTransform>();
	animator = _ent->GetComponent<CAnimator>();
	animator->PlayAnim("Idle");
}

void eden_ec::Hito1Prueba::HandleInput() {

}

void eden_ec::Hito1Prueba::Update(float dt) {
	
	if (inputManager->IsKeyHeld('a')) {
		transform->Translate(eden_utils::Vector3(0, 0, -1));
		transform->SetRotation(eden_utils::Quaternion(90, eden_utils::Vector3(0, 1, 0)));
		if (!keyPressed) {
			animator->PlayAnim("Walk");
		}
		idle = false;
		jump = false;
		keyPressed = true;

	}
	else if (inputManager->IsKeyHeld('w')) {
		transform->Translate(eden_utils::Vector3(1, 0, 0));
		transform->SetRotation(eden_utils::Quaternion(180, eden_utils::Vector3(0, 1, 0)));
		if (!keyPressed) {
			animator->PlayAnim("Walk");
		}
		idle = false;
		jump = false;
		keyPressed = true;

	}
	else if (inputManager->IsKeyHeld('s')) {
		transform->Translate(eden_utils::Vector3(-1, 0, 0));
		if (!keyPressed) {
			animator->PlayAnim("Walk");
		}
		idle = false;
		jump = false;
		keyPressed = true;

	}
	else if (inputManager->IsKeyHeld('d')) {
		transform->Translate(eden_utils::Vector3(0, 0, 1));
		transform->SetRotation(eden_utils::Quaternion(180, eden_utils::Vector3(0, 1, 0)));

		if (!keyPressed) {
			animator->PlayAnim("Walk");
		}
		idle = false;
		jump = false;
		keyPressed = true;

	}
	else if (inputManager->IsKeyDown(inputManager->SPACE)) {
		Jump();
	}
	else {
		if (!idle && !jump) {
			animator->PlayAnim("Idle");
			idle = true;
		}
		if (jump && animator->GetCurrentAnim() == "Idle") { 
			jump = false;
			idle = true;
			transform->Translate(eden_utils::Vector3(0, -20, 0));
		}
		keyPressed = false;
	}

}

void eden_ec::Hito1Prueba::Jump() {
	transform->Translate(eden_utils::Vector3(0, 20, 0));

	if (!jump) {
		animator->PlayAnim("JumpStart");
		jump = true;
		idle = false;
	}
}