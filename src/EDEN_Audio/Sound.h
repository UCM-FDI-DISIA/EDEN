#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_SOUND_H
#define EDEN_SOUND_H

#include <string>

namespace audio_wrapper {
	class SoundWrapper;
}

namespace eden_utils {
	class Vector3;
}

namespace eden_audio {
	class Sound
	{
	public:
		Sound(std::string file);
		~Sound();
		void Play(bool loop);
		void Play(eden_utils::Vector3 pos, bool loop);
	private:
		audio_wrapper::SoundWrapper* _sound = nullptr;
	};
}
#endif

