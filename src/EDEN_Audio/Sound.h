#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_SOUND_H
#define EDEN_SOUND_H

#include <string>

namespace audio_wrapper {
	class SoundWrapper;
}

namespace eden_utils {
	class Vector3;
}

namespace eden_audio {
	/// Clase que representa un sonido y permite controlar todo lo que tenga que ver con este (reproduccion,
	/// pausa, consulta, etc...)
	class Sound {
	public:
		/// Constructora por defecto de la clase sonido
		/// @param file Ruta con el archivo del sonido
		Sound(std::string file);

		/// Destructora por defecto de la clase sonido
		~Sound();

		/// Reproduce un sonido en un espacio 2D, sin coordenadas, por toda la escena o el espacio.
		/// @param loop Si el sonido se quiere reproducir en bucle se pondra en true, si no, en false (false por defecto)
		void Play(bool loop);

		/// Reproduce un sonido en un espacio 3D, esto es, necesita unas coordenadas desde donde se quiera
		/// reproducir, y necesitara de un listener en algun sitio para escucharlo
		/// @param pos Posicion desde la que se reproducira el sonido
		/// @param loop Si el sonido se quiere reproducir en bucle se pondra en true, si no, en false (false por defecto)
		void Play(eden_utils::Vector3 pos, bool loop);

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
		/// Nombre del archivo del sonido (para manejo de errores)
		std::string _filename;

		/// Puntero al wrapper de sonido que sera el que tenga la informacion del sonido con
		/// una cierta libreria, en este caso, Irrklang
		audio_wrapper::SoundWrapper* _sound = nullptr;
	};
}
#endif

