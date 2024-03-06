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
	class RenderObject;
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
		friend render_wrapper::RenderObject;
		friend render_wrapper::CameraWrapper;
		
		/// @brief Destructora
		~RenderManager() override;

		/// @brief Destruye la ra�z y guarda su configuraci�n final en caso de haber sido destru�da
		/// previamente y llama posteriormente al m�todo Shutdown
		void CloseManager();

		/// @brief Ejecuta un ciclo de renderizado (ventana y ra�z)
		void Update();

		/// @brief Destructora de la ventana de SDL
		void CloseWindow();

	protected:
		/// @brief Inicializa el sistema de sombreado de trazado de rayos
		bool InitialiseRTShaderSystem();

		/// @brief Destruye el sistema de sombreado de trazado de rayos
		void DestroyRTShaderSystem();

		/// @brief Inicializaci�n de Ogre a trav�s de su ra�z, ventana, RTShaderSystem
		virtual void Setup();

		/// @brief Creaci�n de la ra�z de Ogre de la escena
		virtual void CreateRoot();

		/// @brief Activaci�n / desactivaci�n de la posibilidad de modificar la
		/// posici�n de la ventana
		/// @param grab Estado de movilidad de la ventana
		void SetWindowGrab(bool grab);

		/// @brief Localizaci�n de archivos para Ogre
		virtual void LocateResources();

		/// @brief Carga de archivos para Ogre
		virtual void LoadResources();

		/// @brief Cierre de ventana de SDL, as� como el RTShaderSystem
		virtual void Shutdown();

		/// @brief Creaci�n de la ventana de Ogre y SDL
		/// @param name Nombre de la ventana
		virtual NativeWindowPair CreateNewWindow(const std::string& name);

		/// @brief Constructora
		/// @param appName Nombre de la ventana
		explicit RenderManager(const std::string& appName = "TEST_APP");


		/// @brief Ra�z de Ogre
		Ogre::Root* _root;

		/// @brief Gestor de escenas
		Ogre::SceneManager* _sceneMngr;

		/// @brief Ventana principal
		NativeWindowPair _window;

		/// @brief Capa de abstracci�n del sistema de archivos
		Ogre::FileSystemLayer* _fsLayer;
		bool _firstRun;

		/// @brief Nombre de la ventana
		std::string _appName;

		/// @brief Localizaci�n de recursos de Ogre
		std::string _solutionPath;

		/// @brief Localizaci�n de recursos de la aplicaci�n
		const std::string _resourcesPath = "assets\\";

		/// @brief Localizaci�n de librer�a del RTShader
		std::string _rtShaderLibPath;

		/// @brief Instancia de generador de sombreado
		Ogre::RTShader::ShaderGenerator* _shaderGenerator;

	private:

		/// @brief Inicializa la librer�a de renderizado,
		/// crea la ventana de renderizado, localiza y carga los recursos (.mesh, .material, etc)
		/// e inicializa los shaders
		/// @param appName Nombre de la ventana
		void InitManager(const std::string& appName);
	};
}

#endif // RENDER_MANAGER_H_
