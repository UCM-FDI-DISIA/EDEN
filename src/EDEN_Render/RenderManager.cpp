#include "RenderManager.h"

#include <OgreRoot.h>
#include <OgreGpuProgramManager.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreDataStream.h>
#include <OgreFileSystemLayer.h>
// #include <OgreWindowEventUtilities.h>

RenderManager::RenderManager(const std::string& appName)
{
	mAppName = appName;
	mFSLayer = new Ogre::FileSystemLayer(mAppName);
	mRoot = nullptr;
	mFirstRun = true;

	mShaderGenerator = nullptr;
	mMaterialMgrListener = nullptr;
}

RenderManager::~RenderManager()
{
	delete mFSLayer;
}

Ogre::RenderWindow* RenderManager::getRenderWindow() const
{
	return mWindow.render;
}

Ogre::Root* RenderManager::getRoot() const
{
	return mRoot;
}

void RenderManager::initApp()
{
	createRoot();

	if (oneTimeConfig()) {
		setup();
	}
}

void RenderManager::closeApp()
{
	if (mRoot != nullptr) {
		mRoot->saveConfig();
	}
	shutdown();
	delete mRoot;
	mRoot = nullptr;
}

void RenderManager::createRoot()
{
	std::string pluginsPath;
	pluginsPath = mFSLayer->getConfigFilePath("plugins.cfg");

	if (!Ogre::FileSystemLayer::fileExists(pluginsPath)) {
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg", "RenderManager::createRoot");
	}
	mSolutionPath = pluginsPath;
	

	mRoot = new Ogre::Root(pluginsPath, mFSLayer->getWritablePath("ogre.cfg"), mFSLayer->getWritablePath("ogre.log"));

	// mOverlaySystem = new Ogre::OverlaySystem;
}

void RenderManager::shutdown()
{
	destroyRTShaderSystem();

	if (mWindow.render != nullptr) {
		mRoot->destroyRenderTarget(mWindow.render);
		mWindow.render = nullptr;
	}

	// delete mOverlaySystem;
	// mOverlaySystem = nullptr;

	if (mWindow.native != nullptr) {
		SDL_DestroyWindow(mWindow.native);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		mWindow.native = nullptr;
	}
}

void RenderManager::setup()
{
	mRoot->initialise(false);
	createWindow(mAppName);
	setWindowGrab(false);

	mRoot->showConfigDialog(OgreBites::getNativeConfigDialog());

	locateResources();
	initialiseRTShaderSystem();
	loadResources();

	mRoot->addFrameListener(this);
}

bool RenderManager::oneTimeConfig()
{
	if (!mRoot->restoreConfig()) {
		return mRoot->showConfigDialog(OgreBites::getNativeConfigDialog());
	}
	else return true;
}

bool RenderManager::initialiseRTShaderSystem()
{
	if (Ogre::RTShader::ShaderGenerator::initialize()) {
		mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

		if (mRTShaderLibPath.empty()) return false;

		if (!mMaterialMgrListener) {
			mMaterialMgrListener = new SGTechniqueResolverListener(mShaderGenerator);
			Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
		}
	}

	return true;
}

void RenderManager::destroyRTShaderSystem()
{
	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	if (mMaterialMgrListener != nullptr) {
		Ogre::MaterialManager::getSingleton().removeListener(mMaterialMgrListener);
		delete mMaterialMgrListener;
		mMaterialMgrListener = nullptr;
	}

	if (mShaderGenerator != nullptr) {
		Ogre::RTShader::ShaderGenerator::destroy();
		mShaderGenerator = nullptr;
	}
}

NativeWindowPair RenderManager::createWindow(const std::string& name)
{
	uint32_t w, h;
	Ogre::NameValuePairList miscParams;

	Ogre::ConfigOptionMap ropts = mRoot->getRenderSystem()->getConfigOptions();

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

	mWindow.native = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(mWindow.native, &wmInfo);

	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	mWindow.render = mRoot->createRenderWindow(name, w, h, false, &miscParams);
	return mWindow;
}

void RenderManager::setWindowGrab(bool _grab)
{
	SDL_bool grab = SDL_bool(_grab);
	SDL_SetWindowGrab(mWindow.native, grab);
	// SDL_SetRelativeMouseMode(grab);
	SDL_ShowCursor(grab);
}

void RenderManager::loadResources()
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void RenderManager::locateResources()
{
	Ogre::ConfigFile cf;

	std::string resourcesPath = mFSLayer->getConfigFilePath("resources.cfg");
	if (Ogre::FileSystemLayer::fileExists(resourcesPath)) {
		cf.load(resourcesPath);
	}
	else {
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			Ogre::FileSystemLayer::resolveBundlePath(mSolutionPath + "\\media"),
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

	OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

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

	mRTShaderLibPath = arch + "/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/materials", type, sec);

	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/HLSL", type, sec);
	}
}

void RenderManager::pollEvents()
{
}