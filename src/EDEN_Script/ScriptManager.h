#ifndef SCRIPT_MANAGER_H
#define SCRIPT_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>

#include "Singleton.h"

struct lua_State;

namespace eden_script {

	// Esta Macro se usa para ver la informaci�n que se est� leyendo del mapa por salida est�ndar
#define _DEBUGGING_SCENE_READING

#define ASSETS_ROUTE "assets\\scenes\\"
#define SCENE_EXTENSION ".lua"
#define ERROR_DEFINITION "Lua error in line "+ std::to_string(__LINE__)
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define ENTITY_TABLE_NAME "Entities"
#define NUM_ENTITIES "numEntities"

	class ComponentArguments;

	/// @brief Informaci�n acerca de las entidades. Contiene un nombre y un vector con informaci�n de sus componentes
	struct EntityInfo {
		std::string name;
		std::vector<ComponentArguments> components;
	};
	
	/// @brief Funciona como Wrapper de Lua y es capaz de leer de un .lua las entidades que necesitan ser creadas en escena y su informaci�n.
	class ScriptManager : public Singleton<ScriptManager> {

		friend Singleton<ScriptManager>;

	public:
		/// @brief Lee la escena "bin/assets/<sceneName>.lua" y rellena <info> con informaci�n del componente
		/// @param sceneName Escena a cargar desde la carpeta "bin/assets"
		/// @param info Vector pasado por referencia donde se guardar� toda la informaci�n de las entidades le�das de mapa
		/// @return True = No error | False = Error
		bool ReadScene(std::string sceneName, std::vector<eden_script::EntityInfo*>& info);

	private:
		/// @brief Constructora que inicializa Lua
		ScriptManager();
		lua_State* L;

		/// @brief Dice si una variable es 'nil' en Lua
		/// @param varType Tipo de la variable a ver (entero devuelto por las funciones de Lua)
		/// @return True = Es nil | False = No es nil
		inline bool isNil(int varType) { return varType == 0; }

		/// @brief Rellena el vector de entidades, suponiendo que ya hemos abierto antes una escena
		/// @param info Informaci�n de entidades a rellenar
		/// @return True = No error | False = Error
		bool EntityTableToData(std::vector<eden_script::EntityInfo*>& info);

		/// @brief Busca en la tabla de Lua que se encuentre en el �ndice 'tableIndex' 
		/// una key 'stringToRead' y devuelve su valor, si lo encuentra.
		/// @param stringToRead Key en la tabla de Lua a leer
		/// @param tableIndex �ndice de la tabla en el Stack de Lua
		/// @return El string asociado a la key 'strinToRead' de la tabla de Lua a leer
		std::string ReadStringFromTable(std::string stringToRead, int tableIndex);

		/// @brief Coge el valor situado en el �ndice 'indexOnLuaStack' del Stack de Lua y lo interpreta como una string
		/// @param indexOnLuaStack �ndice del string a leer en el Stack de Lua
		/// @return El string parseado
		std::string ParseString(int indexOnLuaStack);

		/// @brief Llama a ParseString, pero quita 'indexOnLuaStack' elementos del Stack de Lua hasta 
		/// quitar el string que quer�amos parsear
		/// @param indexOnLuaStack �ndice del string a leer en el Stack de Lua
		/// @return El string parseado
		std::string ParseAndPopString(int indexOnLuaStack);

		/// @brief Se lee una tabla situada en 'tableIndex' en el Stack de Lua y se interpreta
		/// como un mapa desordenada con strings como keys y vector<string> como valor de dichas claves
		/// @param tableIndex �ndice de la tabla a leer en el Stack de Lua
		/// @return La tabla parseada
		std::unordered_map<std::string, std::vector<std::string>> ParseTableToStringMap(int tableIndex);

		/// @brief Busca en la tabla situada en 'currentTableIndex' en el Stack de Lua (esta tabla ser� una entidad) una key 'Components',
		/// cuyo valor es una tabla indexada por n�meros, NO por keys. Se lee esta tabla y se rellena un vector<ComponenArguments>,
		/// que representa los componentes que tiene la entidad que se estaba leyendo
		/// @param currentTableIndex �ndice de la tabla de la entidad que se est� leyendo en el Stack de Lua
		/// @return Los componentes de la entidad le�dos parseados a un vector de ComponentArguments
		std::vector<ComponentArguments> ReadComponents(int currentTableIndex);

		/// @brief Pushea al stack de Lua el elemento con �ndice 'elementIndex' de una tabla situada en el �ndice 'tableIndex' en el Stack de Lua.
		/// El elemento pusheado quedar� en el �ndice -1 del Stack.
		/// @param elementIndex �ndice a pushear
		/// @param tableIndex �ndice de la tabla
		void PushTableElement(int elementIndex, int tableIndex);

		/// @brief Pushea al stack de Lua el valor de la key 'push' de una tabla situada en el �ndice 'tableIndex' en el Stack de Lua
		/// @param push Key a pushear de la tabla
		/// @param tableIndex Tabla de la cual se pushear� la key 'push'
		void PushStringToTable(std::string push, int tableIndex);

		/// @brief Comprobaci�n de errores de Lua. Lanza por consola el error recibido si se est� en modo Debug
		/// @param err Resultado de una operaci�n de Lua
		/// @return True = No error | False = Error
		bool CheckLua(int err);
	};
}

#endif // SCRIPT_MANAGER_H