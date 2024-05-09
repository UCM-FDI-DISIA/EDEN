#ifndef EDEN_C_BUTTON_BEHAVIOUR_H
#define EDEN_C_BUTTON_BEHAVIOUR_H

#include "Component.h"

#include <string>

#include "defs.h"

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
	class CLuaBehaviour : public Component {
		friend class eden_script::LuaManager;
	public:

		/// @brief Constructora base
		EDEN_API CLuaBehaviour() = default;

		/// @brief Constructora
		/// @param name Nombre del script
		EDEN_API CLuaBehaviour(std::string name);
	
		/// @brief Constructora que inicializa un Behaviour con la LuaRef se le pase
		/// @param behaviourLua LuaRef del script .lua que se desea
		EDEN_API CLuaBehaviour(std::string name, luabridge::LuaRef* behaviourLua);
		
		/// @brief El destructor se encarga de borrar el puntero de LuaRef
		EDEN_API ~CLuaBehaviour() override;

		/// @brief Asigna valor a la LuaRef que se corresponde al script .lua
		/// @param behaviourLua LuaRef 
		EDEN_API void SetLuaScript(luabridge::LuaRef* behaviourLua);
		
		/// @brief Metodo que se llama cuando se hace click en el boton
		EDEN_API virtual void OnButtonClick(eden_ec::Entity* selfButton);

		/// brief Metodo que se llama cuando ya no se hace click en el boton
		EDEN_API virtual void OnButtonReleased(eden_ec::Entity* selfButton);

		/// @brief Metodo que se llama cuando entra una colision
		EDEN_API virtual void OnCollisionEnter(eden_ec::Entity* self, eden_ec::Entity* other);

		/// @brief Metodo que se llama cuando se mantiene una colision
		EDEN_API virtual void OnCollisionStay(eden_ec::Entity* self, eden_ec::Entity* other);

		/// @brief Metodo que se llama cuando termina una colision
		EDEN_API virtual void OnCollisionExit(eden_ec::Entity* self, eden_ec::Entity* other);

		/// Devuelve la LuaRef al behaviour en Lua
		EDEN_API luabridge::LuaRef* GetBehaviourLua();

		EDEN_API lua_State* getLuaState();

		/// @brief Construye el componente dado unos argumentos. Se obtendran de una lectura de un .lua
		/// @param args Argumentos leidos de .lua
		EDEN_API void Init(eden_script::ComponentArguments* args) override;

		/// @brief Override necesario. No se usa
		EDEN_API void Awake() override {};

		/// @brief Override necesario. No se usa
		EDEN_API void Start() override {};

		EDEN_API void LoadScript();

		/// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
		EDEN_API static std::string GetID() { return "BEHAVIOUR"; }

		/// @brief LuaRef del script. Esta clase representa el script .lua en C++
		luabridge::LuaRef* _behaviourLua = nullptr;

		/// @brief Puntero de LuaState
		lua_State* _L = nullptr;
	
		/// @brief Nombre del script
		std::string _name = " ";
	};
}

#endif  
