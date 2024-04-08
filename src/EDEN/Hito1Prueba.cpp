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
#include "SceneManager.h"
#include "CAudioEmitter.h"
#include <string>
#include "Sound.h"

const std::string eden_ec::Hito1Prueba::_id = "PRUEBA";

eden_ec::Hito1Prueba::Hito1Prueba() {

	////PRUEBA BOTON
	eden_script::LuaManager* scriptM = eden_script::ScriptManager::Instance()->GetLuaManager();
	scriptM->Regist(*this, "Hito1Prueba", &eden_ec::Hito1Prueba::StartGame, "SetClick", this);
	scriptM->SetGlobal(this, "Hito1Prueba");
	scriptM = nullptr;
}
void eden_ec::Hito1Prueba::Init(eden_script::ComponentArguments* args) {
	inputManager = eden_input::InputManager::Instance();
}

void eden_ec::Hito1Prueba::StartGame() {
	eden::SceneManager* scnManager = eden::SceneManager::Instance();
	scnManager->ChangeScene("CrossThePathFinal");
}
void eden_ec::Hito1Prueba::Start() {
	transform = _ent->GetComponent<CTransform>();
	_text = _ent->GetComponent<CText>();
	_audioEmitter = _ent->GetComponent<CAudioEmitter>();
	_audioEmitter->Play();
	_audioEmitter->SetLoop(true);
}

void eden_ec::Hito1Prueba::HandleInput() {

}

void eden_ec::Hito1Prueba::Update(float dt) {
	
}