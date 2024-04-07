#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_RENDER_MANAGER_H
#define EDEN_RENDER_MANAGER_H

#include <string>
#include <unordered_set>
#include <unordered_map>

#include "Singleton.h"

namespace eden_debug {
	class DebugDrawer;
}

namespace Ogre {
	class FileSystemLayer;
	class RenderWindow;
	class Root;
	class SceneManager;
	class OverlaySystem;
	class OverlayManager;
	namespace RTShader {
		class ShaderGenerator;
	}
}

namespace eden_ec {
	class Entity;
}

namespace eden
{
	class SceneManager;
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
	class NodeManager;
	class RenderObject;
	class CameraWrapper;
}
namespace eden_render
{
	class InfoRenderWorld;
	class RenderManager : public Singleton<RenderManager>
	{
	public:
		/// @brief Singleton del RenderManager
		friend Singleton<RenderManager>;

		/// @brief Clase de debug
		friend eden_debug::DebugDrawer;

		/// @brief Nodo del RenderWrapper
		friend render_wrapper::NodeManager;
		friend render_wrapper::RenderObject;
		friend render_wrapper::CameraWrapper;

		friend eden::SceneManager;
		
		/// @brief Destructora
		~RenderManager() override;

		/// @brief Ejecuta un ciclo de renderizado (ventana y raï¿½z)
		void Update();

		/// @brief Comprueba si ha habido errores en la inicializaci�n
		/// @return True si se ha inicializado bien, False en caso contrario
		inline bool couldInitialize() { return _initialized; }

		int GetWindowWidth();
		int GetWindowHeight();
		
		/// @brief Actualiza todas las posiciones de la escena con su componente Transform
		/// @param sceneID Identificador de la escena
		void UpdatePositions(std::string sceneID);

		/// @brief A�ade una entidad que tenga componentes de renderizado (CMeshRenderer, CCamera, ...) a una escena en concreto
		/// para actualizar su posici�n
		/// @param ent Entidad cuya posici�n va a actualizarse
		void addRenderEntity(eden_ec::Entity* ent);

		/// @brief Quita una entidad de una escena para dejar de actualizar su posici�n
		/// @param ent Entidad que se va a quitar
		void removeRenderEntity(eden_ec::Entity* ent);

		/// @brief Funci�n que deber�a llamarse en el momento en el que la ventana cambia de tama�o
		void ResizedWindow();

		render_wrapper::CameraWrapper* GetCamera(eden_ec::Entity* ent);

	protected:
		Ogre::SceneManager* GetOgreSceneManager();

	private:
		/// @brief Inicializa la librer�a de renderizado,
		/// crea la ventana de renderizado, localiza y carga los recursos (.mesh, .material, etc)
		/// e inicializa los shaders
		/// @param appName Nombre de la ventana
		void InitManager(const std::string& appName);


		/// @brief Inicializa el sistema de sombreado de trazado de rayos
		void InitialiseRTShaderSystem();

		/// @brief Destruye el sistema de sombreado de trazado de rayos
		void DestroyRTShaderSystem();

		/// @brief Inicialización de ventana, RTShaderSystem y recursos
		void Setup();

		/// @brief Creación de la raíz de Ogre de la escena
		void InitializeLib();

		/// @brief Atrapa el ratón en la ventana
		/// @param grab Activa o desactiva la funcionalidad del método
		void SetWindowGrab(bool grab);

		/// @brief Localización de archivos para Ogre
		void LocateResources();

		/// @brief Carga de archivos para Ogre
		void LoadResources();

		/// @brief Cierre de ventana de SDL, así como el RTShaderSystem
		void Shutdown();

		/// @brief Destructora de la ventana de SDL
		void CloseWindow();

		/// @brief Destruye la ra�z y llama posteriormente al m�todo Shutdown
		void CloseManager();

		/// @brief Creaciï¿½n de la ventana de Ogre y SDL
		/// @param name Nombre de la ventana
		NativeWindowPair CreateNewWindow(const std::string& name);

		/// @brief Constructora
		/// @param appName Nombre de la ventana
		explicit RenderManager(const std::string& appName = "TEST_APP");

		/// @brief Crea una nueva escena, si existe actualiza la escena actual 
		/// 
		void CreateRenderScene(std::string sceneID);

		/// @brief 
		/// @param sceneID 
		void RemoveRenderScene(std::string sceneToRemoveID, std::string newCurrentSceneID);

		/// @brief Raiz de Ogre
		Ogre::Root* _root;

		/// @brief Sistema de Overlay
		Ogre::OverlaySystem* _overlaySys;

		/// @brief Gestor de escenas
		std::unordered_map<std::string, InfoRenderWorld*> _renderScenes;

		/// @brief Escena actual de render
		Ogre::SceneManager* _currentRenderScene;

		/// @brief Ventana principal
		NativeWindowPair _window;

		/// @brief Capa de abstraccion del sistema de archivos
		Ogre::FileSystemLayer* _fsLayer;
		bool _firstRun;

		/// @brief Nombre de la ventana
		std::string _appName;

		/// @brief Localizaciï¿½n de recursos de Ogre
		std::string _solutionPath;

		/// @brief Localizaciï¿½n de recursos de la aplicaciï¿½n
		const std::string _resourcesPath = "assets\\";

		/// @brief Localizaciï¿½n de librerï¿½a del RTShader
		std::string _rtShaderLibPath;

		/// @brief Instancia de generador de sombreado
		Ogre::RTShader::ShaderGenerator* _shaderGenerator;

		/// @brief Flag para saber si se ha podido inicializar el manager
		bool _initialized = true;

		/// @brief Flag para saber si el canvas se ha inicializado
		bool _canvasInit = false;

		/// @brief Flag para saber si la ventana ha sido escalada
		bool _resized = false;
	};

	class InfoRenderWorld
	{
		friend RenderManager;
	public:
		InfoRenderWorld(Ogre::Root* root, Ogre::OverlaySystem* overlaySystem);
		~InfoRenderWorld();
	private:
		Ogre::SceneManager* _renderScene;
		/// @brief Conjunto de entidades para actualizar su posici�n
		std::unordered_set<eden_ec::Entity*> _entities;
		Ogre::OverlaySystem* _overlaySystem;
		Ogre::Root* _root;
		Ogre::SceneManager* GetRenderScene();
		render_wrapper::CameraWrapper* _cameraWrapper;
	};
}

#endif // RENDER_MANAGER_H_
