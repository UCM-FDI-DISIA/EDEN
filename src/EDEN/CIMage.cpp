#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <iostream>

#include "CImage.h"
#include "RenderManager.h"
#include "ScriptManager.h"
#include "ComponentArguments.h"


const std::string eden_ec::CImage::_id = "IMAGE";

eden_ec::CImage::CImage(std::string overlayName, float xPos, float yPos,
	float width, float height, std::string texture,
	int depth) {
	auto render = eden_render::RenderManager::Instance();
	int w = render->GetWindowWidth();
	int h = render->GetWindowHeight();
	int xx = w * xPos / 100;
	int yy = h * yPos / 100;
	xPos = xx - (width / 2);
	yPos = yy - (height / 2);


	_texture = texture;
	_overlayContainer = static_cast<Ogre::OverlayContainer*>(
		_overlayManager->createOverlayElement(
			"Panel", overlayName + std::to_string(_numUIElements)));
	_overlayContainer->setMetricsMode(Ogre::GMM_PIXELS);
	_overlayContainer->setPosition(xPos, yPos);
	_overlayContainer->setDimensions(width, height);
	_overlayContainer->setMaterialName(_texture);

	// Creo un elemento overlay para añadirle el panel
	_overlayElement =
		_overlayManager->create("over" + std::to_string(_numUIElements));
	_overlayElement->add2D(_overlayContainer);
	_overlayElement->show();
	SetDepth(depth);

}

eden_ec::CImage::~CImage() {}

void eden_ec::CImage::Init(eden_script::ComponentArguments* args) {
	auto render = eden_render::RenderManager::Instance();
	int xPos = args->GetValueToInt("XPos");
	int yPos = args->GetValueToInt("YPos");
	int width = args->GetValueToInt("Width");
	int height = args->GetValueToInt("Height");

	int w = render->GetWindowWidth();
	int h = render->GetWindowHeight();
	int xx = w * xPos / 100;
	int yy = h * yPos / 100;
	xPos = xx - (width / 2);
	yPos = yy - (height / 2);


	_texture = args->GetValueToString("Texture");
	_overlayContainer = static_cast<Ogre::OverlayContainer*>(
		_overlayManager->createOverlayElement(
			"Panel", args->GetValueToString("OverlayName") + std::to_string(_numUIElements)));
	_overlayContainer->setMetricsMode(Ogre::GMM_PIXELS);
	_overlayContainer->setPosition(xPos, yPos);
	_overlayContainer->setDimensions(width, height);
	_overlayContainer->setMaterialName(_texture);

	// Creo un elemento overlay para añadirle el panel
	_overlayElement =
		_overlayManager->create("over" + std::to_string(_numUIElements));
	_overlayElement->add2D(_overlayContainer);
	_overlayElement->show();
	SetDepth(args->GetValueToInt("Depth"));
	
}