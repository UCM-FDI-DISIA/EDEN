#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include "wtypes.h"
#include <cmath>
#include <map>

// Ogre
#pragma warning(push)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreRoot.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreGpuProgramManager.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreDataStream.h>
#include <OgreFileSystemLayer.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h> 
#include <OgreShaderGenerator.h>
#include <OgreMaterialManager.h>
#pragma warning(pop)

// SDL
#pragma warning(push)
#pragma warning(disable : 26819)
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
#pragma warning(pop)

// EDEN
#include "Transform.h"
#include "Entity.h"
#include "ErrorHandler.h"
#include "CMeshRenderer.h"
#include "CLight.h"
#include "CParticleEmitter.h"

// EDEN_Render
#include "RenderManager.h"
#include "NodeManager.h"
#include "Canvas.h"
#include "CameraWrapper.h"

// EDEN_Managers
#include "ResourcesManager.h"

// STD
#include <vector>

eden_render::RenderManager* eden_render::RenderManager::getInstance() {
	return static_cast<RenderManager*>(Instance());
}

eden_render::RenderManager::RenderManager(const std::string& appName)
{
	_appName = appName; // asigna el nombre de la ventana
	_root = nullptr; // pone la raiz a nulo
	_shaderGenerator = nullptr; // y mantiene el generador de sombreado a nulo
	_resolutions.push_back(_defWindowSize); // setea la resolución default 

	
	try
	{
		InitManager(appName);
	}
	catch (std::exception e)
	{
		_initialized = false;
		eden_error::ErrorHandler::Instance()->HandleException(e);
	}
}

eden_render::RenderManager::~RenderManager()
{
	eden_canvas::Canvas::Instance()->Close();
	CloseManager();
	delete _fsLayer; // borra el sistema de archivos
}

void eden_render::RenderManager::InitManager(const std::string& appName)
{
	_appName = appName; // renombra el nombre de aplicacion
	_fsLayer = new Ogre::FileSystemLayer(_appName); // crea un nuevo sistema de archivos

	InitializeLib(); // crea la raiz
	Setup(); // y arranca la inicializacion base

	_overlaySys = new Ogre::OverlaySystem();
	_currentRenderScene = nullptr;


	///// CAMBIAR A COMPONENTE LIGHT//////
	/*_sceneMngr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
	_shaderGenerator->addSceneManager(_sceneMngr);

	Ogre::Light* luz = _sceneMngr->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(10, 10, 10);
	Ogre::SceneNode* mLightNode = _sceneMngr->getRootSceneNode()->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(1, -1, 0));*/
	///// CAMBIAR A COMPONENTE LIGHT//////

}

Ogre::SceneManager* eden_render::RenderManager::GetOgreSceneManager(std::string sceneID)
{
	auto it = _renderScenes.find(sceneID);
	if (it != _renderScenes.end())
		return it->second->GetRenderScene();
	else
		return nullptr;
}

void eden_render::RenderManager::Update()
{
	_root->renderOneFrame(); // renderiza la raiz de Ogre
	if (_resized) {
		_resized = false;
		eden_canvas::Canvas::Instance()->Resize();
	}
	if (!_canvasInit) {
		eden_canvas::Canvas::Instance()->InitCanvas();
		_canvasInit = true;
	}
}

void eden_render::RenderManager::CloseWindow() {
	SDL_DestroyWindow(_window.native); // destruye la ventana de SDL
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	SDL_Quit(); // y cierra la instancia de SDL
}

void eden_render::RenderManager::CloseManager()
{
	Shutdown(); // llama al cierre de la ventana
	if (couldInitialize()) {
		for (auto it : _renderScenes)
		{
			delete it.second;
		}

		delete _overlaySys;
		_overlaySys = nullptr;
		delete _root; // borra la raiz
		_root = nullptr; // y la pone a nulo

	}
}

void eden_render::RenderManager::InitializeLib()
{
	std::string pluginsPath; // localizacion base de los plugins
	std::string nameFile = "plugins.cfg";
	pluginsPath = _fsLayer->getConfigFilePath(nameFile); // consigue la direccion gracias al sistema de archivos

	if (!Ogre::FileSystemLayer::fileExists(pluginsPath)) { // si no existe el plugin -> excepción de Ogre
		eden_error::ErrorHandler::Instance()->Exception("RenderManager ERROR in line 121", "failed finding file plugins.cfg. Searched on dir: " + pluginsPath + "\n");
	}
	_solutionPath = pluginsPath; // copia la direccion de los plugins
	_solutionPath.resize(_solutionPath.size() - nameFile.size()); // y la reajusta

	// crea una nueva raiz en base a los plugins y la configuracion base de Ogre
	_root = new Ogre::Root(pluginsPath);

	if (_root != nullptr)
	{
		_root->showConfigDialog(nullptr); // desactiva el dialogo de configuracion de Ogre
		_root->initialise(false); // desactiva la inicializacion de la raíz de Ogre
	}
	else
	{
		eden_error::ErrorHandler::Instance()->Exception("RenderManager ERROR in line 134","Failed creating Ogre::Root\n");
	}
}

