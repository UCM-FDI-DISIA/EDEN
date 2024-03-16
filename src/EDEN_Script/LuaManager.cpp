#include "LuaManager.h"
#include "../EDEN/CButtonBehaviour.h"
#include "../EDEN/Transform.h"
#include "../EDEN/Entity.h"
#include "ComponentFactory.h"

#include <lua.hpp>
#include "LuaBridge/LuaBridge.h"
#include <iostream>


LuaManager::LuaManager() 
{
	L_ = nullptr;
}

LuaManager::~LuaManager()
{
	L_ = nullptr;
}

void  LuaManager::InitLua(lua_State* l) {
	L_=l;
	RegisterClasses();
}

void  LuaManager::RegisterClasses() {
	// Registramos la clase base y sus funciones miembro
	luabridge::getGlobalNamespace(L_)
		.beginClass<eden_ec::CButtonBehaviour>("BEHAVIOUR")
		.addFunction("onButtonClick", &eden_ec::CButtonBehaviour::OnButtonClick)
		.addFunction("onButtonReleased", &eden_ec::CButtonBehaviour::OnButtonReleased)
		.addProperty("entity", &eden_ec::CButtonBehaviour::_ent)
		.addProperty("name", &eden_ec::CButtonBehaviour::_name)
		.endClass();
}

bool  LuaManager::LoadScript(std::string name, eden_ec::Entity* ent) {
	// Cargamos el script de Lua desde un archivo
	std::string path = "assets/mesh/" + name + ".lua";
	if (luaL_dofile(L_, path.c_str())) {
		std::cerr << "[SPY ERROR]: Failed to load script: " << lua_tostring(L_, -1) << "\n";
		return false;
	}

	// Creamos una instancia de Behaviour y la pasamos al script
	eden_ec::CButtonBehaviour* behaviourScript = static_cast<eden_ec::CButtonBehaviour*>(ent->GetComponent("BEHAVIOUR"));

	luabridge::setGlobal(L_, behaviourScript, name.c_str());

	// Obtenemos el objeto behaviour desde Lua
	auto behaviourLua =
		new luabridge::LuaRef(luabridge::getGlobal(L_, (name + "Lua").c_str()));

	behaviourScript->SetLuaScript(behaviourLua);

	return true;
}

lua_State*  LuaManager::GetLuaState() { return L_; }