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

        /// @brief Anade una entidad a su escena de sonido para poder llevar control de ella en los cambios de escenas
        /// @param e Entidad con un componente AudioEmitter
        void AddAudioEntity(eden_ec::Entity* e);

        /// @brief Elimina una entidad de su escena de sonido
        /// @param e Entidad con un componente AudioEmitter
        void RemoveAudioEntity(eden_ec::Entity* e);

    private:
        /// @brief Mapa que almacena los clips de sonido con un identificador, que es el nombre de su archivo
        std::unordered_map<std::string, audio_wrapper::SoundClip*> _soundMap;

        /// @brief Mapa que almacena la informacion de todas las escenas de sonido con un identificador, que es su ID de escena
        std::unordered_map <std::string, InfoAudioWorld*> _audioScenes;

        /// @brief Escena actual de sonido
        InfoAudioWorld* _currentAudioScene = nullptr;

        /// @brief Carga todos los recursos de sonido
        void LoadResources();

        /// @brief Crea una escena de sonido dado su identificador
        /// @param id Identificador de la escena
        void CreateAudioScene(std::string id);

        /// @brief Sustituye una escena de sonido por otra, eliminando la vieja
        /// @param old_id Identificador de la escena antigua
        /// @param new_id Identificador de la escena nueva
        void RemoveAudioScene(std::string old_id, std::string new_id);
    };

    /// @brief Clase que representa un mundo/escena de sonido y tiene referencia a todas las entidades que reproducen sonido en una determinada escena
    /// @brief de juego
    class InfoAudioWorld {
        friend AudioManager;
    private:
        /// @brief Constructora por defecto
        InfoAudioWorld() = default;

        /// @brief Destructora por defecto
        ~InfoAudioWorld() = default;

        /// @brief Conjunto que contiene todas las entidades con un componente de emision de sonido
        std::unordered_set<eden_ec::Entity*> _entities;
    };
}



#endif //AUDIOMANAGER_H
