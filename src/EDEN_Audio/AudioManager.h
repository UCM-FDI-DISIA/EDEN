#ifndef EDEN_AUDIOMANAGER_H
#define EDEN_AUDIOMANAGER_H

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Singleton.h"

namespace audio_wrapper {
    class SoundClip;
}

namespace eden_ec {
    class Entity;
}

namespace eden {
    class Scene;
    class SceneManager;
}

namespace eden_audio {
    /// @brief Clase que se encargara del manejo de los recursos de sonido del motor y permite obtener clips de sonido
    class InfoAudioWorld;
    class AudioManager : public Singleton<AudioManager> {
        friend Singleton<AudioManager>;
        friend eden::Scene;
        friend eden::SceneManager;
    public:
        /// @brief Constructora por defecto del manager de audio
        AudioManager();

        /// @brief Destructora por defecto del manager de audio
        ~AudioManager();

        /// @brief Devuelve un clip de sonido a partir del nombre del archivo de sonido
        /// @param filename Nombre del archivo de sonido del cual se quiere obtener un clip de sonido
        /// @return Puntero a un clip de sonido
        audio_wrapper::SoundClip* GetSoundClip(std::string filename) const;

        void AddAudioEntity(eden_ec::Entity* e);

        void RemoveAudioEntity(eden_ec::Entity* e);

    private:
        /// @brief Mapa que almacena los clips de sonido con un identificador, que es el nombre de su archivo
        std::unordered_map<std::string, audio_wrapper::SoundClip*> _soundMap;

        std::unordered_map <std::string, InfoAudioWorld*> _audioScenes;

        /// @brief Carga todos los recursos de sonido
        void LoadResources();

        void CreateAudioScene(std::string id);

        void RemoveAudioScene(std::string old_id, std::string new_id);
    };

    class InfoAudioWorld {
        friend AudioManager;
    public:
        InfoAudioWorld();
        ~InfoAudioWorld();
    private:
        std::unordered_set<eden_ec::Entity*> _entities;
    };
}



#endif //AUDIOMANAGER_H
