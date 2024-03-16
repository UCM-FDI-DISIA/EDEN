#ifndef __BUTTON__BEHAVIOUR_H
#define __BUTTON__BEHAVIOUR_H

#include "Component.h"

#include <string>

namespace luabridge {
	class LuaRef;
}

class lua_State;

namespace eden_ec {

	/// <summary>
	/// Clase que representa un script de comportamiento. El script se definira
	/// en Lua y se utilizara esta clase para poder gestionar su ciclo de vida y
	/// llamada a metodos en C++.
	/// </summary>
	class  CButtonBehaviour : public Component {
		friend class LuaManager;

	public:

		CButtonBehaviour() = default;
		/// <summary>
		/// Constructor vacio, asigna nullptr a la LuaRef, sera necesario
		/// asignarla posteriormente con setLuaScript()
		/// </summary>
		CButtonBehaviour(std::string name);
		/// <summary>
		/// Construye un Behaviour con la LuaRef se le pase
		/// </summary>
		/// <param name="behaviourLua">LuaRef del script .lua que se desea
		/// vincular a esta clase</param>
		CButtonBehaviour(std::string name, luabridge::LuaRef* behaviourLua);
		/// <summary>
		/// El destructor se encarga de borrar el puntero de LuaRef
		/// </summary>
		virtual ~CButtonBehaviour();

		/// <summary>
		/// Asigna valor a la LuaRef que se corresponde al script .lua
		/// </summary>
		/// <param name="behaviourLua">La LuaRef obtenida al hacer un
		/// luabridge::getGlobal con el script .lua</param>
		void SetLuaScript(luabridge::LuaRef* behaviourLua);
		
		/// <summary>
		/// Metodo que se llama cuando se hace click en el boton
		/// </summary>
		virtual void OnButtonClick();
		/// <summary>
		/// Metodo que se llama cuando ya no se hace click en el boton
		/// </summary>
		virtual void OnButtonReleased();

		/// <summary>
		/// Devuelve la LuaRef al behaviour en Lua, requiere Luabridge, usar bajo responsabilidad
		/// </summary>
		/// <returns>Una LuaRef al script en Lua</returns>
		luabridge::LuaRef* GetBehaviourLua();

		/// @brief Construye el componente dado unos argumentos. Se obtendrán de una lectura de un .lua
		/// @param args Argumentos leídos de .lua
		virtual void Init(eden_script::ComponentArguments* args);

		/// @brief Método update heredado de component
		void Update(float deltaTime) override {}

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		void Start() override {}

		/// @brief Definición de método estático GetID necesario para construcción de componentes
		static std::string GetID() { return _id; }

	protected:
		const static std::string _id;

		/// <summary>
		/// LuaRef del script. Esta clase representa el script .lua en C++,
		/// pudiendo usarlo para llamar a todos sus metodos en esta clase
		/// </summary>
		luabridge::LuaRef* _behaviourLua;
		lua_State* L_;
		/// <summary>
		/// Nombre del script
		/// </summary>
		std::string _name;
	};
}

#endif  
