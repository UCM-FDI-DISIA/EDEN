#ifndef EDEN_AUDIOMANAGER_H
#define EDEN_AUDIOMANAGER_H

#include <string>
#include <unordered_map>

#include "Singleton.h"

namespace audio_wrapper {
    class SoundClip;
}

namespace eden_audio {
    /// @brief Clase que se encargara del manejo de los recursos de sonido del motor y permite obtener clips de sonido
    class AudioManager : public Singleton<AudioManager> {
        friend Singleton<AudioManager>;
    public:
        /// @brief Constructora por defecto del manager de audio
        AudioManager();

        /// @brief Destructora por defecto del manager de audio
        ~AudioManager();

        /// @brief Devuelve un clip de sonido a partir del nombre del archivo de sonido
        /// @param filename Nombre del archivo de sonido del cual se quiere obtener un clip de sonido
        /// @return Puntero a un clip de sonido
        audio_wrapper::SoundClip* GetSoundClip(std::string filename) const;
    private:
        /// @brief Mapa que almacena los clips de sonido con un identificador, que es el nombre de su archivo
        std::unordered_map<std::string, audio_wrapper::SoundClip*> _soundMap;

        /// @brief Carga todos los recursos de sonido
        void LoadResources();

    };
}



#endif //AUDIOMANAGER_H
