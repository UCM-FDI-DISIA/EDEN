#define _CRTDBG_MAP_ALLOC
#include "Hito1Prueba.h"
#include <InputManager.h>
#include <ScriptManager.h>
#include <LuaManager.h>
#include <RenderManager.h>
#include "Entity.h"
#include "Transform.h"
#include "CAnimator.h"
#include"CLuaBehaviour.h"
#include"CText.h"

#include <string>
#include "SceneManager.h"

const std::string eden_ec::Hito1Prueba::_id = "PRUEBA";

eden_ec::Hito1Prueba::Hito1Prueba() {

	////PRUEBA BOTON
	eden_script::LuaManager* scriptM = eden_script::ScriptManager::Instance()->GetLuaManager();
	scriptM->Regist(*this, "Hito1Prueba", &eden_ec::Hito1Prueba::Jump,"SetJump",this);
	scriptM->Regist(*this, "Hito1Prueba", &eden_ec::Hito1Prueba::ChangeText, "SetClick", this);
	scriptM->Regist(*this, "Hito1Prueba", &eden_ec::Hito1Prueba::Collide, "Collide", this);
	scriptM->SetGlobal(this, "Hito1Prueba");
	scriptM = nullptr;
}
void eden_ec::Hito1Prueba::Init(eden_script::ComponentArguments* args) {
	inputManager = eden_input::InputManager::Instance();
}

void eden_ec::Hito1Prueba::Start() {
	transform = _ent->GetComponent<CTransform>();
	animator = _ent->GetComponent<CAnimator>();
	_text = _ent->GetComponent<CText>();
	animator->PlayAnim("Idle");
	//eden_audio::AudioManager::Instance()->GetSound("bell.wav")->Play(true);
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

void eden_ec::Hito1Prueba::ChangeText() {
	_clicks++;
	std::string aux = "Clicks: " + std::to_string(_clicks);
	_text->SetNewText(aux);
}

void eden_ec::Hito1Prueba::Collide(eden_ec::Entity* other)
{
	Entity* otro = luabridge::getGlobal(_ent->GetComponent<CLuaBehaviour>()->getLuaState(), "other");
	std::cout << otro->GetEntityID() << std::endl;
}
