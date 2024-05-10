#include "CEDENScene.h"
#include "SceneManager.h"
#include "EdenMaster.h"
#include "Entity.h"
#include "CCamera.h"

void eden_ec::CEDENScene::Start() {
	_ent->GetComponent<eden_ec::CCamera>()->SetBackgroundColor(0, 0, 0, 1);
}

void eden_ec::CEDENScene::Update(float dt) {
	_totalTime += dt;
	if (_totalTime >= 3.5f) {
		eden::SceneManager::Instance()->PopScene();
		eden::Master::Instance()->GetLoadScene()();
	}
}