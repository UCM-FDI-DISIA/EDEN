#include "Canvas.h"
#include <Entity.h>
#include "UIComponent.h"


eden_canvas::Canvas::~Canvas() {

}

void eden_canvas::Canvas::Resize() {
	for (auto ent : _entities) {
		ent->Resize();
	}
}

void eden_canvas::Canvas::InitCanvas(){
	for (auto ent : _entities) {
		ent->SetParameters();
	}
}

void eden_canvas::Canvas::addRenderEntity(eden_ec::UIComponent* ent) {
	_entities.insert(ent);
}

void eden_canvas::Canvas::removeRenderEntity(eden_ec::UIComponent* ent) {
	_entities.erase(ent);
}

