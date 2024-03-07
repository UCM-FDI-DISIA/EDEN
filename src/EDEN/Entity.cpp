#include "ScriptManager.h"
#include "ComponentArguments.h"

#include "Entity.h"
#include "Component.h"

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
    Component* c = ComponentFactory::Instance()->CreateComponentByName(id);
    _components.emplace(id, c);
    c->SetContext(this);
    c->Init(info);
    c->InitComponent();

    return c;
}


bool eden_ec::Entity::HasComponent(std::string id) {
    return _components.count(id);
}

void eden_ec::Entity::Update(float t) {
    if (_active) {
        for (auto it = _components.begin(); it != _components.end(); ++it) {
            it->second->Update(t);
        }
    }
}

void eden_ec::Entity::HandleInput() {
    if (_active) {
        auto n = _components.size();
        for (auto it = _components.begin(); it != _components.end(); ++it) {
            it->second->HandleInput();
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