#include "CEDENScene.h"
#include "SceneManager.h"
//#include "Export.h"

void eden_ec::CEDENScene::Update(float dt) {
	_totalTime += dt;
	if (_totalTime >= 5.0f) {
		//eden::SceneManager::Instance()->PopScene();
		//eden_export::GetLoadScene()();
	}
}