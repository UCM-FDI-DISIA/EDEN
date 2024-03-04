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

#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
#include <OgreShaderGenerator.h>
#include <OgreMaterialManager.h>

eden_render::RenderManager::RenderManager(const std::string& appName)
{
	_appName = appName;
	_root = nullptr;
	_firstRun = true;
	_shaderGenerator = nullptr;
}

eden_render::RenderManager::~RenderManager()
{
	delete _fsLayer;
}

void eden_render::RenderManager::InitManager(const std::string& appName)
{
	_appName = appName;
	_fsLayer = new Ogre::FileSystemLayer(_appName);

	CreateRoot();
	Setup();

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
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(1, 1, 1);
	Ogre::SceneNode* mLightNode = _sceneMngr->getRootSceneNode()->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(1, -1, 0));

	Ogre::SceneNode* cuerpoNode = _sceneMngr->getRootSceneNode()->createChildSceneNode();
	Ogre::Vector3 cuerpoScale = { 0.2, 0.2, 0.2 };
	Ogre::Entity* ent;

	ent = _sceneMngr->createEntity("cube.mesh");
	ent->setMaterialName("Practica1/rojo"); 
	cuerpoNode->attachObject(ent);
	cuerpoNode->setScale(cuerpoScale);
	cuerpoNode->setPosition({ 70,-10,-10 });
	cuerpoNode->yaw(Ogre::Degree(45));
	cuerpoNode->pitch(Ogre::Degree(45));
	camNode->setDirection({ 1,0,0 });
	cuerpoNode = _sceneMngr->getRootSceneNode()->createChildSceneNode();

}

void eden_render::RenderManager::Update()
{	
	_root->renderOneFrame();
	_window.render->update();
}

void eden_render::RenderManager::CloseWindow() {
	SDL_DestroyWindow(_window.native);
	SDL_Quit();
}

void eden_render::RenderManager::CloseManager()
{
	if (_root != nullptr) {
		_root->saveConfig();
	}
	Shutdown();
	delete _root;
	_root = nullptr;
}

void eden_render::RenderManager::CreateRoot()
{
	std::string pluginsPath;
	std::string nameFile = "plugins.cfg";
	pluginsPath = _fsLayer->getConfigFilePath(nameFile);

	if (!Ogre::FileSystemLayer::fileExists(pluginsPath)) {
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg", "RenderManager::createRoot");
	}
	_solutionPath = pluginsPath;
	_solutionPath.resize(_solutionPath.size() - nameFile.size());

	_root = new Ogre::Root(pluginsPath, _fsLayer->getWritablePath("ogre.cfg"), _fsLayer->getWritablePath("ogre.log"));

	// mOverlaySystem = new Ogre::OverlaySystem;
}

void eden_render::RenderManager::Shutdown()
{
	DestroyRTShaderSystem();

	if (_window.render != nullptr) {
		_root->destroyRenderTarget(_window.render);
		_window.render = nullptr;
	}

	// delete mOverlaySystem;
	// mOverlaySystem = nullptr;

	if (_window.native != nullptr) {
		SDL_DestroyWindow(_window.native);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		_window.native = nullptr;
	}
}

void eden_render::RenderManager::Setup()
{
	_root->showConfigDialog(nullptr);
	_root->initialise(false);
	CreateNewWindow(_appName);
	SetWindowGrab(false);

	LocateResources();
	InitialiseRTShaderSystem();
	LoadResources();
}

bool eden_render::RenderManager::InitialiseRTShaderSystem()
{
	if (Ogre::RTShader::ShaderGenerator::initialize()) {
		_shaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

		if (_rtShaderLibPath.empty()) return false;
	}

	return true;
}

void eden_render::RenderManager::DestroyRTShaderSystem()
{
	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

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
	}
	else {
		std::string path = _solutionPath;
		path.append(_resourcesPath);
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			Ogre::FileSystemLayer::resolveBundlePath(path),
			"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	}

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
