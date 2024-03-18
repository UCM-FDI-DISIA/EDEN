#ifndef EDEN_LUA_MANAGER_H
#define EDEN_LUA_MANAGER_H

#include <string>
#include <functional>
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
		
		/// @brief Registra las clases básicas en Lua (Ahora mismo ButtonBehaviour)
		void RegisterClasses();

		/// @brief Carga el script y crea lo asocia a un Behaviour concreto
		/// @param name Nombre del script, sin extension
		/// @param ent Entidad a la que añadir el script
		bool LoadScript(std::string name, eden_ec::Entity* ent);

		/// @brief Metodo que devuelve el lua_State de este manager. Encargado de
		/// gestionar todos los scripts de comportamiento del motor
		lua_State* GetLuaState();

		/// @brief Se encarga de crear el LuaState e incializar todo lo necesario para
		/// el scripting
		void InitLua(lua_State* l);

		template <class T>
		void Regist(T a) {
			luabridge::getGlobalNamespace(L_)
				.beginClass<T>("Hito1Prueba")
				.endClass();
		}

	private:

		/// @brief Puntero al LuaState
		lua_State* L_;
		
	};
}

#endif __LUA_MANAGER_H__