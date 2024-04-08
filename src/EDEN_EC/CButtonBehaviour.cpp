#define _CRTDBG_MAP_ALLOC
#include <iostream>

#include <lua.hpp>
#include <LuaBridge.h>

#include "ErrorHandler.h"

#include "CButtonBehaviour.h"
#include <ScriptManager.h>
#include <LuaManager.h>
#include <ScriptManager.h>
#include <ComponentArguments.h>
#include "Entity.h"

const std::string eden_ec::CButtonBehaviour::_id = "BEHAVIOUR";

eden_ec::CButtonBehaviour::CButtonBehaviour(std::string name) : _behaviourLua(nullptr), _name(name) { _L = nullptr; }

eden_ec::CButtonBehaviour::CButtonBehaviour(std::string name, luabridge::LuaRef* behaviourLua)
	: _behaviourLua(behaviourLua), _name(name) {
	_L = nullptr;
}

eden_ec::CButtonBehaviour::~CButtonBehaviour() { delete _behaviourLua; }

void eden_ec::CButtonBehaviour::SetLuaScript(luabridge::LuaRef* behaviourLua) {
	_behaviourLua = behaviourLua;
	_L = eden_script::ScriptManager::Instance()->GetLuaManager()->GetLuaState();
}

void eden_ec::CButtonBehaviour::OnButtonClick() {
	luabridge::LuaRef OnButtonClickLua = (*_behaviourLua)["OnButtonClick"];
	if (OnButtonClickLua.isFunction()) {
		luabridge::setGlobal(_L, this, "this");
		try {
			OnButtonClickLua();
		}
		catch (luabridge::LuaException e) {
			eden_error::ErrorHandler::Instance()->HandleException(e);
		}
		luabridge::getGlobal(_L, "this");
	}
}

void eden_ec::CButtonBehaviour::OnButtonReleased() {
	luabridge::LuaRef onButtonReleasedLua =
		(*_behaviourLua)["OnButtonReleased"];
	if (onButtonReleasedLua.isFunction()) {
		luabridge::setGlobal(_L, this, "this");
		try {
			onButtonReleasedLua();
		}
		catch (luabridge::LuaException e) {
			eden_error::ErrorHandler::Instance()->HandleException(e);
		}
		luabridge::getGlobal(_L, "this");
	}
}

luabridge::LuaRef* eden_ec::CButtonBehaviour::GetBehaviourLua() { return _behaviourLua; }

void eden_ec::CButtonBehaviour::Init(eden_script::ComponentArguments* args) {
	_name = args->GetValueToString("Script");
	eden_script::ScriptManager::Instance()->GetLuaManager()->LoadScript(_name, _ent);
 }