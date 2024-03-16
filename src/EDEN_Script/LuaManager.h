#ifndef __LUA_MANAGER_H__
#define __LUA_MANAGER_H__


#include <string>

	class lua_State;
	namespace eden_ec {
		class Entity;
	}
	/// <summary>
	/// Clase encargada de gestionar la maquina virtual de Lua y los scripts de comportamiento
	/// </summary>
	class  LuaManager
	{
	public:
		/// <summary>
		/// Registra las clases básicas en Lua, principalmente Behaviour
		/// </summary>
		void RegisterClasses();

		/// <summary>
		/// Carga el script y crea un Behaviour al que asociarlo, tambien se
		/// encarga de añadirlo a este manager y a su entidad
		/// </summary>
		/// <param name="name">Nombre del script, sin extension</param>
		/// <param name="ent">Entidad a la que añadir el Behaviour</param>
		/// <returns>El Behaviour creado</returns>
		bool LoadScript(std::string name, eden_ec::Entity* ent);

		/// <summary>
		/// Metodo que devuelve el lua_State de este manager. Encargado de
		/// gestionar todos los scripts de comportamiento del motor
		/// </summary>
		/// <returns>El lua_State que representa la maquina virtual de
		/// Lua</returns>
		lua_State* GetLuaState();

		~LuaManager();


		/// <summary>
		/// Se encarga de crear el LuaState e incializar todo lo necesario para
		/// el scripting
		/// </summary>
		void InitLua(lua_State* l);

		LuaManager();
	private:


		lua_State* L_;
		// Behaviour* behaviourTemplate_;
	};

#endif __LUA_MANAGER_H__