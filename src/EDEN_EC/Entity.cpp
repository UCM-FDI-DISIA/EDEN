#include "Entity.h"
#include <ScriptManager.h>
#include <ComponentArguments.h>
#include "Component.h"
#include <LuaManager.h>
#include <ErrorHandler.h>

void eden_ec::Entity::AddComponents(eden_script::EntityInfo* entityInfo) {
    for (auto it : entityInfo->components) {
        AddComponentByRead(&it);
    }
}
 
eden_ec::Component* eden_ec::Entity::GetComponent(std::string id) {
    auto it = _components.find(id);
    if (it == _components.end()) {
        return nullptr;
    }
    else {
        return (*it).second;
    }
}

eden_ec::Component* eden_ec::Entity::AddComponentByRead(eden_script::ComponentArguments* info) {
    std::string id = info->GetID();
    if (!_components.contains(id)) {
        Component* c = ComponentFactory::Instance()->CreateComponentByName(id);
        if (!c) eden_error::ErrorHandler::Instance()->Exception("Component not found", "Component " + id + " was not found in factory registry");
        _components.emplace(id, c);
        c->SetContext(this);
        c->Init(info);
        return c;
    }
    else {
        eden_error::ErrorHandler::Instance()->Warning("Component " + id + " was not created due to it already exists in Entity " + _ID);
        return nullptr;
    }
}

void eden_ec::Entity::AwakeComponents() {
    for (auto cmp : _components) {
        cmp.second->Awake();
    }
}

void eden_ec::Entity::StartComponents() {
    for (auto cmp : _components) {
        cmp.second->Start();
    }
}


bool eden_ec::Entity::HasComponent(std::string id) {
    return _components.count(id);
}

void eden_ec::Entity::Update(float t) {
    if (_active) {
        for (auto it = _components.begin(); it != _components.end(); ++it) {
            if(it->second->IsActive()) it->second->Update(t);
        }
    }
}

eden_ec::Entity::~Entity()
{
    for (auto it = _components.begin(); it != _components.end(); ) {
        delete (it)->second;
        (it)->second = nullptr;
        it = _components.erase(it);
    }
}

void eden_ec::Entity::RemoveComponent(std::string id) {
    auto iter = _components.find(id);
    if (iter != _components.end()) {
        delete (*iter).second;
        _components.erase(iter);
    }
}

std::string eden_ec::Entity::GetSceneID() {
    return _sceneID;
}
