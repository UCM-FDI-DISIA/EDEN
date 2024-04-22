#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <sys/stat.h>

#pragma warning(push)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h> 
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlayElement.h>
#include <OgreFontManager.h>
#pragma warning(pop)

#include "UIComponent.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "ResourcesManager.h"
#include "Canvas.h"
#include "Entity.h"
#include "ErrorHandler.h"
#include <string>

int eden_ec::UIComponent::_numUIElements = 0;

eden_ec::UIComponent::UIComponent() {
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
	if(_overlayElement!=nullptr) _overlayManager->destroy(_overlayElement);
	_overlayContainer = nullptr;
	_overlayElement = nullptr;
	_overlayManager = nullptr;
	_text = nullptr;
}

void eden_ec::UIComponent::Show(bool changedFromCanvas) { if(!changedFromCanvas || (changedFromCanvas && canvasVisible)) _overlayElement->show(); if(!changedFromCanvas) canvasVisible = true; }

void eden_ec::UIComponent::Hide(bool changedFromCanvas) { _overlayElement->hide(); if(!changedFromCanvas) canvasVisible = false; }

void eden_ec::UIComponent::SetDepth(float pos) {
	_overlayElement->setZOrder(Ogre::ushort(pos));
}

void eden_ec::UIComponent::SetColor(eden_utils::Vector3 const& color) {
	_overlayContainer->setColour(Ogre::ColourValue(color.GetX(), color.GetY(), color.GetZ()));
}

void eden_ec::UIComponent::SetDimensions(float width, float height) {
	_overlayContainer->setDimensions(width, height);
	float w = ((100 * width) / _screenSize.first)/100;
	float h = ((100 * height) / _screenSize.second) / 100;
	_overlayContainer->_setDimensions(w, h);
	SetSizeParams();
}

void eden_ec::UIComponent::SetRelativeDimensions(float width, float height) {
	_overlayContainer->_setDimensions(width, height);
	SetSizeParams();
}

void eden_ec::UIComponent::SetPosition(float xPos, float yPos) {
	_overlayContainer->setPosition(xPos, yPos);
	SetPosParams();
}

void eden_ec::UIComponent::SetRelativePosition(float xPos, float yPos) {
	_overlayContainer->_setPosition(xPos, yPos);
	SetPosParams();
}

void eden_ec::UIComponent::SetMaterial(std::string const& matName) {

	std::string material = matName;
	eden_resources::ResourcesManager::Resources res = eden_resources::ResourcesManager::Materials;
	if (material == "default.png") res = eden_resources::ResourcesManager::Default;
	if (!eden_resources::ResourcesManager::Instance()->FileExist(material, res)) {
		if (material == "default.png")eden_error::ErrorHandler::Instance()->Exception("[SPY ERROR]:Load Material Error", "Failed to load Texture: " + matName);
		else { 
			eden_error::ErrorHandler::Instance()->Warning("No se ha encontrado el material: "+ material);
			material = "default.png"; 
			SetMaterial("default.png");
		}
	}
	else {
		try {
			_overlayContainer->setMaterialName(material);
		}
		catch (std::exception e) {
			if (material != "default.png") {
				eden_error::ErrorHandler::Instance()->Warning("No se ha podido cargar el material: " + material);
				SetMaterial("default.png");
			}
			else {
				if (material != "default.png")eden_error::ErrorHandler::Instance()->Exception("[SPY ERROR]:Load Material Error", "Failed to load file of Material in UI_MATERIALS folder: " + material);
				else eden_error::ErrorHandler::Instance()->Exception("[SPY ERROR]:Load Material Error", "Failed to load file of Material in Default.material: " + material);
			}
		}
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
	if (!eden_resources::ResourcesManager::Instance()->FileExist("UI_MATERIALS.material", eden_resources::ResourcesManager::Materials))
		eden_error::ErrorHandler::Instance()->Exception("[SPY ERROR]:Load Material Error", "Failed to load the file with all UI Materials: UI_MATERIALS.material");


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
	catch (std::exception e) {
		if(font == "default.ttf")eden_error::ErrorHandler::Instance()->Exception("[SPY ERROR] Load Font Error:", "Failed to load the font: " + font);
		else {
			eden_error::ErrorHandler::Instance()->Warning("Failed to load the font: " + font);
		}
 	}
}

void eden_ec::UIComponent::CreateText(std::string overlayName, float xPos, float yPos,
	float tam, std::string text, std::string font, float rColor, float gColor, float bColor, int depth)
{
	if (!Ogre::FontManager::getSingleton().resourceExists(font)) {
		if (eden_resources::ResourcesManager::Instance()->FileExist(font, eden_resources::ResourcesManager::Fonts)) {
			LoadFont(font);
		}
		else if (eden_resources::ResourcesManager::Instance()->FileExist("default.ttf", eden_resources::ResourcesManager::Default)) {
			font = "default.ttf";
			if (!Ogre::FontManager::getSingleton().resourceExists("default.ttf"))LoadFont("default.ttf");
		}
		else eden_error::ErrorHandler::Instance()->Exception("[SPY ERROR] Load Font Error:", "Failed to load the font: default.ttf");
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

void eden_ec::UIComponent::Register(std::string sceneID)
{
	_sceneID = sceneID;
	eden_canvas::Canvas::Instance()->addRenderEntity(this);
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
	// Creo un elemento overlay para aniadirle el panel
	_overlayElement =
		_overlayManager->create("over" + std::to_string(_numUIElements));
	_overlayElement->add2D(_overlayContainer);
	_overlayElement->show();
	SetDepth((float)depth);
}

void eden_ec::UIComponent::Resize() {

	_screenSize = eden_render::RenderManager::Instance()->GetResolution();
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
	_screenSize = eden_render::RenderManager::Instance()->GetResolution();
	SetSizeParams();
	SetPosParams();
}

void eden_ec::UIComponent::SetSizeParams()
{
	_oWidth = GetDimensions().first;
	_oHeight = GetDimensions().second;
	_rWidth = GetRelativeDimensions().first;
	_rHeight = GetRelativeDimensions().second;
}

void eden_ec::UIComponent::SetPosParams()
{
	_rPos = GetRelativePosition();
	_oPos = GetPosition();
}
