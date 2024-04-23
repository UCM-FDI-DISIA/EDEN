#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_LUA_MANAGER_H
#define EDEN_LUA_MANAGER_H

#include <string>
#include <set>

#include <lua.hpp>
#include <LuaBridge.h>

#include "defs.h"

struct lua_State;

namespace eden_ec {
	class Entity;
}

namespace eden_script {

	/// @brief Clase encargada de gestionar la maquina virtual de Lua y los scripts de comportamiento
	class LuaManager
	{
	public:
	
		/// @brief Constructora de la clase
		EDEN_API LuaManager();

		/// @brief Destructora de la clase
		EDEN_API ~LuaManager();
		
		/// @brief Registra las clases b�sicas en Lua (Ahora mismo ButtonBehaviour)
		EDEN_API void RegisterClasses();

		/// @brief Carga el script y crea lo asocia a un Behaviour concreto
		/// @param name Nombre del script, sin extension
		/// @param ent Entidad a la que a�adir el script
		EDEN_API bool LoadScript(std::string name, eden_ec::Entity* ent);

		/// @brief Metodo que devuelve el lua_State de este manager. Encargado de
		/// gestionar todos los scripts de comportamiento del motor
		EDEN_API lua_State* GetLuaState();

		/// @brief Se encarga de crear el LuaState e incializar todo lo necesario para
		/// el scripting
		EDEN_API void InitLua(lua_State* l);

		/// @brief Metodo que se encarga de registrar clases con las funciones deseadas (de clases ya existentes) mediante luabridge.
		/// Si la clase que se esta intentando crear ya existe simplemente se le aniadiran las funciones nuevas
		/// @tparam T El tipo de clase que se va a registrar
		/// @tparam Funct El tipo de las funciones que vamos a registrar
		/// @tparam W Puntero al tipo de clase 
		/// @param name Nombre con el que se guarda la clase registrada en luabridge
		/// @param nameFunc Nombre con el que se guarda la funcion deseada en la clase registrada
		template <class T, class Funct, class W>
		EDEN_API void Regist(T a, const char *name, Funct _f, const char* nameFunc,W _this) {
			if (!_classes.contains({ name,false })) {
				if(!_classes.contains({ name,true })) _classes.insert({ name,true });

				luabridge::getGlobalNamespace(_L)
					.beginClass<T>(name)
					.addFunction(nameFunc, _f)
					.endClass();
			}
			else HandleError(name);
		}
		/// @brief Metodo que setea de forma gloabal una clase que hemos creado para poder acceder a ella
		/// (*Llamar despues de haber registrado la clase*)
		/// @tparam W Puntero al tipo de clase 
		/// @param name Nombre con el que se guarda la clase registrada en luabridge
		template <class W>
		EDEN_API void SetGlobal(W _this, const char* name) {
			if (_classes.contains({ name,true })) {
				luabridge::setGlobal(_L, _this, name);
				_classes.erase({ name,true });
				_classes.insert({ name,false });
			}
			else HandleError(name);
		}

	private:

		/// @brief Puntero al LuaState
		lua_State* _L;

		/// @brief registro de las clases que han sido aniadidas y flag de si han sido seteadas ya como global o no
		std::set<std::pair<std::string,bool>>_classes;

		/// @brief M�todo que maneja los errores al crear clases en luabridge
		EDEN_API void HandleError(const char* name);
	};
}

#endif //__LUA_MANAGER_H__