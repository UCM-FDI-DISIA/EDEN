#define _CRTDBG_MAP_ALLOC
#include "CollisionLayer.h"
#include "ErrorHandler.h"

physics_wrapper::CollisionLayer::CollisionLayer(std::string layerName, std::string sceneID) : _layerName(layerName){
	auto it = _currentLayer.find(sceneID);
	if (it == _currentLayer.end()) {
		_currentLayer.insert({ sceneID, 0 });
	}
	
	int& currentLayer = _currentLayer[sceneID];
	if (currentLayer >= MAX_COLLISION_GROUP_NUMBER)
	{
		std::string title = "Maximum capacity of collision layers (32) reached";
		std::string message = "CollisionLayer ERROR in line 12. Could not create more than 32 layers, error creating layer: " + layerName;
		eden_error::ErrorHandler::Instance()->Exception(title, message);
	}
	
	_layer = 1 << currentLayer;
	currentLayer++;
}

std::string physics_wrapper::CollisionLayer::GetName() {
	return _layerName;
}

int physics_wrapper::CollisionLayer::GetLayer() {
	return _layer;
}

void physics_wrapper::CollisionLayer::RemoveCollisionToLayer(physics_wrapper::CollisionLayer* layer) {
	_collisionMask = _collisionMask & (~layer->_layer);
}

int physics_wrapper::CollisionLayer::GetCollisionMask() {
	return _collisionMask;
}

std::unordered_map<std::string, int> physics_wrapper::CollisionLayer::_currentLayer;

