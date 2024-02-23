#include "RenderManager.h"

#include <OgreRoot.h>
#include <OgreGpuProgramManager.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreDataStream.h>
#include <OgreFileSystemLayer.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>

eden_render::RenderManager::RenderManager(const std::string& appName)
{
	_appName = appName;
	_fsLayer = new Ogre::FileSystemLayer(_appName);
	_root = nullptr;
	_firstRun = true;

	_shaderGenerator = nullptr;
	_materialMgrListener = nullptr;
}

eden_render::RenderManager::~RenderManager()
{
	delete _fsLayer;
}

void eden_render::RenderManager::InitManager()
{
	CreateRoot();

	if (OneTimeConfig()) {
		Setup();
	}
}

void eden_render::RenderManager::StartRendering()
{
	_root->startRendering();
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
	pluginsPath = _fsLayer->getConfigFilePath("plugins.cfg");

	if (!Ogre::FileSystemLayer::fileExists(pluginsPath)) {
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg", "RenderManager::createRoot");
	}
	_solutionPath = pluginsPath;
	

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
	_root->initialise(false);
	CreateNewWindow(_appName);
	SetWindowGrab(false);

	// mRoot->showConfigDialog(OgreBites::getNativeConfigDialog());

	LocateResources();
	InitialiseRTShaderSystem();
	LoadResources();

	// mRoot->addFrameListener(this);
}

bool eden_render::RenderManager::OneTimeConfig()
{
	if (!_root->restoreConfig()) {
		return _root->showConfigDialog(nullptr);
	}
	else return true;

	return true;
}

bool eden_render::RenderManager::InitialiseRTShaderSystem()
{
	//if (Ogre::RTShader::ShaderGenerator::initialize()) {
	//	mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

	//	if (mRTShaderLibPath.empty()) return false;

	//	if (!mMaterialMgrListener) {
	//		mMaterialMgrListener = new SGTechniqueResolverListener(mShaderGenerator);
	//		Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
	//	}
	//}

	return true;
}

void eden_render::RenderManager::DestroyRTShaderSystem()
{
	//Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	//if (mMaterialMgrListener != nullptr) {
	//	Ogre::MaterialManager::getSingleton().removeListener(mMaterialMgrListener);
	//	delete mMaterialMgrListener;
	//	mMaterialMgrListener = nullptr;
	//}

	//if (mShaderGenerator != nullptr) {
	//	Ogre::RTShader::ShaderGenerator::destroy();
	//	mShaderGenerator = nullptr;
	//}
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
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			Ogre::FileSystemLayer::resolveBundlePath(_solutionPath + "\\media"),
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
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

	// OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

	arch = genLocs.front().archive->getName();
	type = genLocs.front().archive->getType();

	// Add locations for supported shader languages
	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
		}
		else
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
		}

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
		}
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
	}

	_rtShaderLibPath = arch + "/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(_rtShaderLibPath + "/materials", type, sec);

	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(_rtShaderLibPath + "/GLSL", type, sec);
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(_rtShaderLibPath + "/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(_rtShaderLibPath + "/GLSL", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(_rtShaderLibPath + "/HLSL", type, sec);
	}
}
