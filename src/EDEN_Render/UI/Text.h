#pragma once
#ifndef TEXT_H
#define TEXT_H
#include "Component.h"
#include "Resources\Texture.h"
#include <string>

class Font;
namespace eden_ec {

    /// @brief Componente de texto para la UI
    class TextComponent : public eden_ec::Component 
    {

    public:
        /// @brief Constructora
        /// @param text Texto
        /// @param f Font
        /// @param fontColor SDL_Color
        /// @param bgColor SDL_Color
        TextComponent(std::string text, Font& f, Uint8 fr=255 ,Uint8 fg = 255 , Uint8 fb = 255 ,
            Uint8 br = 255, Uint8 bg = 255, Uint8 bb = 255);

        /// @brief Destructora
        virtual ~TextComponent() { delete _textTexture; }

        /// @brief M�todo ejecutado cada frame
        /// @param t Tiempo transcurrido desde el �ltimo frame
        void Update(float t) override;

        /// @brief Renderizado del texto
        void Render();

        /// @brief Anchura del texto
        int GetWidth() const { return _textTexture->width(); }

        /// @brief Anchura del texto
        int GetHeight() const { return _textTexture->height(); }

        /// @brief Setear la posición del texto
        inline void SetPosition(Vector2D& v) { _x = v.getX(); _y = v.getY(); }

        /// @brief Posición del texto
        inline Vector2D GetPosition() const { return Vector2D(_x, _y); }

        /// @brief Cambiar texto
        /// @param text Nuevo texto
        void ChangeText(std::string text);

        /// @brief Cambiar color
        /// @param fontColor Nuevo color
        void ChangeColor(Uint8 fr = 255, Uint8 fg = 255, Uint8 fb = 255);
    private:
        Texture* _textTexture;
        int _x;
        int _y;
        Font& _f;
        SDL_Color _fontColor;
        SDL_Color _bgColor;
        std::string _text;

        Texture* CreateTexture(std::string text, Font& f, SDL_Color fontColor, SDL_Color bgColor);
    };
}

#endif 