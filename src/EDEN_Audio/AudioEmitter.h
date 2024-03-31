#ifndef EDEN_AUDIO_EMITTER
#define EDEN_AUDIO_EMITTER

#include <string>

#include "Vector3.h"

namespace eden_audio {
	class Sound;
	class AudioEmitter {
	public:
		AudioEmitter(std::string name, bool is3D, eden_utils::Vector3 pos = { 0,0,0 }, eden_utils::Vector3 emittingDir = {0,0,0});
		~AudioEmitter() = default;
		void Play();

	private:
		Sound* _soundClip;
		bool _3D;
		bool _loop;
		eden_utils::Vector3 _position;
		eden_utils::Vector3 _emittingDirection;
	};
}

#endif