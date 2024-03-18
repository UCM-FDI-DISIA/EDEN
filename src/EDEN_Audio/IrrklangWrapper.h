#ifndef EDEN_IRRKLANGWRAPPER_H
#define EDEN_IRRKLANGWRAPPER_H

#include <string>

#include "Singleton.h"

namespace irrklang {
	class ISoundEngine;
	class ISoundSource;
}

namespace eden_utils {
	class Vector3;
}

namespace audio_wrapper {
	class IrrklangWrapper : public Singleton<IrrklangWrapper> {
		friend Singleton<IrrklangWrapper>;
	public:
		~IrrklangWrapper() override;

		irrklang::ISoundSource* CreateSoundSource(std::string file);

		irrklang::ISound* Play(irrklang::ISoundSource* soundSource, bool loop = false);

		irrklang::ISound* Play(irrklang::ISoundSource* soundSource, eden_utils::Vector3 position, bool loop = false);
	private:
		IrrklangWrapper();

		irrklang::ISoundEngine* _soundEngine = nullptr;
	};
}

#endif