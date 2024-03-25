#define _CRTDBG_MAP_ALLOC
#include <iostream>

#include "ErrorHandler.h"

#include "LuaManager.h"
#include <CButtonBehaviour.h>
#include <Entity.h>

eden_script::LuaManager::LuaManager()
{
	_L = nullptr;
}

eden_script::LuaManager::~LuaManager()
{
	_L = nullptr;
}

void eden_script::LuaManager::InitLua(lua_State* l) {
	_L=l;
	RegisterClasses();
}

void eden_script::LuaManager::RegisterClasses() {
	// Registramos la clase base y sus funciones miembro
	luabridge::getGlobalNamespace(_L)
		.beginClass<eden_ec::CButtonBehaviour>("CButtonBehaviour")
		.addFunction("OnButtonClick", &eden_ec::CButtonBehaviour::OnButtonClick)
		.addFunction("OnButtonReleased", &eden_ec::CButtonBehaviour::OnButtonReleased)
		.addProperty("entity", &eden_ec::CButtonBehaviour::_ent)
		.addProperty("name", &eden_ec::CButtonBehaviour::_name)
		.endClass();
}

bool eden_script::LuaManager::LoadScript(std::string name, eden_ec::Entity* ent) {
	// Cargamos el script de Lua desde un archivo
	std::string path = "assets/scripts/" + name + ".lua";
	if (luaL_dofile(_L, path.c_str())) {
		eden_error::ErrorHandler::Instance()->Exception("[SPY ERROR]: Failed to load script", lua_tostring(_L, -1));
		return false;
	}

	// Creamos una instancia de Behaviour y la pasamos al script
	eden_ec::CButtonBehaviour* behaviourScript = static_cast<eden_ec::CButtonBehaviour*>(ent->GetComponent("BEHAVIOUR"));

	luabridge::setGlobal(_L, behaviourScript, name.c_str());

	// Obtenemos el objeto behaviour desde Lua
	auto behaviourLua =
		new luabridge::LuaRef(luabridge::getGlobal(_L, (name + "Lua").c_str()));

	behaviourScript->SetLuaScript(behaviourLua);

	return true;
}

lua_State* eden_script::LuaManager::GetLuaState() { return _L; }