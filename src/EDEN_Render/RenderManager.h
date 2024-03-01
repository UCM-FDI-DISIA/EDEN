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
typedef SDL_Window NativeWindowType;

struct NativeWindowPair
{
	Ogre::RenderWindow* render = nullptr;
	NativeWindowType* native = nullptr;
};

namespace eden_render
{
	class RenderManager : public Ogre::FrameListener, public Singleton<RenderManager>
	{
	public:
		friend Singleton<RenderManager>;

		~RenderManager() override;

		void InitManager(const std::string& appName = OGRE_VERSION_NAME);
		void CloseManager();
		void Update();
		void CloseWindow();

	protected:
		bool InitialiseRTShaderSystem();
		void DestroyRTShaderSystem();
		virtual void Setup();
		virtual void CreateRoot();
		virtual bool OneTimeConfig();
		void SetWindowGrab(bool grab);
		virtual void LocateResources();
		virtual void LoadResources();
		virtual void Shutdown();
		virtual NativeWindowPair CreateNewWindow(const std::string& name);
		explicit RenderManager(const std::string& appName = OGRE_VERSION_NAME);

		Ogre::Root* _root;        // raíz de OGRE
		Ogre::SceneManager* _sceneMngr;        // escena OGRE
		NativeWindowPair _window; // ventana ppal

		Ogre::FileSystemLayer* _fsLayer; // File system abstraction layer
		bool _firstRun;
		std::string _appName; // nombre de la ventana
		std::string _solutionPath;
		const std::string _resourcesPath = "assets\\";

		std::string _rtShaderLibPath;
		Ogre::RTShader::ShaderGenerator* _shaderGenerator; // The Shader generator instance.
		void* _materialMgrListener; // Shader generator material manager listener.
	};
}

#endif // RENDER_MANAGER_H_
