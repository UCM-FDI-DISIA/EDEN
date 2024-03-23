#include <iostream>
#include <string>
#include <vector>

#include <lua.hpp>

#include "ScriptManager.h"
#include <ErrorHandler.h>
#include "ComponentArguments.h"
#include "LuaManager.h"

eden_script::ScriptManager::ScriptManager() {

	//Creamos el luaManager
	_luaManager = new LuaManager();
	// Inicializamos la máquina virtual para correr Lua
	_l = luaL_newstate();
	// Abrimos las librerías básicas de Lua
	luaL_openlibs(_l);

	// Comprobamos que Lua esté bien abierto
	assert(_l);

	//Inicializamos el luaManager
	_luaManager->InitLua(_l);
}

eden_script::LuaManager* eden_script::ScriptManager::GetLuaManager() {
	return _luaManager;
}

bool eden_script::ScriptManager::CheckLua(int err, std::string errorTitle) {
	bool result = err == LUA_OK;
#ifdef _DEBUG
	if (!result) {
		// Cogemos el mensaje de error que se ha generado en el Stack de Lua y lo lanzamos en Debug.
		std::string errorMsg = lua_tostring(_l, -1);
		// std::cerr << "Lua ERROR: " << errorMsg << '\n';
		eden_error::ErrorHandler::Instance()->Exception(errorTitle, errorMsg);
	}
#endif
	
	return result;
}
	
void eden_script::ScriptManager::PushStringToTable(std::string push, int tableIndex) {
	// Pushear la string que queremos leer al Stack
	lua_pushstring(_l, push.c_str());
	// Pushear a -1 el elemento de la table con key 'push'

	// TRATAMIENTO DE ERRORES DE LUA AQUÍ --------
	lua_gettable(_l, tableIndex);
}

std::string eden_script::ScriptManager::ParseString(int indexOnLuaStack) {
	assert(indexOnLuaStack < 0);

	// TRATAMIENTO DE ERRORES DE LUA AQUÍ --------
	std::string cppString = lua_tostring(_l, indexOnLuaStack);

	return cppString;
}

std::string eden_script::ScriptManager::ParseAndPopString(int indexOnLuaStack) {
	std::string cppString = ParseString(indexOnLuaStack);
	
	// TRATAMIENTO DE ERRORES DE LUA AQUÍ --------
	lua_pop(_l, -indexOnLuaStack);

	return cppString;
}

std::string eden_script::ScriptManager::ReadStringFromTable(std::string stringToRead, int tableIndex) {
	// Pusheamos la string a la pila de Lua
	PushStringToTable(stringToRead, tableIndex);
	// Cogemos la string
	return ParseAndPopString(-1);
}

void eden_script::ScriptManager::PushTableElement(int elementIndex, int tableIndex) {
	// Pusheamos al Stack un número, que será el índice de un elemento en la Table
	lua_pushnumber(_l, elementIndex);
	// Usando el número en el top del Stack, accedemos a la tabla que ahora se encuentra
	// una posición por debajo del top del Stack (-2) y le pedimos que pushee lo que tenga en su índice i

	// TRATAMIENTO DE ERRORES DE LUA AQUÍ --------
	lua_gettable(_l, tableIndex);
}

std::unordered_map<std::string, std::vector<std::string>> eden_script::ScriptManager::ParseTableToStringMap(int tableIndex) {
	// Recorremos la tabla de tipo key - value y la parseamos a un mapa
	lua_pushnil(_l);

	std::unordered_map<std::string, std::vector<std::string>> table;
	while (lua_next(_l, tableIndex - 1) != 0)
	{
		// Al hacer lua_next() se pushea primero una key y luego su valor. Los parseamos a string de c++
		std::string key = ParseString(-2);
		std::string value = ParseString(-1);

		std::string temp = "";
		// Si un valor necesita varios argumentos para construirse, estos se separan con '|'
		// Por ejemplo, al construir un Vector3 'Position' se haría de la siguiente forma: "Position = x|y|z"
		for (int i = 0; i < value.size(); ++i) {
			if (value[i] == '|') {
				table[key].push_back(temp);
				temp = "";
			}
			else {
				temp.push_back(value[i]);
			}
		}
		table[key].push_back(temp);

		// Quitamos del stack el valor. La key se queda para poder ejecutra lua_next.
		lua_pop(_l, 1);
	}

	// Finalmente la última key se popea al hacer lua_next y que este sea == 0

	// Devolvemos el mapa parseado al tipo que nos interesa para los componentes
	return table;
}

