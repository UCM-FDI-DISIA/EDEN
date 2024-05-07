#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_SOUNDWRAPPER_H
#define EDEN_SOUNDWRAPPER_H

#include <string>

#include "CAudioEmitter.h"
#include "AudioManager.h"

namespace irrklang {
    class ISound;
}

namespace eden_utils {
    class Vector3;
}

namespace audio_wrapper {
    class SoundClip;
    /// Clase que actuara de wrapper de los sonidos de Irrklang. Cada SoundWrapper representara
    /// un sonido distinto, que se generara en el AudioWrapper.
    class Sound {
        friend class eden_ec::CAudioEmitter;
        friend class eden_audio::AudioManager;
    public:
        /// Constructora por defecto del SoundWrapper
        /// @param file Ruta del archivo con el sonido
        Sound(SoundClip* clip);

        /// Destructora por defecto de la clase SoundWrapper
        ~Sound();
    private:
        // Clip de sonido con la fuente
        audio_wrapper::SoundClip* _clip = nullptr;

        /// Instancia del sonido de Irrklang para trackear datos sobre este
        irrklang::ISound* _sound = nullptr;

        /// Nombre del archivo asociado al sonido
        std::string _filename;

        /// Booleano que indica si el sonido es o no es tridimensional
        bool _threeDimensional;

        /// @brief Volumen sin haber sido multiplicado por el volumen general
        float _volumeWithoutGeneralMixing;

        /// @brief Volumen habiendose multiplicado por el volumen general
        float _volumeWithGeneralMixing;

        /// @brief Booleano que indica si el volumen del sonido está siendo afectado por el volumen general o no
        bool _isBeingMixed;

        /// Reproduce un sonido en un espacio 2D, sin coordenadas, por toda la escena o el espacio.
        /// @param loop Si el sonido se quiere reproducir en bucle se pondra en true, si no, en false (false por defecto)
        void Play(bool loop = false);

        /// Reproduce un sonido en un espacio 3D, esto es, necesita unas coordenadas desde donde se quiera
        /// reproducir, y necesitara de un listener en algun sitio para escucharlo
        /// @param position Posicion desde la que se reproducira el sonido
        /// @param loop Si el sonido se quiere reproducir en bucle se pondra en true, si no, en false (false por defecto)
        void Play(eden_utils::Vector3 position, bool loop = false);

        /// Pausa el sonido
        void Pause();

        /// Reanuda el sonido
        void Resume();

        /// Para la ejecucion del sonido
        void Stop();

        /// Reinicia el sonido desde el principio, tanto en 2D como en 3D de manera automatica
        void Restart();

        /// Devuelve si el sonido esta o no pausado
        /// @return Booleano que indica si el sonido esta o no pausado
        bool IsPaused() const;

        /// Devuelve si el sonido ha terminado o no
        /// @return Booleano que indica si el sonido ha terminado o no
        bool HasEnded() const;

        /// Establece si un sonido esta en bucle o no
        /// @param loop Booleano para establecer si el sonido se reproduce en bucle (true) o no (false)
        void SetLoop(bool loop);

        /// Devuelve si el sonido esta siendo reproducido en bucle o no
        /// @return Booleano que indica si el sonido esta siendo reproducido en bucle o no
        bool IsLooped() const;

        /// Establece el paneo (distrubicion por los altavoces izquierdo y derecho en un sistema estereo)
        /// @param pan Un float indicando el paneo. 1 es derecha, 0 es el centro (ambos altavoces) y -1 la izquierda.
        void SetPan(float pan);

        /// Devuelve la distribucion del paneo del sonido
        /// @return Float con la distribucion del paneo del sonido
        float GetPan() const;

        /// Establece la posicion desde donde se emite el sonido
        /// @param position Posicion desde donde se emite el sonido
        void SetPosition(eden_utils::Vector3 position);

        /// Devuelve la posicion desde donde se emite el sonido
        /// @return Vector con la posicion desde donde se emite el sonido
        eden_utils::Vector3 GetPlayingPosition() const;

        /// Cambia el volumen del sonido desde 0 (silencio) hasta 1 (volumen completo)
        /// @param volume Valor en punto flotante desde 0 hasta 1
        void SetVolume(float volume);

        /// Devuelve el volumen del sonido
        /// @return Valor en punto flotante con el volumen actual del sonido
        float GetVolume() const;

        /// @brief Multiplica los valores del volumen individual del sonido con el volumen general
        /// @param generalVolume Volumen general del motor
        void MixVolumeWithGeneralVolume(float generalVolume);

        /// @brief Devuelve el volumen individual del sonido mezclado con el volumen general
        /// @return Valor en punto flotante con la mezcla entre el volumen del sonido y el volumen general
        float GetMixedVolume() const;

        /// @brief Devuelve el volumen en crudo (sin ser afectado por el volumen general)
        /// @return Valor en punto flotante con la mezcla entre el volumen del sonido y el volumen general
        float GetRawVolume() const;

        /// @brief Cambia el valor de la velocidad de reproduccion del sonido (cambiando asi la frecuencia junto con el pitch (altura del sonido)). A mayor sea el valor, sonara el doble de rapido que sera
        /// mas agudo. A menor el valor, mas lento y mas grave. Valores solo entre algo mas que 0 (0 nunca reproduciria el sonido) e infinito, 1 por defecto.
        /// @param pitch Valor del pitch. 1 por defecto. 2 seria el doble de velocidad, mas agudo; 0.5 la mitad de velocidad, mas grave.
        void SetPitch(float pitch);

        /// @brief Devuelve el pitch del sonido
        /// @return Valor en punto flotante del pitch del sonido
        float GetPitch() const;

        /// @brief Devuelve el nombre del archivo de sonido
        /// @return String con el nombre del archivo de sonido
        std::string GetFilename() const;

        /// @brief Devuelve un booleano indicando si el sonido se ha creado (se ha reproducido anteriormente) o no
        /// @return booleano indicando si el sonido se ha creado (se ha reproducido anteriormente) o no
        bool HasBeingCreated() const;

    };
}

#endif //EDEN_SOUNDWRAPPER_H
