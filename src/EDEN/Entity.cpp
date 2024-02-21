#include "Entity.h"
#include "Component.h"

eden_ec::Component* eden_ec::Entity::getComponent(std::string id) {
    auto it = _components.find(id);
    if (it == _components.end()) {
        return nullptr;
    }
    else {
        return (*it).second;
    }
}

/// WIP
eden_ec::Component* eden_ec::Entity::addComponentByName(std::string id/*, Struct_Info info*/) {
    Component* c = ComponentFactory::Instance()->CreateComponentByName(id);
    _components.emplace(id, c);
    c->SetContext(this);
    c->initComponent();

    return c;
}


bool eden_ec::Entity::hasComponent(std::string id) {
    return _components.count(id);
}

void eden_ec::Entity::update(float t) {
    if (_active) {
        for (auto it = _components.begin(); it != _components.end(); ++it) {
            it->second->update(t);
        }
    }
}

void eden_ec::Entity::handleInput() {
    if (_active) {
        auto n = _components.size();
        for (auto it = _components.begin(); it != _components.end(); ++it) {
            it->second->handleInput();
        }
    }
}

void eden_ec::Entity::removeComponent(std::string id) {
    auto iter = _components.find(id);
    if (iter != _components.end()) {
        delete (*iter).second;
        _components.erase(iter);
    }
}