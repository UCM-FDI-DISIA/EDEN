#define _CRTDBG_MAP_ALLOC
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
	class  CLuaBehaviour : public Component {
		friend class eden_script::LuaManager;
	public:

		/// @brief Constructora base
		CLuaBehaviour() = default;

		/// @brief Constructora
		/// @param name Nombre del script
		CLuaBehaviour(std::string name);
	
		/// @brief Constructora que inicializa un Behaviour con la LuaRef se le pase
		/// @param behaviourLua LuaRef del script .lua que se desea
		CLuaBehaviour(std::string name, luabridge::LuaRef* behaviourLua);
		
		/// @brief El destructor se encarga de borrar el puntero de LuaRef
		~CLuaBehaviour() override;

		/// @brief Asigna valor a la LuaRef que se corresponde al script .lua
		/// @param behaviourLua LuaRef 
		void SetLuaScript(luabridge::LuaRef* behaviourLua);
		
		/// @brief Metodo que se llama cuando se hace click en el boton
		virtual void OnButtonClick();

		/// brief Metodo que se llama cuando ya no se hace click en el boton
		virtual void OnButtonReleased();

		/// @brief Metodo que se llama cuando entra una colision
		virtual void OnCollisionEnter(eden_ec::Entity* other);

		/// @brief Metodo que se llama cuando se mantiene una colision
		virtual void OnCollisionStay(eden_ec::Entity* other);

		/// @brief Metodo que se llama cuando termina una colision
		virtual void OnCollisionExit(eden_ec::Entity* other);

		/// Devuelve la LuaRef al behaviour en Lua
		luabridge::LuaRef* GetBehaviourLua();

		lua_State* getLuaState();

		/// @brief Construye el componente dado unos argumentos. Se obtendr�n de una lectura de un .lua
		/// @param args Argumentos le�dos de .lua
		void Init(eden_script::ComponentArguments* args) override;

		/// @brief Override necesario. No se usa
		void Start() override {};

		/// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
		static std::string GetID() { return _id; }

	protected:
		const static std::string _id;

		/// @brief LuaRef del script. Esta clase representa el script .lua en C++
		luabridge::LuaRef* _behaviourLua = nullptr;

		/// @brief Puntero de LuaState
		lua_State* _L = nullptr;
	
		/// @brief Nombre del script
		std::string _name = " ";
	};
}

#endif  
