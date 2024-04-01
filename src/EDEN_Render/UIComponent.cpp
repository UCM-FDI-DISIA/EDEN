#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <sys/stat.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h> 
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlayElement.h>
#include <OgreFontManager.h>

#include "UIComponent.h"
#include <InputManager.h>
#include "Canvas.h"

#include "ErrorHandler.h"

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
	if (!FileExists(_rute + "UI_MATERIALS.material"))
		eden_error::ErrorHandler::Instance()->Exception("[SPY ERROR]: Failed to load the file with all UI Materials", "UI_MATERIALS.material");
}

eden_ec::UIComponent::~UIComponent() {
	eden_canvas::Canvas::Instance()->removeRenderEntity(this);
	_overlayManager->destroyOverlayElement(_overlayContainer);
	if(_overlayElement!=nullptr)_overlayManager->destroy(_overlayElement);
	_overlayContainer = nullptr;
	_overlayElement = nullptr;
	_overlayManager = nullptr;
	_text = nullptr;
	_numUIElements--;
}

void eden_ec::UIComponent::Show() { _overlayElement->show(); }

void eden_ec::UIComponent::Hide() { _overlayElement->hide(); }

void eden_ec::UIComponent::SetDepth(float pos) {
	_overlayElement->setZOrder(Ogre::ushort(pos));
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

bool eden_ec::UIComponent::FileExists(std::string const& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

void eden_ec::UIComponent::SetMaterial(std::string const& matName) {

	if(!FileExists(_rute+matName))
		eden_error::ErrorHandler::Instance()->Exception("[SPY ERROR]: Failed to load Texture", matName);
	try {
		_overlayContainer->setMaterialName(matName);
	}
	catch (std::exception e) {
		eden_error::ErrorHandler::Instance()->Exception("[SPY ERROR]: Failed to load file of Material in UI_MATERIALS folder", matName);
	}
}

void eden_ec::UIComponent::SetOverlayVisible(bool vis) {
	_overlayElement->setVisible(vis);
}

bool eden_ec::UIComponent::IsVisible() { return _overlayElement->isVisible(); }

float eden_ec::UIComponent::GetDepth() { return _overlayElement->getZOrder(); }

eden_utils::Vector3 const eden_ec::UIComponent::GetColor() const {
	Ogre::ColourValue color = _overlayContainer->getColour();
	return eden_utils::Vector3(color.r, color.g, color.a);
}

std::pair<float, float> const eden_ec::UIComponent::GetDimensions() const {
	return std::pair<float, float>(_overlayContainer->getWidth(), _overlayContainer->getHeight());
}

std::pair<float, float> const eden_ec::UIComponent::GetRelativeDimensions() const {
	return std::pair<float, float>(_overlayContainer->_getWidth(), _overlayContainer->_getHeight());
}

std::pair<float, float> const eden_ec::UIComponent::GetPosition() const {
	return std::pair<float, float>(_overlayContainer->getLeft(), _overlayContainer->getTop());
}

std::pair<float, float> const eden_ec::UIComponent::GetRelativePosition() const {
	return std::pair<float, float>(_overlayContainer->_getLeft(), _overlayContainer->_getTop());
}

std::string const& eden_ec::UIComponent::GetMaterialName() {
	return _overlayContainer->getMaterialName();
}

void eden_ec::UIComponent::CreateImage(std::string overlayName, float xPos, float yPos,
	float width, float height, std::string texture,	int depth) 
{
	_texture = texture;
	SetOverlayContainer(overlayName, xPos, yPos, width, height);
	SetMaterial(_texture);

	// Creo un elemento overlay para a�adirle el panel
	SetOverlayElement(depth);
}

void eden_ec::UIComponent::LoadFont(std::string font) {

	try {
		Ogre::FontPtr mFont = Ogre::FontManager::getSingleton().create(font, "General");
		mFont->setParameter("type", "truetype");
		mFont->setParameter("source", font);
		mFont->setParameter("size", "100");
		mFont->setParameter("resolution", "250");
		mFont->load();
	}
	catch (std::exception) {
		eden_error::ErrorHandler::Instance()->Exception("[SPY ERROR]: Failed to load the font", font);
	}
}

void eden_ec::UIComponent::CreateText(std::string overlayName, float xPos, float yPos,
	float tam, std::string text, std::string font, float rColor, float gColor, float bColor, int depth)
{
	if (!Ogre::FontManager::getSingleton().resourceExists(font)) {
		LoadFont(font);
	}
	
	SetOverlayContainer(overlayName, xPos, yPos, tam *text.length(), tam);
	SetOverlayElement(depth);
	
	_text= static_cast<Ogre::TextAreaOverlayElement*>(_overlayManager->createOverlayElement(
		"TextArea", overlayName+"_text_" + std::to_string(_numUIElements)));
	_text->setMetricsMode(Ogre::GMM_PIXELS);
	_text->setPosition(_overlayContainer->getWidth()/2 , _overlayContainer->getHeight() / 2);
	_text->setCaption(text);
	_text->setCharHeight(tam);
	_text->setFontName(font);
	_text->setColour(Ogre::ColourValue(rColor/255,gColor/255,bColor/255));
	_text->setAlignment(Ogre::TextAreaOverlayElement::Center);
	_text->show();
	_overlayContainer->addChild(_text);
}

std::string eden_ec::UIComponent::GetText() {
	std::string text = "";
	if (_text != nullptr)text = _text->getCaption();
	return text;
}

void eden_ec::UIComponent::SetText(const std::string& text) {
	if (_text != nullptr) {
		_text->setCaption(text);
		_overlayContainer->setDimensions(_text->getCharHeight() * text.length(), _text->getCharHeight());
		Resize();
	}
}

void eden_ec::UIComponent::SetOverlayContainer(std::string overlayName, float xPos, float yPos,
	float width, float height) 
{
	_overlayContainer = static_cast<Ogre::OverlayContainer*>(
		_overlayManager->createOverlayElement(
			"Panel", overlayName + std::to_string(_numUIElements)));
	_overlayContainer->setMetricsMode(Ogre::GMM_PIXELS);
	_overlayContainer->setPosition(xPos, yPos);
	_overlayContainer->setDimensions(width, height);
	_overlayContainer->show();
}

void eden_ec::UIComponent::SetOverlayElement(int depth) {
	// Creo un elemento overlay para a�adirle el panel
	_overlayElement =
		_overlayManager->create("over" + std::to_string(_numUIElements));
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

	if (_text != nullptr) {
		if(_oWidth/_text->getCaption().length()<_oHeight)_text->setCharHeight(_oWidth / _text->getCaption().length());
		else _text->setCharHeight(_oHeight);
		_text->setPosition(_overlayContainer->getWidth() / 2, _overlayContainer->getHeight() / 2);
	}
}

void eden_ec::UIComponent::SetParameters() {
	_rWidth = GetRelativeDimensions().first;
	_rHeight = GetRelativeDimensions().second;
	_rPos = GetRelativePosition();

	_oWidth = GetDimensions().first;
	_oHeight = GetDimensions().second;
	_oPos = GetPosition();
}