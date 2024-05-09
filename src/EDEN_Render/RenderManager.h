#ifndef EDEN_RENDER_MANAGER_H
#define EDEN_RENDER_MANAGER_H

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "Singleton.h"

#define RESOURCES_LOCATION_TYPE "FileSystem"
#define EDEN_RENDER_SYSTEM "OpenGL Rendering Subsystem"
#define DLL_EXTENSION ".dll"
#define PLUGIN_FORMAT "Plugin"

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

struct SDL_Window;
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
	/// @brief Se encarga de inicializar el sistema de renderizado y renderizar en cada frame
	/// los objetos de la escena
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
		EDEN_API ~RenderManager() override;
		
		/// @brief Ejecuta un ciclo de renderizado (ventana y raiz)
		void Update();

		/// @brief Comprueba si ha habido errores en la inicializacion
		/// @return True si se ha inicializado bien, False en caso contrario
		inline bool couldInitialize() { return _initialized; }

		/// @brief Devuelve el ancho de la ventana
		/// @return Devuelve el ancho de la ventana 
		EDEN_API int GetWindowWidth();

		/// @brief Devuelve el alto de la ventana
		/// @return Devuelve el alto de la ventana 
		EDEN_API int GetWindowHeight();
		
		/// @brief Cambia el estado de visibilidad del cursor
		/// @param _cursor True = Se ve el cursor | False = no se ve el cursor
		EDEN_API void ShowCursor(bool _cursor);

		/// @brief Atrapa el raton en la ventana
		/// @param grab Activa o desactiva la funcionalidad del metodo
		EDEN_API void SetWindowGrab(bool grab);

		/// @brief Setea la posicion del raton como relativa a la posicion anterior o al centro de la pantalla
		/// @param relative Booleano que indica el modo del raton
		EDEN_API void SetRelativeMouseMode(bool relative);

		/// @brief Actualiza todas las posiciones de la escena con su componente Transform
		/// @param sceneID Identificador de la escena
		void UpdatePositions(std::string sceneID);

		/// @brief Aniade una entidad que tenga componentes de renderizado (CMeshRenderer, CCamera, ...) a una escena en concreto
		/// para actualizar su posicion
		/// @param ent Entidad cuya posicion va a actualizarse
		EDEN_API void AddRenderEntity(eden_ec::Entity* ent);

		/// @brief Quita una entidad de una escena para dejar de actualizar su posicion
		/// @param ent Entidad que se va a quitar
		EDEN_API void RemoveRenderEntity(eden_ec::Entity* ent);

		/// @brief Funcion que deberia llamarse en el momento en el que la ventana cambia de tamanio
		EDEN_API void ResizedWindow();

		/// @brief Metodo que intercambia el modo de pantalla entre "pantalla completa" y tamanio elegido
		EDEN_API void FullScreen();

		EDEN_API inline bool IsFullScreen() { return _isFullScreen; }

		/// @brief Metodo que setea las resoluciones
		EDEN_API void SetResolutions(std::vector<std::pair<int, int>> resolutions);

		/// @brief Metodo que devuelve la resolución actual
		EDEN_API std::pair<int, int> GetResolution();

		/// @brief Metodo que cambia la resolucin actual
		EDEN_API void ChangeResolution();

		/// @brief Cambia a la siguiente resolucion aniadida
		EDEN_API void NextResolutuion();

		/// @brief Cambia a la anterior resolucion aniadida
		EDEN_API void PreviousResolution();

		/// @brief Cambia el nombre a la ventana 
		/// @param name Nombre de la ventana
		EDEN_API void SetWindowName(std::string name);

		/// @brief Establece el icono de la ventana
		/// @param filename Nombre del archivo con la textura que se quiera setear el icono
		EDEN_API void SetWindowIcon(std::string filename);

		/// @brief Devuelve la camara de la escena actual. Si no existe la crea
		/// @param ent Entidad a la que se va a aniadir la camara
		/// @return Devuelve la camara de la escena actual. Si no existe la crea
		EDEN_API render_wrapper::CameraWrapper* GetCamera(eden_ec::Entity* ent);

		EDEN_API static RenderManager* getInstance();

	protected:
		/// @brief Devuelve el manager de Ogre actual
		/// @return Devuelve el manager de Ogre actual 
		Ogre::SceneManager* GetOgreSceneManager(std::string sceneID);

	private:
		/// @brief Inicializa la libreria de renderizado,
		/// crea la ventana de renderizado, localiza y carga los recursos (.mesh, .material, etc)
		/// e inicializa los shaders
		/// @param appName Nombre de la ventana
		void InitManager(const std::string& appName);

		/// @brief Inicializa el sistema de sombreado de trazado de rayos
		void InitialiseRTShaderSystem();

		/// @brief Destruye el sistema de sombreado de trazado de rayos
		void DestroyRTShaderSystem();

		/// @brief Inicializacion de ventana, RTShaderSystem y recursos
		void Setup();

		/// @brief Creación de la raiz de Ogre de la escena
		void InitializeLib();

		/// @brief Localizacion de archivos para Ogre
		void LocateResources();

		/// @brief Carga de archivos para Ogre
		void LoadResources();

		/// @brief Cierre de ventana de SDL, asi como el RTShaderSystem
		void Shutdown();

		/// @brief Destructora de la ventana de SDL
		void CloseWindow();

		/// @brief Destruye la raiz y llama posteriormente al metodo Shutdown
		void CloseManager();

		/// @brief Creacion de la ventana de Ogre y SDL
		/// @param name Nombre de la ventana
		NativeWindowPair CreateNewWindow(const std::string& name);

		/// @brief Constructora
		/// @param appName Nombre de la ventana
		RenderManager(const std::string& appName = "TEST_APP");

		/// @brief Crea una nueva escena. Si existe, actualiza la escena actual 
		/// @param sceneID ID de la escena que se quiere crear
		void CreateRenderScene(std::string sceneID);

		/// @brief Asigna como escena principal la escena sceneID
		/// @param sceneID ID de la escena que se quiere asignar como principal
		void SetRenderScene(std::string sceneID);

		/// @brief Borra la escena sceneToRemoveID si existe. Luego crea una escena con ID newCurrentSceneID
		/// @param sceneToRemoveID ID de la escena que se quiere borrar
		/// @param newCurrentSceneID ID de la escena que se quiere crear
		void RemoveRenderScene(std::string sceneToRemoveID, std::string newCurrentSceneID);

		/// @brief Muestra o esconde todas las entidades de la escena sceneID
		/// @param sceneID ID de la escena
		/// @param show Si es verdadero, muestra las entidades. En caso contrario, las esconde
		void ShowEntities(std::string sceneID, bool show);

		/// @brief Cambia el tamanio de la ventana
		/// @param w Ancho de la ventana
		/// @param h Alto de la ventana
		void ChangeWindowSize(int w, int h);

		/// <summary>
		/// Comprueba que todos los plugins del archivo con ruta path existen
		/// </summary>
		/// <param name="path">Ruta del archivo plugins.cfg</param>
		/// <returns>True si se encuentran todos los plugins, False en caso contrario</returns>
		bool CheckPlugins(std::string& path);

		/// @brief Raiz de Ogre
		Ogre::Root* _root = nullptr;

		/// @brief Sistema de Overlay
		Ogre::OverlaySystem* _overlaySys = nullptr;

		/// @brief Gestor de escenas
		std::unordered_map<std::string, InfoRenderWorld*> _renderScenes;

		/// @brief Escena actual de render
		InfoRenderWorld* _currentRenderScene = nullptr;

		/// @brief Ventana principal
		NativeWindowPair _window;

		/// @brief Capa de abstraccion del sistema de archivos
		Ogre::FileSystemLayer* _fsLayer = nullptr;

		/// @brief Nombre de la ventana
		std::string _appName = " ";

		/// @brief Localizacion de recursos de Ogre
		std::string _solutionPath = " ";

		/// @brief Localizacion de recursos de la aplicacion
		const std::string _resourcesPath = "assets\\";

		/// @brief Localizacion de libreria del RTShader
		std::string _rtShaderLibPath = " ";

		/// @brief Instancia de generador de sombreado
		Ogre::RTShader::ShaderGenerator* _shaderGenerator = nullptr;

		/// @brief Flag para saber si se ha podido inicializar el manager
		bool _initialized = true;

		/// @brief Flag para saber si el canvas se ha inicializado
		bool _canvasInit = false;

		/// @brief Flag para saber si la ventana ha sido escalada
		bool _resized = false;

		/// @brief Tamanio actual de la pantalla
		uint32_t _currW, _currH;

		/// @brief Tamanio de la pantalla completa
		uint32_t _fullW, _fullH;
		bool _isFullScreen = false;

		/// @brief Vector con las distintas resoluciones
		std::vector<std::pair<int, int>> _resolutions;
		
		/// @brief indice de la resolucion actual
		int _currRes = 0;

		/// @brief Resolucion default
		std::pair<int, int> _defWindowSize = {640,480};
	};

	class __declspec(dllexport) InfoRenderWorld
	{
		friend RenderManager;
		friend render_wrapper::NodeManager;
		friend render_wrapper::RenderObject;
	private:
		/// @brief Constructora de la clase
		/// @param root Referencia a la raiz de Ogre
		/// @param overlaySystem Referencia al sistema de overlay
		/// @param sceneID ID del a escena que se quiere crear
		InfoRenderWorld(Ogre::Root* root, Ogre::OverlaySystem* overlaySystem, std::string sceneID);

		/// @brief Destructora de la clase
		~InfoRenderWorld();

		/// @brief Manager de Ogre
		Ogre::SceneManager* _renderScene = nullptr;

		/// @brief ID de la escena
		std::string _sceneID = " ";

		/// @brief Conjunto de entidades para actualizar su posicion
		std::unordered_set<eden_ec::Entity*> _entities;

		/// @brief Sistema de overlay
		Ogre::OverlaySystem* _overlaySystem = nullptr;

		/// @brief Raiz de Ogre
		Ogre::Root* _root = nullptr;

		/// @brief Wrapper de la camara de la escena
		render_wrapper::CameraWrapper* _cameraWrapper = nullptr;

		/// @brief Manager de la escena
		/// @return Manager de la escena 
		Ogre::SceneManager* GetRenderScene();
	};
}

#endif // RENDER_MANAGER_H_
