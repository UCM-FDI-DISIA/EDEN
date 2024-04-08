#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_LUA_MANAGER_H
#define EDEN_LUA_MANAGER_H

#include <string>
#include <set>

#include <lua.hpp>
#include <LuaBridge.h>

struct lua_State;

namespace eden_ec {
	class Entity;
	class Hito1Prueba;
}

namespace eden_script {

	/// @brief Clase encargada de gestionar la maquina virtual de Lua y los scripts de comportamiento
	class LuaManager
	{
	public:
	
		/// @brief Constructora de la clase
		LuaManager();

		/// @brief Destructora de la clase
		~LuaManager();
		
		/// @brief Registra las clases b�sicas en Lua (Ahora mismo ButtonBehaviour)
		void RegisterClasses();

		/// @brief Carga el script y crea lo asocia a un Behaviour concreto
		/// @param name Nombre del script, sin extension
		/// @param ent Entidad a la que a�adir el script
		bool LoadScript(std::string name, eden_ec::Entity* ent);

		/// @brief Metodo que devuelve el lua_State de este manager. Encargado de
		/// gestionar todos los scripts de comportamiento del motor
		lua_State* GetLuaState();

		/// @brief Se encarga de crear el LuaState e incializar todo lo necesario para
		/// el scripting
		void InitLua(lua_State* l);
		

		/// @brief M�todo que se encarga de registrar clases con las funciones deseadas (de clases ya existentes) mediante luabridge.
		/// Si la clase que se est� intentando crear ya existe simplemente se le a�adir�n las funciones nuevas
		/// @tparam T El tipo de clase que se va a registrar
		/// @tparam Funct El tipo de las funciones que vamos a registrar
		/// @tparam W Puntero al tipo de clase 
		/// @param name Nombre con el que se guarda la clase registrada en luabridge
		/// @param nameFunc Nombre con el que se guarda la funci�n deseada en la clase registrada
		template <class T, class Funct, class W>
		void Regist(T a, const char *name, Funct _f, const char* nameFunc,W _this) {
			if (!_classes.contains({ name,false })) {
				if(!_classes.contains({ name,true })) _classes.insert({ name,true });

				luabridge::getGlobalNamespace(_L)
					.beginClass<T>(name)
					.addFunction(nameFunc, _f)
					.endClass();
			}
			else HandleError(name);
		}
		/// @brief M�todo que setea de forma gloabal una clase que hemos creado para poder acceder a ella
		/// (*Llamar despues de haber registrado la clase*)
		/// @tparam W Puntero al tipo de clase 
		/// @param name Nombre con el que se guarda la clase registrada en luabridge
		template <class W>
		void SetGlobal(W _this, const char* name) {
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

		/// @brief registro de las clases que han sido a�adidas y flag de si han sido seteadas ya como global o no
		std::set<std::pair<std::string,bool>>_classes;

		/// @brief M�todo que maneja los errores al crear clases en luabridge
		void HandleError(const char* name);
	};
}

#endif //__LUA_MANAGER_H__