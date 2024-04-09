#include "export.h"

#include <iostream>
#include <filesystem>

#include "ErrorHandler.h"

/// Engine Loop3
#include "EdenMaster.h"

/// Entity-Component
#include "Entity.h"
#include "Component.h"
#include "ComponentFactory.h"
#include "TestComponent.h"
#include "Transform.h"
#include "CMeshRenderer.h"

/// Engine Render
#include "CImage.h"
#include "CText.h"
#include "CButton.h"
#include "CCursor.h"
#include "CCamera.h"
#include "CParticleEmitter.h"

/// Engine Physics
#include "CRigidBody.h"
#include "CLuaBehaviour.h"

// Engine Script
#include <ScriptManager.h>
#include "SceneManager.h"
#include "Scene.h"

// Engine Audio
#include "CAudioEmitter.h"
#include "CAudioListener.h"

#include "Hito1Prueba.h"
#include "CAnimator.h"

#include "RenderManager.h"

#include <string>

#include <Windows.h>

void RegisterComponents() {
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CTransform>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CMeshRenderer>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CCamera>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CImage>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CText>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::Hito1Prueba>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CAnimator>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CButton>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CLuaBehaviour>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CCursor>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CRigidBody>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CMeshRenderer>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CParticleEmitter>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CAudioEmitter>();
	eden_ec::ComponentFactory::Instance()->RegisterComponent<eden_ec::CAudioListener>();
}

void eden_export::InitEDEN() {
	// Registro de componentes
	RegisterComponents();

	// Cogemos una instancia del manejador de errores
	// errorHandler = eden_error::ErrorHandler::Instance();

	master = eden::Master::Instance();
}

void eden_export::RunEDEN() {
	master->Loop();
}

void eden_export::StopEDEN() {
	master->Close();
	// errorHandler->Close();
}