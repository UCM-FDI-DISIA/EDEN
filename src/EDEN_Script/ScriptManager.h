#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_SCRIPT_MANAGER_H
#define EDEN_SCRIPT_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>

#include <exception>

#include "Singleton.h"

struct lua_State;

namespace eden_script {
class LuaManager;

	// Esta Macro se usa para ver la informacion que se esta leyendo del mapa por salida estandar
#define _DEBUGGING_SCENE_READING

#ifdef _MSC_VER
#define ASSETS_ROUTE "assets\\"
#define SCENE_ROUTE "assets\\scenes\\"
#endif
#ifdef __APPLE__
#define ASSETS_ROUTE "assets/"
#define SCENE_ROUTE "assets/scenes/"
#endif
#define SCENE_EXTENSION ".lua"
#define BLUEPRINTS_FILE_NAME "Blueprints"
//
//#define ERROR_DEFINITION "Lua error in line "+ std::to_string(__LINE__)
//#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

// #define ASSERT_EDEN(a, b) assert((void)b, a)
// #define _MACRO_AA(b) std::cerr << #b << "\n\n\n\n\n\n\n"

#define ENTITY_TABLE_NAME "Entities"
#define COLLISION_TABLE_NAME "CollisionLayers"
#define NUM_ENTITIES "numEntities"

	class ComponentArguments;

	/// @brief Informacion acerca de las entidades. Contiene un nombre y un vector con informacion de sus componentes
	struct EntityInfo {
		std::string name;
		std::vector<ComponentArguments> components;
	};
	
	/// @brief Funciona como Wrapper de Lua y es capaz de leer de un .lua las entidades que necesitan ser creadas en escena y su informacion.
	class ScriptManager : public Singleton<ScriptManager> {

		friend Singleton<ScriptManager>;

	public:
		/// @brief Lee la escena "bin/assets/<sceneName>.lua" y rellena <info> con informacion del componente
		/// @param sceneName Escena a cargar desde la carpeta "bin/assets"
		/// @param info Vector pasado por referencia donde se guardara toda la informacion de las entidades leidas de mapa
		/// @param collisionInfo Vector pasado por referencia donde se guardara toda la informacion de las capas de colision leidas de mapa
		/// @return True = No error | False = Error
		bool ReadScene(std::string sceneName, std::vector<eden_script::EntityInfo*>& info, std::unordered_map<std::string, std::vector<std::string>>& collisionInfo);

		/// @brief Lee el archivo "bin/assets/Blueprints.lua" y rellena info con la información de los blueprints que existan.
		/// @param info Información a rellenar
		/// @return True = No error | False = Error
		bool ReadBlueprints(std::vector<eden_script::EntityInfo*>& info);

		/// @brief Devuelve puntero a LuaManager
		eden_script::LuaManager* GetLuaManager();

	private:

		/// @brief Puntero al LuaManager
		LuaManager* _luaManager;

		/// @brief Constructora que inicializa Lua
		ScriptManager();
		lua_State* _l;

		/// @brief Dice si una variable es 'nil' en Lua
		/// @param varType Tipo de la variable a ver (entero devuelto por las funciones de Lua)
		/// @return True = Es nil | False = No es nil
		inline bool IsNil(int varType) { return varType == 0; }

		bool CollisionTableToData(std::unordered_map<std::string, std::vector<std::string>>& collisionInfo);

		/// @brief Rellena el vector de entidades, suponiendo que ya hemos abierto antes una escena
		/// @param info Informacion de entidades a rellenar
		/// @return True = No error | False = Error
		bool EntityTableToData(std::vector<eden_script::EntityInfo*>& info, std::string tableName);


		/// @brief Busca en la tabla de Lua que se encuentre en el indice 'tableIndex' 
		/// una key 'stringToRead' y devuelve su valor, si lo encuentra.
		/// @param stringToRead Key en la tabla de Lua a leer
		/// @param tableIndex indice de la tabla en el Stack de Lua
		/// @return El string asociado a la key 'strinToRead' de la tabla de Lua a leer
		std::string ReadStringFromTable(std::string stringToRead, int tableIndex);

		/// @brief Coge el valor situado en el indice 'indexOnLuaStack' del Stack de Lua y lo interpreta como una string
		/// @param indexOnLuaStack indice del string a leer en el Stack de Lua
		/// @return El string parseado
		std::string ParseString(int indexOnLuaStack);

		/// @brief Llama a ParseString, pero quita 'indexOnLuaStack' elementos del Stack de Lua hasta 
		/// quitar el string que queriamos parsear
		/// @param indexOnLuaStack indice del string a leer en el Stack de Lua
		/// @return El string parseado
		std::string ParseAndPopString(int indexOnLuaStack);

		/// @brief Se lee una tabla situada en 'tableIndex' en el Stack de Lua y se interpreta
		/// como un mapa desordenada con strings como keys y vector<string> como valor de dichas claves
		/// @param tableIndex indice de la tabla a leer en el Stack de Lua
		/// @return La tabla parseada
		std::unordered_map<std::string, std::vector<std::string>> ParseTableToStringMap(int tableIndex);

		/// @brief Busca en la tabla situada en 'currentTableIndex' en el Stack de Lua (esta tabla sera una entidad) una key 'Components',
		/// cuyo valor es una tabla indexada por numeros, NO por keys. Se lee esta tabla y se rellena un vector<ComponentArguments>,
		/// que representa los componentes que tiene la entidad que se estaba leyendo
		/// @param currentTableIndex indice de la tabla de la entidad que se esta leyendo en el Stack de Lua
		/// @return Los componentes de la entidad leidos parseados a un vector de ComponentArguments
		std::vector<ComponentArguments> ReadComponents(int currentTableIndex);

		/// @brief Pushea al stack de Lua el elemento con indice 'elementIndex' de una tabla situada en el indice 'tableIndex' en el Stack de Lua.
		/// El elemento pusheado quedara en el indice -1 del Stack.
		/// @param elementIndex indice a pushear
		/// @param tableIndex indice de la tabla
		void PushTableElement(int elementIndex, int tableIndex);

		/// @brief Pushea al stack de Lua el valor de la key 'push' de una tabla situada en el indice 'tableIndex' en el Stack de Lua
		/// @param push Key a pushear de la tabla
		/// @param tableIndex Tabla de la cual se pusheara la key 'push'
		void PushStringToTable(std::string push, int tableIndex);

		/// @brief Comprobacion de errores de Lua. Lanza por consola el error recibido si se esta en modo Debug
		/// @param err Resultado de una operacion de Lua
		/// @param errorTitle Breve información acerca de dónde se produciría el error
		/// @return True = No error | False = Error
		bool CheckLua(int err, std::string errorTitle);
	};
}

#endif // SCRIPT_MANAGER_H