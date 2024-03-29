#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_AUDIOWRAPPER_H
#define EDEN_AUDIOWRAPPER_H

#include <string>

#include "Singleton.h"

namespace irrklang {
	class ISoundEngine;
	class ISoundSource;
	class ISound;
}

namespace eden_utils {
	class Vector3;
}

namespace audio_wrapper {
	/// Clase encargada de envolver el motor de sonido de Irrklang. La haremos singleton
	/// puesto que solo necesitamos un unico motor de sonido y no varios.
	/// El motor de sonido gestiona la creacion y reproduccion de sonidos desde archivos,
	/// tanto .wav, .ogg, .mp3 y varios mas.
	class AudioWrapper : public Singleton<AudioWrapper> {
		friend Singleton<AudioWrapper>;
	public:
		/// Destructora por defecto del wrapper del motor de sonido
		~AudioWrapper() override;

		/// Metodo para crear una fuente de sonido a partir de un archivo mp3, ogg o wav
		/// @param file Ruta del archivo
		/// @return Un puntero a una fuente de sonido propia de Irrklang
		irrklang::ISoundSource* CreateSoundSource(std::string file);

		/// Metodo para reproducir un sonido en un espacio bidimensional o en su defecto en toda
		/// una escena, esto es, que no va por coordenadas
		/// @param soundSource Fuente del sonido a reproducir
		/// @param loop Si el sonido se quiere reproducir en bucle se pondra en true, si no, en false (false por defecto)
		/// @return Un puntero a un sonido de Irrklang, el cual sirve para poder trackearlo en caso de que se necesite
		irrklang::ISound* Play(irrklang::ISoundSource* soundSource, bool loop = false);

		/// Metodo para reproducir un sonido en un espacio tridimensional, esto es, que necesita unas coordenadas
		/// donde se pueda reproducir
		/// @param soundSource Fuente del sonido a reproducir
		/// @param position Posicion desde donde se quiere emitir el sonido
		/// @param loop Si el sonido se quiere reproducir en bucle se pondra en true, si no, en false (false por defecto)
		/// @return Un puntero a un sonido de Irrklang, el cual sirve para poder trackearlo en caso de que se necesite
		irrklang::ISound* Play(irrklang::ISoundSource* soundSource, eden_utils::Vector3 position, bool loop = false);
	private:
		/// Constructora por defecto de la clase AudioWrapper. Privada ya que es un singleton.
		AudioWrapper();

		/// Puntero al motor de sonido de Irrklang desde el que se crearan todos los sonidos
		irrklang::ISoundEngine* _soundEngine = nullptr;
	};
}

#endif