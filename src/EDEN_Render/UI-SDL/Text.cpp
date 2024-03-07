#include "Text.h"
#include "Resources\checkML.h"
#include "Resources\SDLUtils.h"
#include "Entity.h"
#include "Resources\Font.h"

eden_ec::TextComponent::TextComponent(std::string text, Font& f, int fr, int fg, int fb,
    int br, int bg, int bb) : _text(text), _f(f){
    _x = 0;
    _y = 0;
    _fontColor.r = abs(fr % 255);
    _fontColor.g = abs(fg % 255);
    _fontColor.b = abs(fb % 255);
    _bgColor.r = abs(br % 255);
    _bgColor.g = abs(bg % 255);
    _bgColor.b = abs(bb % 255);
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

void eden_ec::TextComponent::ChangeColor(int fr, int fg, int fb) {
    delete _textTexture;
    _fontColor.r = abs(fr % 255);
    _fontColor.g = abs(fg % 255);
    _fontColor.b = abs(fb % 255);
    _textTexture = CreateTexture(this->_text, this->_f, this->_fontColor, this->_bgColor);
}