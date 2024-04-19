#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_RENDER_MANAGER_H
#define EDEN_RENDER_MANAGER_H

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

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

		/// @brief Devuelve el ancho de la ventana
		/// @return Devuelve el ancho de la ventana 
		int GetWindowWidth();

		/// @brief Devuelve el alto de la ventana
		/// @return Devuelve el alto de la ventana 
		int GetWindowHeight();
		
		/// @brief Actualiza todas las posiciones de la escena con su componente Transform
		/// @param sceneID Identificador de la escena
		void UpdatePositions(std::string sceneID);

		/// @brief A�ade una entidad que tenga componentes de renderizado (CMeshRenderer, CCamera, ...) a una escena en concreto
		/// para actualizar su posici�n
		/// @param ent Entidad cuya posici�n va a actualizarse
		void AddRenderEntity(eden_ec::Entity* ent);

		/// @brief Quita una entidad de una escena para dejar de actualizar su posici�n
		/// @param ent Entidad que se va a quitar
		void RemoveRenderEntity(eden_ec::Entity* ent);

		/// @brief Funci�n que deber�a llamarse en el momento en el que la ventana cambia de tama�o
		void ResizedWindow();

		/// @brief Método que intercambia el modo de pantalla entre "pantalla completa" y tamaño elegido
		void FullScreen();

		/// @brief Método que setea las resoluciones
		void SetResolutions(std::vector<std::pair<int, int>> resolutions);

		/// @brief Método que devuelve la resolución actual
		std::pair<int, int> GetResolution();

		/// @brief Método que cambia la resuluión actual
		void ChangeResolution();

		/// @brief Cambia a la siguiente resolucion añadida
		void NextResolutuion();

		/// @brief Cambia a la anterior resolucion añadida
		void PreviousResolution();

		/// @brief Devuelve la camara de la escena actual. Si no existe la crea
		/// @param ent Entidad a la que se va a añadir la camara
		/// @return Devuelve la camara de la escena actual. Si no existe la crea
		render_wrapper::CameraWrapper* GetCamera(eden_ec::Entity* ent);

	protected:
		/// @brief Devuelve el manager de Ogre actual
		/// @return Devuelve el manager de Ogre actual 
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
		RenderManager(const std::string& appName = "TEST_APP");

		/// @brief Crea una nueva escena. Si existe, actualiza la escena actual 
		/// @param sceneID ID de la escena que se quiere crear
		void CreateRenderScene(std::string sceneID);

		/// @brief Borra la escena sceneToRemoveID si existe. Luego crea una escena con ID newCurrentSceneID
		/// @param sceneToRemoveID ID de la escena que se quiere borrar
		/// @param newCurrentSceneID ID de la escena que se quiere crear
		void RemoveRenderScene(std::string sceneToRemoveID, std::string newCurrentSceneID);

		/// @brief Muestra o esconde todas las entidades de la escena sceneID
		/// @param sceneID ID de la escena
		/// @param show Si es verdadero, muestra las entidades. En caso contrario, las esconde
		void ShowEntities(std::string sceneID, bool show);

		/// @brief Cambia el tamaño de la ventana
		/// @param w Ancho de la ventana
		/// @param h Alto de la ventana
		void ChangeWindowSize(int w, int h);

		/// @brief Raiz de Ogre
		Ogre::Root* _root;

		/// @brief Sistema de Overlay
		Ogre::OverlaySystem* _overlaySys;

		/// @brief Gestor de escenas
		std::unordered_map<std::string, InfoRenderWorld*> _renderScenes;

		/// @brief Escena actual de render
		InfoRenderWorld* _currentRenderScene;

		/// @brief Ventana principal
		NativeWindowPair _window;

		/// @brief Capa de abstraccion del sistema de archivos
		Ogre::FileSystemLayer* _fsLayer;

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

		/// @brief Tamaño actual de la pantalla
		uint32_t _currW, _currH;

		/// @brief Tamaño de la pantalla completa
		uint32_t _fullW, _fullH;
		bool _isFullScreen = false;

		/// @brief Vector con las distintas resoluciones
		std::vector<std::pair<int, int>> _resolutions;
		
		/// @brief indice de la resolucion actual
		int _currRes = 0;

		/// @brief Resolución default
		std::pair<int, int> _defWindowSize = {640,480};
	};

	/// @brief Contiene informacion de la escena y las entidades que utilizan Ogre. Cada instancia de esta clase representa una escena.
	class InfoRenderWorld
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
		Ogre::SceneManager* _renderScene;

		/// @brief ID de la escena
		std::string _sceneID;

		/// @brief Conjunto de entidades para actualizar su posici�n
		std::unordered_set<eden_ec::Entity*> _entities;

		/// @brief Sistema de overlay
		Ogre::OverlaySystem* _overlaySystem;

		/// @brief Raiz de Ogre
		Ogre::Root* _root;

		/// @brief Wrapper de la camara de la escena
		render_wrapper::CameraWrapper* _cameraWrapper;

		/// @brief Manager de la escena
		/// @return Manager de la escena 
		Ogre::SceneManager* GetRenderScene();
	};
}

#endif // RENDER_MANAGER_H_
