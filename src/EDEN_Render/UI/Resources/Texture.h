// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>
#include "SDL_image.h"
#include <string>
#include <cassert>
#include <iostream>

#include "Font.h"

using uint = unsigned int;

class Texture {

private:

	// Construct from text
	void constructFromText(SDL_Renderer* renderer, const std::string& text,
		const Font& font, const SDL_Color* fgColor,
		const SDL_Color* bgColor = nullptr);

	void load(std::string filename, uint32_t numRows = 1, uint32_t numCols = 1);

	SDL_Texture* texture_;
	SDL_Renderer* renderer_;
	uint width_;
	uint height_;
	uint fw=0; ///< Anchura del frame de la textura
	uint fh=0; ///< Altura del frame de la textura
	uint numCols = 1; ///< Número de columnas de la textura
	uint numRows = 1; ///< Número de filas de la textura

public:

	// cannot copy textures
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	// can be moved
	Texture& operator=(Texture&& other) noexcept;
	Texture(Texture&& other) noexcept;

	// Construct from image
	Texture(SDL_Renderer* renderer, const std::string& fileName);

	//Constructor from framedImage
	Texture(SDL_Renderer* r, std::string filename, uint32_t numRows, uint32_t numCols) : renderer_(r)
	{
		load(filename, numRows, numCols);
		std::cout << "textura leida " << fw << " " << fh << std::endl;
	};

	// Construct from text
	Texture(SDL_Renderer* renderer, const std::string& text, const Font& font,
		const SDL_Color& fgColor);

	// Construct from text with background
	Texture(SDL_Renderer* renderer, const std::string& text, const Font& font,
		const SDL_Color& fgColor, const SDL_Color& bgColor);

	void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

	virtual ~Texture() {
		if (texture_ != nullptr)
			SDL_DestroyTexture(texture_); // delete the SDL texture
	}

	inline int width() const {
		return width_;
	}

	inline int height() const {
		return height_;
	}

	// This rendering method corresponds to method SDL_RenderCopyEx.
	//
	// Renders part of the texture (src) to a destination rectangle (dest)
	// with a rotation (angle) around point p (of dest), and flips
	// according to the value of flip. If 'p'is nullptr, the rotation is done
	// wrt. the center
	//
	inline void render(const SDL_Rect& src, const SDL_Rect& dest, double angle,
		const SDL_Point* p = nullptr,
		SDL_RendererFlip flip = SDL_FLIP_NONE) {
		assert(texture_ != nullptr);
		SDL_RenderCopyEx(renderer_, texture_, &src, &dest, angle, p, flip);
	}

	// This rendering method corresponds to method SDL_RenderCopy.
	//
	// Renders part of the texture (src) to a destination rectangle (dest).
	// It can be implemented by calling the previous render method as well,
	// but we use SDL_RenderCopy directly since it does less checks so it
	// saves some checks ...
	inline void render(const SDL_Rect& src, const SDL_Rect& dest) {
		assert(texture_ != nullptr);
		SDL_RenderCopy(renderer_, texture_, &src, &dest);
	}

	// render the complete texture at position (x,y).
	inline void render(int x, int y) {
		SDL_Rect dest = { x, y, (int)width_, (int)height_ };
		render(dest);
	}

	// renders the complete texture at a destination rectangle (dest)
	inline void render(const SDL_Rect& dest, int angle = 0) {
		SDL_Rect src = { 0, 0, (int)width_, (int)height_ };
		render(src, dest, angle);
	}

	// renders the complete texture at a destination rectangle (dest),
	// with rotation
	inline void render(const SDL_Rect& dest, float rotation) {
		SDL_Rect src = { 0, 0, (int)width_, (int)height_ };
		render(src, dest, rotation);
	}

	/// Devuelve el número de columnas en que se divide la textura
	/// \return Entero con el número de columnas en que se divide la textura
	int getNumCols() const { return numCols; };

	/// Devuelve el número de filas en que se divide la textura
	/// \return Entero con el número de filas en que se divide la textura
	int getNumRows() const { return numRows; };

	inline int getFrameWidth() const { return fw; };
	inline int getFrameHeight() const { return fh; };

	inline void setColor(const SDL_Color& c) { SDL_SetTextureColorMod(texture_, c.r, c.g, c.b); }
	inline void setAlpha(int alpha) { SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND); SDL_SetTextureAlphaMod(texture_, alpha); }

};