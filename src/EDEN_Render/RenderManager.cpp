#include "RenderManager.h"

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

#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>

#include <OgreShaderGenerator.h>
#include <OgreMaterialManager.h>
#include <iostream>
#include "Node.h"
#include "Transform.h"
#include "Entity.h"

eden_render::RenderManager::RenderManager(const std::string& appName)
{
	_appName = appName; // asigna el nombre de la ventana
	_root = nullptr; // pone la ra�z a nulo
	_firstRun = true; // activa la primer inicializaci�n
	_shaderGenerator = nullptr; // y mantiene el generador de sombreado a nulo

	try
	{
		InitManager(appName);
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << "\n";
		_initialized = false;
	}
}

eden_render::RenderManager::~RenderManager()
{
	CloseManager();
	delete _fsLayer; // borra el sistema de archivos
}

void eden_render::RenderManager::InitManager(const std::string& appName)
{
	_appName = appName; // renombra el nombre de aplicaci�n
	_fsLayer = new Ogre::FileSystemLayer(_appName); // crea un nuevo sistema de archivos

	InitializeLib(); // crea la raíz
	Setup(); // y arranca la inicialización base

	_sceneMngr = _root->createSceneManager();
	_sceneMngr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
	_shaderGenerator->addSceneManager(_sceneMngr);

	// create the camera
	Ogre::Camera* cam = _sceneMngr->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	Ogre::SceneNode* camNode = _sceneMngr->getRootSceneNode()->createChildSceneNode("nCam");
	camNode->attachObject(cam);
	camNode->setPosition({ 0,0,0 });
	cam->getRealDirection();
	Ogre::Viewport* vp = _window.render->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.9, 0.7, 0.7));

	Ogre::Light* luz = _sceneMngr->createLight("Luz");
	luz->setType(Ogre::Light::LT_POINT);
	luz->setDiffuseColour(10, 10, 10);
	Ogre::SceneNode* mLightNode = _sceneMngr->getRootSceneNode()->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(1, -1, 0));

	/*Ogre::SceneNode* cuerpoNode = _sceneMngr->getRootSceneNode()->createChildSceneNode();
	Ogre::Vector3 cuerpoScale = { 0.2, 0.2, 0.2 };
	Ogre::Entity* ent;

	ent = _sceneMngr->createEntity("cube.mesh");
	ent->setMaterialName("Practica1/rojo"); 
	cuerpoNode->attachObject(ent);
	cuerpoNode->setScale(cuerpoScale);
	cuerpoNode->setPosition({ 70,-10,-10 });
	cuerpoNode->yaw(Ogre::Degree(45));
	cuerpoNode->pitch(Ogre::Degree(45));
	cuerpoNode = _sceneMngr->getRootSceneNode()->createChildSceneNode();*/
	camNode->setDirection({ 1,0,0 });


	_overlaySys = new Ogre::OverlaySystem();
}

void eden_render::RenderManager::Update()
{	
	_root->renderOneFrame(); // renderiza la ra�z de Ogre
	_window.render->update(); // renderiza la ventana de SDL
}

void eden_render::RenderManager::CloseWindow() {
	SDL_DestroyWindow(_window.native); // destruye la ventana de SDL
	SDL_Quit(); // y cierra la instancia de SDL
}

void eden_render::RenderManager::CloseManager()
{
	Shutdown(); // llama al cierre de la ventana
	delete _root; // borra la ra�z
	_root = nullptr; // y la pone a nulo
	_overlaySys = nullptr;
}