void eden_render::RenderManager::Shutdown()
{
	DestroyRTShaderSystem(); // destruye el sistema de sombreado

	if (_window.render != nullptr) { // si sigue habiendo ventana de Ogre
		_root->destroyRenderTarget(_window.render); // la destruye
		_window.render = nullptr; // y la apunta a nulo
	}

	if (_window.native != nullptr) { // si sigue habiendo ventana de SDL
		CloseWindow();
		_window.native = nullptr; // y la apunta a nulo
	}
}

void eden_render::RenderManager::Setup()
{
	CreateNewWindow(_appName); // crea la ventana
	SetWindowGrab(false); // permite que el raton se pueda mover fuera de la ventana

	LocateResources(); // localiza los recursos
	InitialiseRTShaderSystem(); // arranca el sistema de sombreado
	LoadResources(); // y carga los recursos
}

void eden_render::RenderManager::InitialiseRTShaderSystem()
{
	if (Ogre::RTShader::ShaderGenerator::initialize()) {
		_shaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	}
	else {
		eden_error::ErrorHandler::Instance()->Exception("RenderManager ERROR in line 171", "Failed Initializing\n");
	}
}

void eden_render::RenderManager::DestroyRTShaderSystem()
{
	if (_shaderGenerator != nullptr) {
		Ogre::RTShader::ShaderGenerator::destroy();
		_shaderGenerator = nullptr;
	}
}


NativeWindowPair eden_render::RenderManager::CreateNewWindow(const std::string& name)
{
	uint32_t w, h;
	Ogre::NameValuePairList miscParams;

	Ogre::ConfigOptionMap ropts = _root->getRenderSystem()->getConfigOptions();

	std::istringstream mode(ropts["Video Mode"].currentValue);
	std::string token;
	mode >> token;

	//TAMANIO FULL SCREEN
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	_fullW = desktop.right;
	_fullH = desktop.bottom;
	w = _defWindowSize.first;
	h = _defWindowSize.second;
	_isFullScreen = false;
	miscParams["FSAA"] = ropts["FSAA"].currentValue;
	miscParams["vsync"] = ropts["VSync"].currentValue;
	miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;

	if (!SDL_WasInit(SDL_INIT_EVERYTHING)) SDL_InitSubSystem(SDL_INIT_EVERYTHING);
	Uint32 flags = SDL_WINDOW_RESIZABLE;

	if (ropts["Full Screen"].currentValue == "Yes") flags = SDL_WINDOW_FULLSCREEN;

	_window.native = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);
	_currW = w;
	_currH = h;

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_window.native, &wmInfo);

	

#ifdef SDL_VIDEO_DRIVER_WINDOWS
	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));
#endif
#ifdef SDL_VIDEO_DRIVER_COCOA
	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.cocoa.window));
#endif

	_window.render = _root->createRenderWindow(name, w, h, false, &miscParams);

	return _window;
}

void eden_render::RenderManager::ShowCursor(bool _cursor) {
	SDL_ShowCursor(SDL_bool(_cursor));
}

void eden_render::RenderManager::SetRelativeMouseMode(bool _relative) {
	SDL_SetRelativeMouseMode(SDL_bool(_relative));
}

void eden_render::RenderManager::SetWindowGrab(bool _grab)
{
	SDL_bool grab = SDL_bool(_grab);
	SDL_SetWindowGrab(_window.native, grab);
	// SDL_SetRelativeMouseMode(grab);
	ShowCursor(_grab);
}

void eden_render::RenderManager::LoadResources()
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void eden_render::RenderManager::LocateResources()
{
	std::string type = RESOURCES_LOCATION_TYPE;
	std::string sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	std::vector<std::string> routes = { MESH_ROUTE,MATERIALS_ROUTE,UI_ROUTE,FONTS_ROUTE,DEFAULT_ROUTE };
	for (std::string& it : routes) {
		std::string path = _solutionPath;
		path.append(it);	
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(path, type, sec);
	}
	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);
}

int eden_render::RenderManager::GetWindowWidth() {
	return _window.render->getWidth();
}

int eden_render::RenderManager::GetWindowHeight() {
	return _window.render->getHeight();
}

