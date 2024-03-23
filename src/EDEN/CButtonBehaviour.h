#ifndef EDEN_C_BUTTON_BEHAVIOUR_H
#define EDEN_C_BUTTON_BEHAVIOUR_H

#include "Component.h"

#include <string>

namespace luabridge {
	class LuaRef;
}

namespace eden_script {
	class LuaManager;
}

struct lua_State;

namespace eden_ec {

	/// @brief Clase que representa un script de comportamiento. El script se definira
	/// en Lua y se utilizara esta clase para poder gestionar su ciclo de vida y
	/// llamada a metodos en C++.
	class  CButtonBehaviour : public Component {
		friend class eden_script::LuaManager;

	public:

		/// @brief Constructora base
		CButtonBehaviour() = default;

		/// @brief Constructora
		/// @param name Nombre del script
		CButtonBehaviour(std::string name);
	
		/// @brief Constructora que inicializa un Behaviour con la LuaRef se le pase
		/// @param behaviourLua LuaRef del script .lua que se desea
		CButtonBehaviour(std::string name, luabridge::LuaRef* behaviourLua);
		
		/// @brief El destructor se encarga de borrar el puntero de LuaRef
		virtual ~CButtonBehaviour();

		/// @brief Asigna valor a la LuaRef que se corresponde al script .lua
		/// @param behaviourLua LuaRef 
		void SetLuaScript(luabridge::LuaRef* behaviourLua);
		
		/// @brief Metodo que se llama cuando se hace click en el boton
		virtual void OnButtonClick();

		/// Metodo que se llama cuando ya no se hace click en el boton
		virtual void OnButtonReleased();

		/// Devuelve la LuaRef al behaviour en Lua
		luabridge::LuaRef* GetBehaviourLua();

		/// @brief Construye el componente dado unos argumentos. Se obtendrán de una lectura de un .lua
		/// @param args Argumentos leídos de .lua
		virtual void Init(eden_script::ComponentArguments* args);

		/// @brief Override necesario. No se usa
		void Start() override {};

		/// @brief Definición de método estático GetID necesario para construcción de componentes
		static std::string GetID() { return _id; }

	protected:
		const static std::string _id;

		/// @brief LuaRef del script. Esta clase representa el script .lua en C++
		luabridge::LuaRef* _behaviourLua;

		/// @brief Puntero de LuaState
		lua_State* _L = nullptr;
	
		/// @brief Nombre del script
		std::string _name;
	};
}

#endif  
