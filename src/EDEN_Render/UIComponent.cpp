#include <iostream>

#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h> 
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlayElement.h>

#include "UIComponent.h"
#include <InputManager.h>
#include "Canvas.h"

const std::string eden_ec::UIComponent::_id = "UICOMPONENT";
int eden_ec::UIComponent::_numUIElements = 0;

eden_ec::UIComponent::UIComponent() {
	
	eden_canvas::Canvas::Instance()->addRenderEntity(this);
	_overlayManager = Ogre::OverlayManager::getSingletonPtr();
	_inputManager = eden_input::InputManager::Instance();
	_numUIElements++;

	_oHeight = 0;
	_oWidth = 0;
	_rHeight = 0;
	_rWidth = 0;
}

eden_ec::UIComponent::~UIComponent() {
	eden_canvas::Canvas::Instance()->removeRenderEntity(this);
	_overlayManager->destroyOverlayElement(_overlayContainer);
	_overlayManager->destroy(_overlayElement);
	_overlayContainer = nullptr;
	_overlayElement = nullptr;
	_overlayManager = nullptr;
	_numUIElements--;
}

void eden_ec::UIComponent::Show() { _overlayElement->show(); }

void eden_ec::UIComponent::Hide() { _overlayElement->hide(); }

void eden_ec::UIComponent::SetDepth(float pos) {
	_overlayElement->setZOrder(Ogre::ushort(pos));
}

void eden_ec::UIComponent::SetCaption(std::string const& caption) {
	_overlayContainer->setCaption(caption);
}

void eden_ec::UIComponent::SetColor(eden_utils::Vector3 const& color) {
	_overlayContainer->setColour(Ogre::ColourValue(color.GetX(), color.GetY(), color.GetZ()));
}

void eden_ec::UIComponent::SetDimensions(float width, float height) {
	_overlayContainer->setDimensions(width, height);
}

void eden_ec::UIComponent::SetRelativeDimensions(float width, float height) {
	_overlayContainer->_setDimensions(width, height);
}

void eden_ec::UIComponent::SetPosition(float xPos, float yPos) {
	_overlayContainer->setPosition(xPos, yPos);
}

void eden_ec::UIComponent::SetRelativePosition(float xPos, float yPos) {
	_overlayContainer->_setPosition(xPos, yPos);
}

void eden_ec::UIComponent::SetMaterial(std::string const& matName) {
	_overlayContainer->setMaterialName(matName);
}

void eden_ec::UIComponent::SetOverlayVisible(bool vis) {
	_overlayElement->setVisible(vis);
}

bool eden_ec::UIComponent::IsVisible() { return _overlayElement->isVisible(); }

float eden_ec::UIComponent::GetDepth() { return _overlayElement->getZOrder(); }

std::string const& eden_ec::UIComponent::GetCaption() {
	return _overlayContainer->getCaption();
}

eden_utils::Vector3 const& eden_ec::UIComponent::GetColor() {
	return eden_utils::Vector3(_overlayContainer->getColour().r, _overlayContainer->getColour().g, _overlayContainer->getColour().a);
}

std::pair<float, float> const& eden_ec::UIComponent::GetDimensions() {
	return std::pair<float, float>(_overlayContainer->getWidth(), _overlayContainer->getHeight());
}

std::pair<float, float> const& eden_ec::UIComponent::GetRelativeDimensions() {
	return std::pair<float, float>(_overlayContainer->_getWidth(), _overlayContainer->_getHeight());
}

std::pair<float, float> const& eden_ec::UIComponent::GetPosition() {
	return std::pair<float, float>(_overlayContainer->getLeft(), _overlayContainer->getTop());
}

std::pair<float, float> const& eden_ec::UIComponent::GetRelativePosition() {
	return std::pair<float, float>(_overlayContainer->_getLeft(), _overlayContainer->_getTop());
}

std::string const& eden_ec::UIComponent::GetMaterialName() {
	return _overlayContainer->getMaterialName();
}

void eden_ec::UIComponent::CreateImage(std::string overlayName, float xPos, float yPos,
	float width, float height, std::string texture,
	int depth) {

	_texture = texture;
	_overlayContainer = static_cast<Ogre::OverlayContainer*>(
		_overlayManager->createOverlayElement(
			"Panel", overlayName+ std::to_string(_numUIElements)));
	_overlayContainer->setMetricsMode(Ogre::GMM_PIXELS);
	_overlayContainer->setPosition(xPos, yPos);
	_overlayContainer->setDimensions(width, height);
	_overlayContainer->setMaterialName(_texture);

	// Creo un elemento overlay para a�adirle el panel
	_overlayElement =
		_overlayManager->create("over"+ std::to_string(_numUIElements));
	_overlayElement->add2D(_overlayContainer);
	_overlayElement->show();
	SetDepth((float)depth);

}

void eden_ec::UIComponent::Resize() {

	SetRelativeDimensions(_rWidth, _rHeight);
	SetRelativePosition(_rPos.first, _rPos.second);

	_oWidth = GetDimensions().first;
	_oHeight = GetDimensions().second;
	_oPos = GetPosition();
}

void eden_ec::UIComponent::SetParameters() {
	_rWidth = GetRelativeDimensions().first;
	_rHeight = GetRelativeDimensions().second;
	_rPos = GetRelativePosition();

	_oWidth = GetDimensions().first;
	_oHeight = GetDimensions().second;
	_oPos = GetPosition();
}