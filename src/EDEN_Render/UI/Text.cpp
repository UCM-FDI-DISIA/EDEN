#include "Text.h"
#include "Resources\checkML.h"
#include "Resources\SDLUtils.h"
#include "Entity.h"
#include "Resources\Font.h"

eden_ec::TextComponent::TextComponent(std::string text, Font& f, Uint8 fr = 255, Uint8 fg = 255, Uint8 fb = 255,
    Uint8 br = 255, Uint8 bg = 255, Uint8 bb = 255) : _text(text), _f(f){
    _x = 0;
    _y = 0;
    _fontColor.r = fr;
    _fontColor.g = fg;
    _fontColor.b = fb;
    _bgColor.r = br;
    _bgColor.g = bg;
    _bgColor.b = bb;
    _textTexture = CreateTexture(this->_text, this->_f, this->_fontColor, this->_bgColor);
}

Texture* eden_ec::TextComponent::CreateTexture(std::string text, Font& f, SDL_Color fontColor, SDL_Color bgColor) {
    //Mac renderiza el texto de diferente manera que Windows, por tanto hacemos esa distinción aquí
#ifdef __APPLE__
    return new Texture(sdlutils().renderer(), text, f, fontColor, bgColor);
#endif

#ifdef __WINDOWS__
    if (bgColor.a <= 1) return new Texture(sdlutils().renderer(), text, f, fontColor);
    else return new Texture(sdlutils().renderer(), text, f, fontColor, bgColor);
#endif
}

void eden_ec::TextComponent::Update(float f) {
    Render();
}

void eden_ec::TextComponent::Render() {
    _textTexture->render(_x, _y);
}

void eden_ec::TextComponent::ChangeText(std::string text) {
    delete _textTexture;
    this->_text = text;
    _textTexture = CreateTexture(this->_text, this->_f, this->_fontColor, this->_bgColor);
}

void eden_ec::TextComponent::ChangeColor(Uint8 fr = 255, Uint8 fg = 255, Uint8 fb = 255) {
    delete _textTexture;
    _fontColor.r = fr;
    _fontColor.g = fg;
    _fontColor.b = fb;
    _textTexture = CreateTexture(this->_text, this->_f, this->_fontColor, this->_bgColor);
}