#ifndef AUDIOWRAPPER_H
#define AUDIOWRAPPER_H

namespace irrklang {
    class ISoundEngine;
    class ISoundSource;
    class ISound;
}

namespace audio_wrapper {
    class AudioWrapper {
    public:
        AudioWrapper();
        ~AudioWrapper();
    private:
        irrklang::ISoundEngine* _soundEngine = nullptr;
    };
}



#endif //AUDIOWRAPPER_H
