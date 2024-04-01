#ifndef EDEN_AUDIOMANAGER_H
#define EDEN_AUDIOMANAGER_H

#include <string>
#include <unordered_map>

#include "Singleton.h"

#ifdef _MSC_VER
#define AUDIO_ROUTE "assets\\audio\\"
#endif
#ifdef __APPLE__
#define AUDIO_ROUTE "assets/audio/"
#endif

namespace audio_wrapper {
    class SoundClip;
}

namespace eden_audio {
    class AudioManager : public Singleton<AudioManager> {
        friend Singleton<AudioManager>;
    public:
        AudioManager();
        ~AudioManager();
        audio_wrapper::SoundClip* GetSoundClip(std::string filename) const;
    private:
        void LoadResources();
        std::unordered_map<std::string, audio_wrapper::SoundClip*> _soundMap;
    };
}



#endif //AUDIOMANAGER_H