void eden_render::RenderManager::UpdatePositions(std::string sceneID) {
	render_wrapper::NodeManager* nodeMngr = render_wrapper::NodeManager::Instance();
	eden_ec::CTransform* transform;
	std::unordered_set<eden_ec::Entity*>* currentEnts = &_renderScenes[sceneID]->_entities;
	for (auto ent : (*currentEnts)) {
		transform = ent->GetComponent<eden_ec::CTransform>();
		if (transform != nullptr) {
			nodeMngr->SetPosition(transform->GetPosition(), ent->GetEntityID(), ent->GetSceneID());
			nodeMngr->SetOrientation(transform->GetRotation(), ent->GetEntityID(), ent->GetSceneID());
			nodeMngr->Scale(transform->GetScale(), ent->GetEntityID(), ent->GetSceneID());
		}
		else {
			eden_error::ErrorHandler::Instance()->Warning("Render Entity '" + ent->GetEntityID() + "' has no Transform");
		}
	}
}

void eden_render::RenderManager::AddRenderEntity(eden_ec::Entity* ent) {
	std::unordered_map<std::string, InfoRenderWorld*>::iterator it = _renderScenes.find(ent->GetSceneID());
	if (it != _renderScenes.end())
	{
		it->second->_entities.insert(ent);
	}
	else
	{
		std::string message = "RenderManager ERROR in line 317 could not find scene: " + ent->GetSceneID()
			+ "\n";

		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
	}
}

void eden_render::RenderManager::RemoveRenderEntity(eden_ec::Entity* ent) {
	std::unordered_map<std::string, InfoRenderWorld*>::iterator it = _renderScenes.find(ent->GetSceneID());
	if (it != _renderScenes.end())
	{
		it->second->_entities.erase(ent);
	}
	else
	{
		std::string message = "RenderManager ERROR in line 332 could not find scene: " + ent->GetSceneID()
			+ "\n";

		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
	}
}

void eden_render::RenderManager::ResizedWindow() {
	_window.render->windowMovedOrResized();
	_resized = true;
}

