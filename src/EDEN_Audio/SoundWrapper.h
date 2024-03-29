#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_SOUNDWRAPPER_H
#define EDEN_SOUNDWRAPPER_H

#include <string>

namespace irrklang {
    class ISoundSource;
    class ISound;
}

namespace eden_utils {
    class Vector3;
}

namespace eden_audio {
    class Sound;
}

namespace audio_wrapper {
    /// Clase que actuara de wrapper de los sonidos de Irrklang. Cada SoundWrapper representara
    /// un sonido distinto, que se generara en el AudioWrapper. Por elegancia, y en caso de que
    /// en algun momento se quiera cambiar de libreria de sonido, esta clase sirve para poder
    /// dejar intacta la clase Sound, que sera la que se comunicara con el manager de nuestro sistema
    /// de audio y el listener, aunque sea una clase un tanto innecesaria.
    class SoundWrapper {
    public:
        /// Constructora por defecto del SoundWrapper
        /// @param file Ruta del archivo con el sonido
        SoundWrapper(std::string file);

        /// Destructora por defecto de la clase SoundWrapper
        ~SoundWrapper();

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

        /// Devuelve si el sonido esta o no pausado
        /// @return Booleano que indica si el sonido esta o no pausado
        bool IsPaused() const;

        /// Para la ejecucion del sonido
        void Stop();

        /// Reinicia el sonido desde el principio, tanto en 2D como en 3D de manera automatica
        void Restart();

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
        void ChangeVolume(float volume);

        /// Devuelve el volumen del sonido
        /// @return Valor en punto flotante con el volumen actual del sonido
        float GetVolume() const;
    private:
        /// Ruta del archivo de sonido
        std::string _fileName;

        /// Fuente del sonido de Irrklang
        irrklang::ISoundSource* _soundSource = nullptr;

        /// Sonido de Irrklang para trackear datos sobre este
        irrklang::ISound* _sound = nullptr;

        /// Booleano que indica si el sonido es o no es tridimensional
        bool _threeDimensional;
    };
}

#endif //EDEN_SOUNDWRAPPER_H
