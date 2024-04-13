#define _CRTDBG_MAP_ALLOC
#include "Hito2MenuPausa.h"
#include <InputManager.h>
#include <ScriptManager.h>
#include <LuaManager.h>
#include"CLuaBehaviour.h"
#include "SceneManager.h"

#include <RenderManager.h>

const std::string eden_ec::Hito2MenuPausa::_id = "PAUSA";

eden_ec::Hito2MenuPausa::Hito2MenuPausa() {

	////PRUEBA BOTON
	eden_script::LuaManager* scriptM = eden_script::ScriptManager::Instance()->GetLuaManager();
	scriptM->Regist(*this, "Pausa", &eden_ec::Hito2MenuPausa::ResumeGame, "Resume", this);
	scriptM->Regist(*this, "Pausa", &eden_ec::Hito2MenuPausa::ExitGame, "Exit", this);
	scriptM->Regist(*this, "Pausa", &eden_ec::Hito2MenuPausa::BackToMenu, "BackMenu", this);
	scriptM->SetGlobal(this, "Pausa");
	scriptM = nullptr;
}
void eden_ec::Hito2MenuPausa::Init(eden_script::ComponentArguments* args) {
	inputManager = eden_input::InputManager::Instance();
}
void eden_ec::Hito2MenuPausa::Start() {
	
}

void eden_ec::Hito2MenuPausa::HandleInput() {

}

void eden_ec::Hito2MenuPausa::ResumeGame()
{
	eden::SceneManager* scnManager = eden::SceneManager::Instance();
	scnManager->PopScene();
}

void eden_ec::Hito2MenuPausa::ExitGame()
{
	eden_input::InputManager::Instance()->SetCloseWindow();
}

void eden_ec::Hito2MenuPausa::BackToMenu()
{
	//eden_render::RenderManager::Instance()->ChangeResolution();
	eden::SceneManager* scnManager = eden::SceneManager::Instance();
	scnManager->ChangeScene("Menu");
}

void eden_ec::Hito2MenuPausa::Update(float dt) {

}