void eden_render::RenderManager::ChangeWindowSize(int w, int h)
{
	SDL_SetWindowSize(_window.native, w, h);
	SDL_SetWindowPosition(_window.native, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	ResizedWindow();
}

void eden_render::RenderManager::FullScreen()
{
	uint32_t w, h;
	if (_isFullScreen) {
		w = _currW;
		h = _currH;
	}
	else {
		w = _fullW;
		h = _fullH;
	}

	ChangeWindowSize(w, h);
	_isFullScreen = !_isFullScreen;
}

void eden_render::RenderManager::SetResolutions(std::vector<std::pair<int, int>> resolutions)
{
	std::map<int, std::pair<int, int>> aux;

	std::pair<int, int> res;
	for (int i = 0; i < resolutions.size(); i++) {
		if (resolutions[i].first < _fullW && resolutions[i].second < _fullH) {
			res = { resolutions[i].first,resolutions[i].second };
			aux[res.first + (sqrt(res.first * res.first + res.second * res.second))] = res;
		}
	}
	_resolutions.clear();
	for (auto it = aux.begin(); it != aux.end(); it++) {
		_resolutions.push_back((*it).second);
	}

	if (_resolutions.empty())_resolutions.push_back(_defWindowSize);
	_currRes = 0;
}

std::pair<int, int> eden_render::RenderManager::GetResolution()
{
	return { _currW,_currH };
}

void eden_render::RenderManager::ChangeResolution()
{
	ChangeWindowSize(_resolutions[_currRes].first, _resolutions[_currRes].second);
	_currW = _resolutions[_currRes].first;
	_currH = _resolutions[_currRes].second;
}

void eden_render::RenderManager::NextResolutuion()
{
	_currRes = (_currRes + 1) % _resolutions.size();
}

void eden_render::RenderManager::PreviousResolution()
{
	_currRes--;
	if (_currRes < 0)_currRes = _resolutions.size() - 1;
}

render_wrapper::CameraWrapper* eden_render::RenderManager::GetCamera(eden_ec::Entity* ent)
{
	auto sceneIt = _renderScenes.find(ent->GetSceneID());
	if (sceneIt == _renderScenes.end())
	{
		std::string message = "RenderManager ERROR in line 355 could not find scene: " + ent->GetSceneID()
			+ "\n";

		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
		return nullptr;
	}
	else
	{
		if (sceneIt->second->_cameraWrapper == nullptr)
		{
			sceneIt->second->_cameraWrapper = new render_wrapper::CameraWrapper(ent->GetEntityID(), ent->GetSceneID());
		}
		return sceneIt->second->_cameraWrapper;
	}
}

void eden_render::RenderManager::CreateRenderScene(std::string sceneID)
{
	auto sceneIt = _renderScenes.find(sceneID);
	if (_currentRenderScene != nullptr)
	{
		_shaderGenerator->removeSceneManager(_currentRenderScene->_renderScene);
		eden_canvas::Canvas::Instance()->HideScene(_currentRenderScene->_sceneID);
		ShowEntities(_currentRenderScene->_sceneID, false);
	}
	if (sceneIt == _renderScenes.end())
	{
		InfoRenderWorld* info = new InfoRenderWorld(_root, _overlaySys, sceneID);
		_currentRenderScene = info;
		_renderScenes[sceneID] = info;
		eden_canvas::Canvas::Instance()->addScene(sceneID);
	}
	else

	{
		_currentRenderScene = sceneIt->second;
		_shaderGenerator->addSceneManager(_currentRenderScene->_renderScene);
		if(sceneIt->second->_cameraWrapper != nullptr) sceneIt->second->_cameraWrapper->SetActiveCamera();
		eden_canvas::Canvas::Instance()->ShowScene(_currentRenderScene->_sceneID);
		ShowEntities(_currentRenderScene->_sceneID, true);
	}
	_shaderGenerator->_setActiveSceneManager(_currentRenderScene->_renderScene);
	_root->_setCurrentSceneManager(_currentRenderScene->_renderScene);
	_canvasInit = false;

}

void eden_render::RenderManager::SetRenderScene(std::string sceneID)
{
	auto sceneIt = _renderScenes.find(sceneID);
	if (sceneIt != _renderScenes.end())
	{
		_currentRenderScene = sceneIt->second;
		_shaderGenerator->addSceneManager(_currentRenderScene->_renderScene);
		if (sceneIt->second->_cameraWrapper != nullptr) sceneIt->second->_cameraWrapper->SetActiveCamera();
		eden_canvas::Canvas::Instance()->ShowScene(_currentRenderScene->_sceneID);
		ShowEntities(_currentRenderScene->_sceneID, true);
	}
}

void eden_render::RenderManager::RemoveRenderScene(std::string sceneToRemoveID, std::string newCurrentSceneID)
{
	auto sceneIt = _renderScenes.find(sceneToRemoveID);
	if (sceneIt != _renderScenes.end())
	{
		delete sceneIt->second;
		_renderScenes.erase(sceneIt);
		_currentRenderScene = nullptr;
		render_wrapper::NodeManager::Instance()->RemoveScene(sceneToRemoveID);
		eden_canvas::Canvas::Instance()->removeScene(sceneToRemoveID);

	}
	SetRenderScene(newCurrentSceneID);
}

void eden_render::RenderManager::ShowEntities(std::string sceneID, bool show)
{
	auto sceneIt = _renderScenes.find(sceneID);
	if (sceneIt != _renderScenes.end()) {
		for (eden_ec::Entity* ent : sceneIt->second->_entities) {
			eden_ec::CMeshRenderer* meshEnt = ent->GetComponent<eden_ec::CMeshRenderer>();
			eden_ec::CLight* lightEnt = ent->GetComponent<eden_ec::CLight>();
			eden_ec::CParticleEmitter* partEnt = ent->GetComponent<eden_ec::CParticleEmitter>();

			if (meshEnt != nullptr) meshEnt->SetInvisible(!show, true);
			if (lightEnt != nullptr) lightEnt->SetVisibility(show, true);
			if (partEnt != nullptr) 
			{
				partEnt->SetVisible(show, true);
				partEnt->SetActive(show, true);
			}
		}
	}
	else {
		std::string message = "RenderManager ERROR in line 455 scene does not exist: " + sceneID + "\n";

		eden_error::ErrorHandler::Instance()->Warning(message.c_str());
	}
}

eden_render::InfoRenderWorld::InfoRenderWorld(Ogre::Root* root, Ogre::OverlaySystem* overlaySystem, std::string sceneID)
{
	_root = root;
	_overlaySystem = overlaySystem;
	_sceneID = sceneID;
	//_overlaySys = new Ogre::OverlaySystem();

	_cameraWrapper = nullptr;

	_renderScene = _root->createSceneManager();
	_renderScene->addRenderQueueListener(_overlaySystem);
	_renderScene->setAmbientLight(Ogre::ColourValue(0.2f, 0.2f, 0.2f));

}

eden_render::InfoRenderWorld::~InfoRenderWorld()
{
	if (_cameraWrapper != nullptr) delete _cameraWrapper;
	_renderScene->removeRenderQueueListener(_overlaySystem);
	_renderScene->destroyAllEntities();
	_renderScene->destroyAllAnimations();
	_renderScene->destroyAllAnimationStates();
	if(Ogre::RTShader::ShaderGenerator::getSingletonPtr() != nullptr) Ogre::RTShader::ShaderGenerator::getSingletonPtr()->removeSceneManager(_renderScene);
	
	_root->destroySceneManager(_renderScene);

	_renderScene = nullptr;

}

Ogre::SceneManager* eden_render::InfoRenderWorld::GetRenderScene()
{
	return _renderScene;
}
