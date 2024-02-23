#ifndef RENDER_MANAGER_H_
#define RENDER_MANAGER_H_

#include <string>

#include <OgreFrameListener.h>

#include "Singleton.h"

namespace Ogre {
	class FileSystemLayer;
	class RenderWindow;
	class Root;
	class SceneManager;
	namespace RTShader {
		class ShaderGenerator;
	}
}

class SDL_Window;

class SGTechniqueResolverListener;

typedef SDL_Window NativeWindowType;

/**
link between a renderwindow and a platform specific window
*/
struct NativeWindowPair
{
	Ogre::RenderWindow* render = nullptr;
	NativeWindowType* native = nullptr;
};

/**
Base class responsible for setting up a common context for applications.
Subclass to implement specific event callbacks.
*/
class RenderManager : public Ogre::FrameListener, public Singleton<RenderManager>
{
public:
	friend Singleton<RenderManager>;


	~RenderManager() override;

	/**
	get the main RenderWindow owns the context on OpenGL
	*/
	Ogre::RenderWindow* getRenderWindow() const;

	Ogre::Root* getRoot() const;


	void Init();

	// Ogre::OverlaySystem* getOverlaySystem() const { return mOverlaySystem; }

	/**
	This function initializes the render system and resources.
	*/
	void initApp();

	/**
	This function closes down the application - saves the configuration then shutdowns.
	*/
	void closeApp();

	/**
	Initialize the RT Shader system.
	*/
	bool initialiseRTShaderSystem();

	/**
	Destroy the RT Shader system.
	*/
	void destroyRTShaderSystem();

	/**
	Sets up the context after configuration.
	*/
	virtual void setup();

	/**
	Creates the OGRE root.
	*/
	virtual void createRoot();

	/**
	Configures the startup settings for OGRE. I use the config dialog here,
	but you can also restore from a config file. Note that this only happens
	when you start the context, and not when you reset it.
	*/
	virtual bool oneTimeConfig();

	/**
	When input is grabbed the mouse is confined to the window.
	*/
	void setWindowGrab(bool grab);

	/**
	Finds context-wide resource groups. I load paths from a config file here,
	but you can choose your resource locations however you want.
	*/
	virtual void locateResources();

	/**
	Loads context-wide resource groups. I chose here to simply initialise all
	groups, but you can fully load specific ones if you wish.
	*/
	virtual void loadResources();

	/**
	Cleans up and shuts down the context.
	*/
	virtual void shutdown();

	/**
	process all window events since last call
	*/
	void pollEvents();

	/**
	Create a new render window
	You must use SDL and not an auto-created window as SDL does not get the events otherwise.
	By default the values from ogre.cfg are used for w, h and miscParams.
	*/
	virtual NativeWindowPair createWindow(const std::string& name);

protected:
	explicit RenderManager(const std::string& appName = OGRE_VERSION_NAME);

	Ogre::Root* mRoot;        // ra�z de OGRE
	NativeWindowPair mWindow; // ventana ppal

	Ogre::FileSystemLayer* mFSLayer; // File system abstraction layer
	bool mFirstRun;
	std::string mAppName; // nombre de la ventana
	std::string mSolutionPath;

	std::string mRTShaderLibPath;
	Ogre::RTShader::ShaderGenerator* mShaderGenerator; // The Shader generator instance.
	SGTechniqueResolverListener* mMaterialMgrListener; // Shader generator material manager listener.
};

#endif // RENDER_MANAGER_H_
