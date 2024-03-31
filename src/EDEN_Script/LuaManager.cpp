#define _CRTDBG_MAP_ALLOC
#include <iostream>

#include "ErrorHandler.h"

#include "LuaManager.h"
#include <CLuaBehaviour.h>
#include <Hito1Prueba.h>
#include <Transform.h>
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
		.beginClass<eden_ec::CLuaBehaviour>("CLuaBehaviour")
		.addFunction("OnButtonClick", &eden_ec::CLuaBehaviour::OnButtonClick)
		.addFunction("OnButtonReleased", &eden_ec::CLuaBehaviour::OnButtonReleased)
		.addFunction("OnCollisionEnter", &eden_ec::CLuaBehaviour::OnCollisionEnter)
		.addFunction("OnCollisionStay", &eden_ec::CLuaBehaviour::OnCollisionStay)
		.addFunction("OnCollisionExit", &eden_ec::CLuaBehaviour::OnCollisionExit)
		.addProperty("entity", &eden_ec::CLuaBehaviour::_ent)
		.addProperty("name", &eden_ec::CLuaBehaviour::_name)
		.endClass();

	luabridge::getGlobalNamespace(_L)
		.beginClass<eden_ec::Entity>("Entity")
		.addProperty("id", &eden_ec::Entity::GetEntityID)
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
	eden_ec::CLuaBehaviour* behaviourScript = static_cast<eden_ec::CLuaBehaviour*>(ent->GetComponent("BEHAVIOUR"));

	luabridge::setGlobal(_L, behaviourScript, name.c_str());

	// Obtenemos el objeto behaviour desde Lua
	auto behaviourLua =
		new luabridge::LuaRef(luabridge::getGlobal(_L, (name + "Lua").c_str()));

	behaviourScript->SetLuaScript(behaviourLua);

	return true;
}

void eden_script::LuaManager::HandleError(const char* name) {
	std::string aux = name;
	eden_error::ErrorHandler::Instance()->Assert(false,("[SPY ERROR]: That class already exists as global: "+ aux));
}

lua_State* eden_script::LuaManager::GetLuaState() { return _L; }