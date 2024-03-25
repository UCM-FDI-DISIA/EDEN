#define _CRTDBG_MAP_ALLOC
#include "CollisionLayer.h"

int physics_wrapper::CollisionLayer::_currentLayer = 0;

physics_wrapper::CollisionLayer::CollisionLayer(std::string layerName) : _layerName(layerName), _layer(1 << _currentLayer) {
	_currentLayer++;
}


std::string physics_wrapper::CollisionLayer::GetName() {
	return _layerName;
}

int physics_wrapper::CollisionLayer::GetLayer() {
	return _layer;
}

void physics_wrapper::CollisionLayer::AddCollisionToLayer(physics_wrapper::CollisionLayer* layer) {
	_collisionMask = _collisionMask | layer->_layer;
}

int physics_wrapper::CollisionLayer::GetCollisionMask() {
	return _collisionMask;
}



