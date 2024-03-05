 #ifndef RENDER_MANAGER_H_
#define RENDER_MANAGER_H_

#include <string>
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
	/// @brief Ventana de renderizado de Ogre
	Ogre::RenderWindow* render = nullptr;

	/// @brief Ventana de renderizado de SDL
	NativeWindowType* native = nullptr;
};
namespace render_wrapper {
	class Node;
	class CameraWrapper;
}
namespace eden_render
{
	class RenderManager : public Singleton<RenderManager>
	{
	public:
		/// @brief Singleton del RenderManager
		friend Singleton<RenderManager>;

		/// @brief Nodo del RenderWrapper
		friend render_wrapper::Node;
		friend render_wrapper::CameraWrapper;
		
		/// @brief Destructora
		~RenderManager() override;

		/// @brief Inicializa la librería de renderizado,
		/// crea la ventana de renderizado, localiza y carga los recursos (.mesh, .material, etc)
		/// e inicializa los shaders
		/// @param appName Nombre de la ventana
		void InitManager(const std::string& appName);

		/// @brief Destruye la raíz y guarda su configuración final en caso de haber sido destruída
		/// previamente y llama posteriormente al método Shutdown
		void CloseManager();

		/// @brief Ejecuta un ciclo de renderizado (ventana y raíz)
		void Update();

		/// @brief Destructora de la ventana de SDL
		void CloseWindow();

	protected:
		/// @brief Inicializa el sistema de sombreado de trazado de rayos
		bool InitialiseRTShaderSystem();

		/// @brief Destruye el sistema de sombreado de trazado de rayos
		void DestroyRTShaderSystem();

		/// @brief Inicialización de Ogre a través de su raíz, ventana, RTShaderSystem
		virtual void Setup();

		/// @brief Creación de la raíz de Ogre de la escena
		virtual void CreateRoot();

		/// @brief Activación / desactivación de la posibilidad de modificar la
		/// posición de la ventana
		/// @param grab Estado de movilidad de la ventana
		void SetWindowGrab(bool grab);

		/// @brief Localización de archivos para Ogre
		virtual void LocateResources();

		/// @brief Carga de archivos para Ogre
		virtual void LoadResources();

		/// @brief Cierre de ventana de SDL, así como el RTShaderSystem
		virtual void Shutdown();

		/// @brief Creación de la ventana de Ogre y SDL
		/// @param name Nombre de la ventana
		virtual NativeWindowPair CreateNewWindow(const std::string& name);

		/// @brief Constructora
		/// @param appName Nombre de la ventana
		explicit RenderManager(const std::string& appName = "TEST_APP");


		/// @brief Raíz de Ogre
		Ogre::Root* _root;

		/// @brief Gestor de escenas
		Ogre::SceneManager* _sceneMngr;

		/// @brief Ventana principal
		NativeWindowPair _window;

		/// @brief Capa de abstracción del sistema de archivos
		Ogre::FileSystemLayer* _fsLayer;
		bool _firstRun;

		/// @brief Nombre de la ventana
		std::string _appName;

		/// @brief Localización de recursos de Ogre
		std::string _solutionPath;

		/// @brief Localización de recursos de la aplicación
		const std::string _resourcesPath = "assets\\";

		/// @brief Localización de librería del RTShader
		std::string _rtShaderLibPath;

		/// @brief Instancia de generador de sombreado
		Ogre::RTShader::ShaderGenerator* _shaderGenerator;
	};
}

#endif // RENDER_MANAGER_H_
