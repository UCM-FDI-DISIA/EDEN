#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_SOUNDWRAPPER_H
#define EDEN_SOUNDWRAPPER_H

#include <string>

namespace irrklang {
    class ISoundSource;
    class ISound;
}

namespace eden_audio {
    class Sound;
}

namespace eden_utils {
    class Vector3;
}

namespace audio_wrapper {
    class SoundWrapper {
    public:
        SoundWrapper(std::string file);
        ~SoundWrapper();
        void Play(bool loop = false);
        void Play(eden_utils::Vector3 position, bool loop = false);
        void ChangeVolume(float volume);
        float GetVolume() const;
    private:
        std::string _fileName;
        irrklang::ISoundSource* _soundSource = nullptr;
        irrklang::ISound* _sound = nullptr;
    };
}

#endif //EDEN_SOUNDWRAPPER_H
