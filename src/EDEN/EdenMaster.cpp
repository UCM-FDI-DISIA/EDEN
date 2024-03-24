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

bool eden::Master::_initialized = false;

eden::Master::Master()
{
	// la comprobación de que se haya podido inicializar el RenderManager ahora se hace dentro del propio RenderManager.
	_renderManager = eden_render::RenderManager::Instance("EDEN Engine");

	if (!_renderManager->couldInitialize()) delete _renderManager;

	_inputManager = eden_input::InputManager::Instance();
	_scnManager = SceneManager::Instance();
	_physicsManager = physics_manager::PhysicsManager::Instance();

	_initialized = true;
}

void eden::Master::CloseApplication() {
	std::cout << "---------------------\n\n\n\n\nCLOSING APPLITACION\n\n\n\n\n---------------------\n\n\n\n\n";
}

eden::Master::~Master()
{
	delete _scnManager;
	delete _inputManager;
	if(_renderManager != nullptr && _renderManager->couldInitialize()) 
		delete _renderManager;

	delete _physicsManager;
	Singleton::~Singleton();
}

void eden::Master::Loop()
{
	const std::chrono::steady_clock::time_point loopStartTime = std::chrono::high_resolution_clock::now();

	std::chrono::steady_clock::time_point frameStartTime, frameEndTime;

	float lastPhysicsUpdateTime = 0;
	
	while (!exit) {
		int numPU = (int) ((_elapsedTime - lastPhysicsUpdateTime) / (_physicsUpdateTimeInterval));
		if (numPU > 0) {
			_physicsManager->UpdatePositions();
			for (int i = 0; i < numPU; ++i) {
				_physicsManager->updateSimulation(_physicsUpdateTimeInterval);
			}
			_physicsManager->ResolvePositions();
		}
		lastPhysicsUpdateTime = lastPhysicsUpdateTime + (numPU * _physicsUpdateTimeInterval);

		frameStartTime = std::chrono::high_resolution_clock::now();

		_inputManager->Update();
		_scnManager->Update(_deltaTime);
		_renderManager->UpdatePositions();
		_renderManager->Update();
		exit = _inputManager->CloseWindowEvent();
		if (_inputManager->ResizedWindowEvent()) {
			_renderManager->ResizedWindow();
		}

		frameEndTime = std::chrono::high_resolution_clock::now();
		_deltaTime = std::chrono::duration<float, std::milli>(frameEndTime - frameStartTime).count() / 1000;
		_elapsedTime = std::chrono::duration<float, std::milli>(frameEndTime - loopStartTime).count() / 1000;
	}
}
