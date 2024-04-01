#ifndef EDEN_SOUNDCLIP_H
#define EDEN_SOUNDCLIP_H

#include <string>

namespace irrklang {
	class ISoundSource;
}

namespace audio_wrapper {
	class SoundClip {
	public:
		SoundClip(std::string filename);
		~SoundClip();
		inline std::string GetFilename() const { return _filename; }
		inline irrklang::ISoundSource* GetSource() const { return _soundSource; }
	private:
		// Fuente del sonido de irrklang
		irrklang::ISoundSource* _soundSource = nullptr;

		std::string _filename;
	};
}

#endif