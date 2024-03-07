#include "UIComponent.h"

//#include "UIManager.h"
#include "../EDEN_Input/InputManager.h"
//#include "SeparityUtils\checkML.h"


#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h> 
#include <OgreTextAreaOverlayElement.h>

const std::string eden_ec::UIComponent::_id = "UICOMPONENT";
int eden_ec::UIComponent::_numUIElements = 0;
eden_ec::UIComponent::UIComponent() {

	_overlayManager = Ogre::OverlayManager::getSingletonPtr();
	_inputManager = eden_input::InputManager::Instance();
	_numUIElements++;
}

eden_ec::UIComponent::~UIComponent() {
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
	_overlayElement->setZOrder(pos);
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

void eden_ec::UIComponent::SetWidth(float width) {
	_overlayContainer->setWidth(width);
}

void eden_ec::UIComponent::SetHeigth(float heigth) {
	_overlayContainer->setHeight(heigth);
}

void eden_ec::UIComponent::SetHorizontalAligment(
	Ogre::GuiHorizontalAlignment const& hAligment) {
	_overlayContainer->setHorizontalAlignment(hAligment);
}

void eden_ec::UIComponent::SetVerticalAligment(
	Ogre::GuiVerticalAlignment const& vAligment) {
	_overlayContainer->setVerticalAlignment(vAligment);
}

void eden_ec::UIComponent::SetPosition(float xPos, float yPos) {
	_overlayContainer->setPosition(xPos, yPos);
}

void eden_ec::UIComponent::SetMaterial(std::string const& matName) {
	_overlayContainer->setMaterialName(matName);
}

void eden_ec::UIComponent::SetMetrics(Ogre::GuiMetricsMode const& mode) {
	_overlayContainer->setMetricsMode(mode);
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
	Ogre::ColourValue color = _overlayContainer->getColour();
	return eden_utils::Vector3(color.r, color.g, color.a);
}

std::pair<float, float> const& eden_ec::UIComponent::GetDimensions() {
	return std::pair<float, float>(GetWidth(), GetHeight());
}

float eden_ec::UIComponent::GetWidth() { return _overlayContainer->getWidth(); }

float eden_ec::UIComponent::GetHeight() {
	return _overlayContainer->getHeight();
}

Ogre::GuiHorizontalAlignment const&
eden_ec::UIComponent::GetHorizontalAligment() {
	return _overlayContainer->getHorizontalAlignment();
}

Ogre::GuiVerticalAlignment const& eden_ec::UIComponent::GetVerticalAligment() {
	return _overlayContainer->getVerticalAlignment();
}

std::pair<float, float> const& eden_ec::UIComponent::GetPosition() {
	return std::pair<float, float>(_overlayContainer->getTop(), _overlayContainer->getLeft());
}

std::string const& eden_ec::UIComponent::GetMaterialName() {
	return _overlayContainer->getMaterialName();
}

Ogre::GuiMetricsMode const& eden_ec::UIComponent::GetMetrics() {
	return _overlayContainer->getMetricsMode();
}

void eden_ec::UIComponent::Init(eden_script::ComponentArguments* args) {
	
}