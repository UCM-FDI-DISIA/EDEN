#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#include <iostream>
#endif

#ifdef _MSC_VER
#include <windows.h>
#endif
#include <ctime>
#include <chrono>

#include "ErrorHandler.h"

#include "EdenMaster.h"
#include <RenderManager.h>
#include <PhysicsManager.h>
#include <InputManager.h>
#include "SceneManager.h"
#include "Scene.h"
#include "AudioManager.h"
#include "ScriptManager.h"
#include "ResourcesManager.h"

bool eden::Master::_initialized = false;

eden::Master* eden::Master::getInstance() {
	return static_cast<Master*>(Instance());
}

eden::Master::Master()
{
	eden_resources::ResourcesManager::Instance()->LoadResources();

	// la comprobacion de que se haya podido inicializar el RenderManager ahora se hace dentro del propio RenderManager.
	_renderManager = eden_render::RenderManager::Instance("EDEN Engine");

	if (!_renderManager->couldInitialize()) {
		_renderManager->Close();
		_initialized = false;
		return;
	}
	else {
		//Ejemplo de seteo de Resoluciones por el programador
		std::vector<std::pair<int, int>> resolutions;
		resolutions.push_back({ 640,480 });
		resolutions.push_back({ 1280,720 });
		resolutions.push_back({ 960,540 });
		_renderManager->SetResolutions(resolutions);
	}
	_inputManager = eden_input::InputManager::Instance();
	_scnManager = SceneManager::Instance();
	_physicsManager = physics_manager::PhysicsManager::Instance();
	_audioManager = eden_audio::AudioManager::Instance();

	_initialized = true;
}

void eden::Master::CloseApplication() {
	std::cout << "---------------------\n\n\n\n\nCLOSING APPLICATION\n\n\n\n\n---------------------\n\n\n\n\n";
	exit = true;
}

eden::Master::~Master()
{
	_scnManager->Close();
	_physicsManager->Close();
	_inputManager->Close();
	_audioManager->Close();
	eden_script::ScriptManager::Instance()->Close();

	if (_renderManager != nullptr && _renderManager->couldInitialize()) {

		_renderManager->Close();
	}

	eden_resources::ResourcesManager::Instance()->Close();
}

void eden::Master::Loop()
{
	const std::chrono::steady_clock::time_point loopStartTime = std::chrono::high_resolution_clock::now();

	std::chrono::steady_clock::time_point frameStartTime, frameEndTime;

	float lastPhysicsUpdateTime = 0;
	
	while (!exit) {
		int numPU = (int) ((_elapsedTime - lastPhysicsUpdateTime) / (_physicsUpdateTimeInterval));
		if (numPU > 0) {
			std::string sceneID = _scnManager->GetCurrentScene()->GetSceneID();
			_physicsManager->UpdatePositions(sceneID);
			for (int i = 0; i < numPU; ++i) {
				_physicsManager->updateSimulation(_physicsUpdateTimeInterval, sceneID);
			}
			_physicsManager->ResolvePositions(sceneID);
		}
		lastPhysicsUpdateTime = lastPhysicsUpdateTime + (numPU * _physicsUpdateTimeInterval);

		frameStartTime = std::chrono::high_resolution_clock::now();

		_inputManager->Update();
		_scnManager->Update(_deltaTime);
		_renderManager->UpdatePositions(_scnManager->GetCurrentScene()->GetSceneID());
		_renderManager->Update();
		_audioManager->Update(_deltaTime);
		exit = _inputManager->CloseWindowEvent();
		if (_inputManager->ResizedWindowEvent()) {
			_renderManager->ResizedWindow();
		}

		frameEndTime = std::chrono::high_resolution_clock::now();
		_deltaTime = std::chrono::duration<float, std::milli>(frameEndTime - frameStartTime).count() / 1000;
		_elapsedTime = std::chrono::duration<float, std::milli>(frameEndTime - loopStartTime).count() / 1000;
	}
}
