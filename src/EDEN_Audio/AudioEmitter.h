#ifndef EDEN_AUDIO_EMITTER
#define EDEN_AUDIO_EMITTER

#include <string>
#include <queue>

#include "Vector3.h"
#include "Component.h"

namespace audio_wrapper {
	class SoundClip;
	class Sound;
}

namespace eden_ec {
	class CTransform;
	class AudioEmitter : public Component {
	public:
		AudioEmitter(std::string name, bool is3D, eden_utils::Vector3 pos = { 0,0,0 }, eden_utils::Vector3 emittingDir = {0,0,0});
		~AudioEmitter() override;
		void Start() override;
		void Update(float t) override;
		void Play();
		void Pause();
		void Resume();
		void Stop();
		void Restart();
		inline audio_wrapper::SoundClip* GetSoundClip() const { return _soundClip; }
		void ChangeClip(std::string name);
		audio_wrapper::Sound* GetSound() const;

	private:
		const static std::string _id;
		audio_wrapper::SoundClip* _soundClip;
		audio_wrapper::Sound* _sound;
		bool _3D;
		bool _loop;
		eden_ec::CTransform* _transform;
	};
}

#endif