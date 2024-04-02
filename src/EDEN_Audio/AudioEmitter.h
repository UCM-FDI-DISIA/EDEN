#ifndef EDEN_AUDIO_EMITTER
#define EDEN_AUDIO_EMITTER

#include <string>
#include <queue>

#include "Vector3.h"

namespace audio_wrapper {
	class SoundClip;
	class Sound;
}

namespace eden_audio {
	class AudioEmitter {
	public:
		AudioEmitter(std::string name, bool is3D, eden_utils::Vector3 pos = { 0,0,0 }, eden_utils::Vector3 emittingDir = {0,0,0});
		~AudioEmitter() = default;
		void Play();
		inline audio_wrapper::SoundClip* GetSoundClip() const { return _soundClip; }
		void ChangeClip(std::string name);

	private:
		audio_wrapper::SoundClip* _soundClip;
		std::vector<audio_wrapper::Sound*> _sounds;
		bool _3D;
		bool _loop;
		eden_utils::Vector3 _position;
		eden_utils::Vector3 _emittingDirection;
	};
}

#endif