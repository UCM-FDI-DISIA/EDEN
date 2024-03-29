#ifndef EDEN_AUDIOLISTENER_H
#define EDEN_AUDIOLISTENER_H

#include "Vector3.h"

namespace eden_audio {
    class AudioListener {
    public:
        AudioListener();
        ~AudioListener();
    private:
        eden_utils::Vector3 _listenerPosition;
    };
}



#endif //AUDIOLISTENER_H
