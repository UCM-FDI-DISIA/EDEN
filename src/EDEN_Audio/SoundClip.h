#ifndef EDEN_SOUNDCLIP_H
#define EDEN_SOUNDCLIP_H

#include <string>

namespace irrklang {
	class ISoundSource;
}

namespace audio_wrapper {
	/// @brief Clase que proporciona una abstraccion a las fuentes de sonido de Irrklang como un "clip" de sonido, al estilo de Unity.
	/// El clip solo contendra informacion acerca de la fuente y del nombre del archivo del que proviene.
	class SoundClip {
	public:
		/// @brief Constructora por defecto del clip de sonido
		/// @param filename Nombre del archivo (incluido el .mp3, .wav, .ogg, lo que sea) de sonido
		SoundClip(std::string filename);

		/// @brief Destructora por defecto de la clase SoundClip
		~SoundClip();

		/// @brief Devuelve el nombre del fichero de sonido de un clip de sonido
		/// @return String con el nombre del fichero de sonido
		inline std::string GetFilename() const { return _filename; }

		/// @brief Devuelve la fuente de irrklang del clip de sonido
		/// @return Puntero a una fuente de sonido
		inline irrklang::ISoundSource* GetSource() const { return _soundSource; }
	private:
		// Fuente del sonido de irrklang
		irrklang::ISoundSource* _soundSource = nullptr;

		/// @brief Nombre del archivo de sonido
		std::string _filename = " ";
	};
}

#endif