std::vector<eden_script::ComponentArguments> eden_script::ScriptManager::ReadComponents(int currentTableIndex) {
	// Ponemos en el top del Stack la table de los componentes, cuyos elementos son a su vez tables con información
	PushStringToTable("Components", currentTableIndex);

	// aquí hay que hacer un for por cada componente
	int numComponentes = (int)luaL_len(_l, -1);
	std::vector<ComponentArguments> components = std::vector<ComponentArguments>();
	for (int i = 1; i <= numComponentes; ++i) {
		// Se pushea la tabla del componente
		PushTableElement(i, -2);

		// Se lee su ID
		std::string id = ReadStringFromTable("Name", -2);
		ComponentArguments cmp(id);

#ifdef _DEBUGGING_SCENE_READING 
		std::cout << "Reading Component '" << id << '\'' << '\n';
#endif
		// Se pushea la tabla de argumentos del componente
		PushStringToTable("Arguments", -2);
		
		// Recibimos la información de los argumentos del componente
		cmp._args = ParseTableToStringMap(-1);

		components.push_back(cmp);

		lua_pop(_l, 2);
	}

	return components;
}

bool eden_script::ScriptManager::EntityTableToData(std::vector<eden_script::EntityInfo*>& info) {
	// L debería haber sido inicializado en la constructora. Esto NUNCA debería saltar, pero por si a caso
	assert(_l);
	
	// Accedemos a la Table de Entidades del .lua de la escena
	if (IsNil(lua_getglobal(_l, ENTITY_TABLE_NAME))) {
		std::string sEntityTable = ENTITY_TABLE_NAME;
		EDEN_EXCEPTION(sEntityTable.c_str());
		// std::cerr << ERROR_DEFINITION << " " << __FILENAME__ << ": Entities Table was not found on the scene you're trying to read. It should be named: '" + sEntityTable + "'\n";
		return false;
	}

	// Tenemos que saber si hemos encontrado la tabla. Hacemos un assert de la función CheckLua para ello
	if (!lua_istable(_l, -1)) {
		std::string sEntityTable = ENTITY_TABLE_NAME;
		std::cerr << "The variable '" + sEntityTable + "' was not a Table as expected'\n'";
		return false;
	}

	int numEntities = (int)luaL_len(_l, -1);

	int tableIndexOnAccess = -2;
	// Recorremos la tabla, comenzando en 1 en lugar de 0
	for (int i = 1; i <= numEntities; ++i) {
		// Generamos un puntero de información de entidad
		EntityInfo* newInfo = new EntityInfo();

		// Pusheamos el elemento actual de la tabla
		PushTableElement(i, tableIndexOnAccess);

		// Nuestra tabla debe tener un string "Name" y una tabla "Components"
		newInfo->name = ReadStringFromTable("Name" , tableIndexOnAccess);
#ifdef _DEBUGGING_SCENE_READING
		std::cout << "Reading Entity '" << newInfo->name <<'\'' << '\n';
#endif
		// Leemos la tabla de componentes y la asignamos
		newInfo->components = ReadComponents(tableIndexOnAccess);

		// Como ya no usaremos más el elemento que estamos leyendo actualmente de la tabla, debemos 
		// quitarlo del top del Stack para que la Table siga siendo el top.
		lua_pop(_l, 2);

		// Puhseamos la información nueva al vector de información de entidades
		info.push_back(newInfo);
	}
}

bool eden_script::ScriptManager::ReadScene(std::string sceneName, std::vector<eden_script::EntityInfo*>& info) {
	assert(_l);

	std::string fileName = SCENE_ROUTE + sceneName + SCENE_EXTENSION;
	if (CheckLua(luaL_dofile(_l, fileName.c_str()), "Reading " + fileName)) {
		bool readingSuccesful = EntityTableToData(info);
		return true;
	}
	else {
		return false;
	}
}