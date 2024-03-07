#include <fmod_errors.h>
#include <fmod.hpp>


int main() {
	FMOD::System* system;
	FMOD_RESULT result = FMOD::System_Create(&system);
	result = system->init(100, FMOD_3D, 0);
	result = system->close();
	delete system;
	return 0;
}