void eden_render::RenderManager::InitializeLib()
{
	std::string pluginsPath; // localizaci�n base de los plugins
	std::string nameFile = "plugins.cfg";
	pluginsPath = _fsLayer->getConfigFilePath(nameFile); // consigue la direcci�n gracias al sistema de archivos

	if (!Ogre::FileSystemLayer::fileExists(pluginsPath)) { // si no existe el plugin -> excepción de Ogre
		std::string error = "RenderManager ERROR in line 121: failed finding file plugins.cfg. Searched on dir: " + pluginsPath + "\n";
		throw std::exception(error.c_str());
	}
	_solutionPath = pluginsPath; // copia la direcci�n de los plugins
	_solutionPath.resize(_solutionPath.size() - nameFile.size()); // y la reajusta

	// crea una nueva raíz en base a los plugins y la configuración base de Ogre
	_root = new Ogre::Root(pluginsPath);

	if (_root != nullptr)
	{
		_root->showConfigDialog(nullptr); // desactiva el diálogo de configuración de Ogre
		_root->initialise(false); // desactiva la inicialización de la raíz de Ogre
	}
	else
	{
		std::string error = "RenderManager ERROR in line 134: failed creating Ogre::Root\n";
		throw std::exception(error.c_str());
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
		SDL_DestroyWindow(_window.native); // la destruye
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		_window.native = nullptr; // y la apunta a nulo
	}
}

void eden_render::RenderManager::Setup()
{
	CreateNewWindow(_appName); // crea la ventana
	SetWindowGrab(false); // permite que el ratón se pueda mover fuera de la ventana

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
		std::string error = "RenderManager ERROR in line 171: failed initializing\n";
		throw std::exception(error.c_str());
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
	mode >> w;
	mode >> token;
	mode >> h;

	miscParams["FSAA"] = ropts["FSAA"].currentValue;
	miscParams["vsync"] = ropts["VSync"].currentValue;
	miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;

	if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_InitSubSystem(SDL_INIT_VIDEO);

	Uint32 flags = SDL_WINDOW_RESIZABLE;

	if (ropts["Full Screen"].currentValue == "Yes") flags = SDL_WINDOW_FULLSCREEN;

	_window.native = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_window.native, &wmInfo);

	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	_window.render = _root->createRenderWindow(name, w, h, false, &miscParams);
	return _window;
}

void eden_render::RenderManager::SetWindowGrab(bool _grab)
{
	SDL_bool grab = SDL_bool(_grab);
	SDL_SetWindowGrab(_window.native, grab);
	// SDL_SetRelativeMouseMode(grab);
	SDL_ShowCursor(grab);
}

void eden_render::RenderManager::LoadResources()
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void eden_render::RenderManager::LocateResources()
{
	Ogre::ConfigFile cf;

	std::string resourcesPath = _fsLayer->getConfigFilePath("resources.cfg");
	if (Ogre::FileSystemLayer::fileExists(resourcesPath)) {
		cf.load(resourcesPath);
		std::string sec, type, arch;
		// go through all specified resource groups
		Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
		for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
			sec = seci->first;
			const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
			Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

			// go through all resource paths
			for (i = settings.begin(); i != settings.end(); i++)
			{
				type = i->first;
				arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
				std::string path = _solutionPath;
				path.append(arch);
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(path, type, sec);
			}
		}

		sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
		const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

		// OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

		arch = genLocs.front().archive->getName();
		type = genLocs.front().archive->getType();

		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(_solutionPath + "materials", type, sec);

		Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);
	}
	else
	{
		std::string error = "RenderManager ERROR in line 241: file resources.cfg not found in path " + resourcesPath +"\n";
		throw std::exception(error.c_str());
	}
}

int eden_render::RenderManager::GetWindowWidth() {
	return _window.render->getWidth();
}

int eden_render::RenderManager::GetWindowHeight() {
	return _window.render->getHeight();
}

void eden_render::RenderManager::UpdatePositions() {
	render_wrapper::Node* nodeMngr = render_wrapper::Node::Instance();
	eden_ec::CTransform* transform;
	for (auto ent : _entities) {
		transform = ent->GetComponent<eden_ec::CTransform>();
		if (transform != nullptr) {
			nodeMngr->SetPosition(transform->GetPosition(), ent->GetEntityID());
			nodeMngr->SetOrientation(transform->GetRotation(), ent->GetEntityID());
			nodeMngr->Scale(transform->GetScale(), ent->GetEntityID());
		}
	}
}

void eden_render::RenderManager::addRenderEntity(eden_ec::Entity* ent) {
	_entities.insert(ent);
}

void eden_render::RenderManager::removeRenderEntity(eden_ec::Entity* ent) {
	_entities.erase(ent);
}
