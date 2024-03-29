#include <iostream>

#include <lua.hpp>
#include <LuaBridge.h>

#include "CLuaBehaviour.h"
#include <ScriptManager.h>
#include <LuaManager.h>
#include <ScriptManager.h>
#include <ComponentArguments.h>
#include "Entity.h"
#include "Hito1Prueba.h"

const std::string eden_ec::CLuaBehaviour::_id = "BEHAVIOUR";

eden_ec::CLuaBehaviour::CLuaBehaviour(std::string name) : _behaviourLua(nullptr), _name(name) {
}

eden_ec::CLuaBehaviour::CLuaBehaviour(std::string name, luabridge::LuaRef* behaviourLua)
	: _behaviourLua(behaviourLua),_name(name) {
}

eden_ec::CLuaBehaviour::~CLuaBehaviour() { delete _behaviourLua; }

void eden_ec::CLuaBehaviour::SetLuaScript(luabridge::LuaRef* behaviourLua) {
	_behaviourLua = behaviourLua;
	_L = eden_script::ScriptManager::Instance()->GetLuaManager()->GetLuaState();
}

void eden_ec::CLuaBehaviour::OnButtonClick() {
	luabridge::LuaRef OnButtonClickLua = (*_behaviourLua)["OnButtonClick"];
	if (OnButtonClickLua.isFunction()) {
		luabridge::setGlobal(_L, this, "this");
		try {
			OnButtonClickLua();
		}
		catch (luabridge::LuaException e) {
			std::cout << e.what() << "\n";
		}
		luabridge::getGlobal(_L, "this");
	}
}

void eden_ec::CLuaBehaviour::OnButtonReleased() {
	luabridge::LuaRef onButtonReleasedLua =
		(*_behaviourLua)["OnButtonReleased"];
	if (onButtonReleasedLua.isFunction()) {
		luabridge::setGlobal(_L, this, "this");
		try {
			onButtonReleasedLua();
		}
		catch (luabridge::LuaException e) {
			std::cout << e.what() << "\n";
		}
		luabridge::getGlobal(_L, "this");
	}
}

void eden_ec::CLuaBehaviour::OnCollisionEnter(eden_ec::Entity* other)
{
	luabridge::LuaRef onCollisionEnterLua = (*_behaviourLua)["OnCollisionEnter"];
	if (onCollisionEnterLua.isFunction()) {
		luabridge::setGlobal(_L, this, "this");
		luabridge::setGlobal(_L, other, "other");
		try {
			onCollisionEnterLua(other);
		}
		catch (luabridge::LuaException e) {
			std::cout << e.what() << "\n";
		}
		luabridge::getGlobal(_L, "other");
		luabridge::getGlobal(_L, "this");
	}
}

void eden_ec::CLuaBehaviour::OnCollisionStay(eden_ec::Entity* other)
{
	luabridge::LuaRef onCollisionStayLua =
		(*_behaviourLua)["OnCollisionStay"];
	if (onCollisionStayLua.isFunction()) {
		luabridge::setGlobal(_L, this, "this");
		luabridge::setGlobal(_L, other, "other");
		try {
			onCollisionStayLua();
		}
		catch (luabridge::LuaException e) {
			std::cout << e.what() << "\n";
		}
		luabridge::getGlobal(_L, "other");
		luabridge::getGlobal(_L, "this");
	}
}

void eden_ec::CLuaBehaviour::OnCollisionExit(eden_ec::Entity* other)
{
	luabridge::LuaRef onCollisionExitLua =
		(*_behaviourLua)["OnCollisionExit"];
	if (onCollisionExitLua.isFunction()) {
		luabridge::setGlobal(_L, this, "this");
		luabridge::setGlobal(_L, other, "other");
		try {
			onCollisionExitLua();
		}
		catch (luabridge::LuaException e) {
			std::cout << e.what() << "\n";
		}
		luabridge::getGlobal(_L, "other");
		luabridge::getGlobal(_L, "this");
	}
}

luabridge::LuaRef* eden_ec::CLuaBehaviour::GetBehaviourLua() { return _behaviourLua; }

lua_State* eden_ec::CLuaBehaviour::getLuaState() {
	return _L;
}

void eden_ec::CLuaBehaviour::Init(eden_script::ComponentArguments* args) {
	_name = args->GetValueToString("Script");
	eden_script::ScriptManager::Instance()->GetLuaManager()->LoadScript(_name, _ent);
 }