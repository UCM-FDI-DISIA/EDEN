#include <SDL.h>
#undef main

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Quit();

	return 0;
}