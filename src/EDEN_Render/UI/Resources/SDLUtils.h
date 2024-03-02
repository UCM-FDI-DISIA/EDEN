// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>
#include <string>
#include <unordered_map>

#include "Singleton.h"
#include "Font.h"
//#include "Music.h"
//#include "SoundEffect.h"
#include "Texture.h"
#include "Vector2D.h"

struct Mapa {
	std::string route;
	int cols;
	std::string tileset;
	std::string background;
	std::string bgsong;

	Mapa(std::string r, int cols, std::string tileset, std::string background, std::string bgsong) : route(r), cols(cols), tileset(tileset), background(background), bgsong(bgsong) {}
};

class SDLUtils : public Singleton<SDLUtils> {

	friend Singleton<SDLUtils>; // needed to give access to private constructors

public:

	// we abstract away the actual data structure we use for
	// tables. All we assume is that is has the following
	// methods
	//
	//   emplace(key,value)
	//   at(key)
	//   clear()
	//
	template<typename T>
	using sdl_resource_table = std::unordered_map<std::string, T>;

	// just a wrapper for accessing a map, just to protect the table,
	// and to throw a meaning full exception when the key is not found
	// in the original map
	//
	template<typename T>
	class map_access_wrapper {
	public:
		sdl_resource_table<T>& map_;
		std::string desc_;
		map_access_wrapper(sdl_resource_table<T>& map, std::string desc) :
			map_(map), desc_(desc) {
		}

		inline auto& at(std::string key) {
			try {
				return map_.at(key);
			}
			catch (std::out_of_range& e) {
				throw "Key '" + key + "' does not exists in '" + //
					desc_ + "'";
			}
			catch (std::exception& e) {
				throw "Error when accessing key '" + key + "' of '" + //
					desc_ + "'. Original error was: " + e.what();
			}
		}
	};

	virtual ~SDLUtils();

	// cannot copy/move
	SDLUtils(SDLUtils&) = delete;
	SDLUtils(SDLUtils&&) = delete;
	SDLUtils& operator=(SDLUtils&) = delete;
	SDLUtils& operator=(SDLUtils&&) = delete;

	// access to the underlying SDL_Window -- in principle not needed
	inline SDL_Window* window() {
		return window_;
	}

	// access to the underlying SDL_Renderer -- needed when creating textures
	// other than those initialised in this class
	inline SDL_Renderer* renderer() {
		return renderer_;
	}

	// clear the renderer with a given SDL_Color
	inline void clearRenderer(SDL_Color bg = build_sdlcolor(0x000000FF)) {
		SDL_SetRenderDrawColor(renderer_, COLOREXP(bg));
		SDL_RenderClear(renderer_);
	}

	// present the current content of the renderer
	inline void presentRenderer() {
		SDL_RenderPresent(renderer_);
	}

	// the window's width
	inline int width() {
		return width_;
	}

	// the window's height
	inline int height() {
		return height_;
	}

	inline Vector2D getWindowDimensions() const {
		int w, h;
		SDL_GetRendererOutputSize(renderer_, &w, &h);
		return Vector2D(w, h);
	}

	// toggle to full-screen/window mode

	enum SCREEN_MODES { WINDOWED, FULL_DISPLAY, FULLSCREEN };

	inline void toggleFullScreen(SCREEN_MODES s) {
		auto flags = SDL_GetWindowFlags(window_);
		currentScreenMode_ = s;
		if (flags & SDL_WINDOW_FULLSCREEN && s == WINDOWED) {
			SDL_SetWindowFullscreen(window_, 0);
		}
		else if (s == FULL_DISPLAY) {
			SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		else if (s == FULLSCREEN) SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
	}

	inline SCREEN_MODES getCurrentScreenMode() const { return currentScreenMode_; }

	// show the cursor when mouse is over the window
	inline void showCursor() {
		SDL_ShowCursor(1);
	}

	// hide the cursor when mouse is over the window
	inline void hideCursor() {
		SDL_ShowCursor(0);
	}

	// All resource maps can be modified from outside, this way you can store
	// your own dynamically. Be careful when modifying them!

	// fonts map
	inline auto& fonts() {
		return fontsAccessWrapper_;
	}

	// images map
	inline auto& images() {
		return imagesAccessWrapper_;
	}

	// messages map
	inline auto& msgs() {
		return msgsAccessWrapper_;
	}

	inline auto& levels() {
		return levelsAccessWrapper_;
	}
	// Access to real time
	inline Uint32 currRealTime() const {
		return SDL_GetTicks();
	}

private:
	SDLUtils();
	SDLUtils(std::string windowTitle, int width, int height);
	SDLUtils(std::string windowTitle, int width, int height,
		std::string filename);

	void initWindow();
	void closeWindow();
	void initSDLExtensions(); // initialize resources (fonts, textures, audio, etc.)
	void closeSDLExtensions(); // free resources the

	std::string windowTitle_; // window title
	int width_; // window width
	int height_; // window height
	SCREEN_MODES currentScreenMode_;

	SDL_Window* window_; // the window
	SDL_Renderer* renderer_; // the renderer

	sdl_resource_table<Font> fonts_; // fonts map (string -> font)
	sdl_resource_table<Texture> images_; // textures map (string -> texture)
	sdl_resource_table<Texture> msgs_; // textures map (string -> texture)
	//sdl_resource_table<SoundEffect> sounds_; // sounds map (string -> sound)
	//sdl_resource_table<Music> musics_; // musics map (string -> music)
	sdl_resource_table<Mapa> levels_;

	map_access_wrapper<Font> fontsAccessWrapper_;
	map_access_wrapper<Texture> imagesAccessWrapper_;
	map_access_wrapper<Texture> msgsAccessWrapper_;
	//map_access_wrapper<SoundEffect> soundsAccessWrapper_;
	//map_access_wrapper<Music> musicsAccessWrapper_;
	map_access_wrapper<Mapa> levelsAccessWrapper_;
};

// This macro defines a compact way for using the singleton SDLUtils, instead of
// writing SDLUtils::instance()->method() we write sdlutils().method()
//
inline SDLUtils& sdlutils() {
	return *SDLUtils::Instance();
}