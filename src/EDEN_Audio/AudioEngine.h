#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_AUDIOENGINE_H
#define EDEN_AUDIOENGINE_H

#include <string>

#include "Singleton.h"
#include "Vector3.h"

namespace irrklang {
	class ISoundEngine;
	class ISoundSource;
	class ISound;
	template <class T> class vec3d;
	typedef float ik_f32;
	typedef vec3d<ik_f32> vec3df;
}

namespace audio_wrapper {
	/// Clase encargada de envolver el motor de sonido de Irrklang. La haremos singleton
	/// puesto que solo necesitamos un unico motor de sonido y no varios.
	/// El motor de sonido gestiona la creacion y reproduccion de sonidos desde archivos,
	/// tanto .wav, .ogg, .mp3 y varios mas.
	class AudioEngine : public Singleton<AudioEngine> {
		friend Singleton<AudioEngine>;
	public:
		/// Destructora por defecto del wrapper del motor de sonido
		~AudioEngine() override;

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

		/// @brief Metodo para establecer la posicion, direccion, velocidad (si la hubiese (es para producir un efecto Doppler)) y la normal (para que Irrklang sepa cual es la izq. y la dcha.) del listener
		/// @param position Vector con la posicion del listener
		/// @param hearingDir Direccion desde la que el listener escuchara sonidos
		/// @param movingSpeed Velocidad a la que se mueve el listener (solo para efecto Doppler), por defecto {0,0,0}
		/// @param normal La normal del listener, por defecto {0,1,0}
		void SetListenerParameters(eden_utils::Vector3 position, eden_utils::Vector3 hearingDir, eden_utils::Vector3 movingSpeed = { 0,0,0 }, eden_utils::Vector3 normal = { 0,1,0 });

		/// @brief Transforma un vector propio de Irrklang a un vector de EDEN
		/// @param vector Vector de Irrklang
		/// @return Vector de EDEN
		static eden_utils::Vector3 IrrklangVecToEdenVec(irrklang::vec3df vector);

		/// @brief Transforma un vector propio de EDEN en uno de Irrklang
		/// @param vector Vector de EDEN
		/// @return Vector de Irrklang
		static irrklang::vec3df EdenVecToIrrklangVec(eden_utils::Vector3 vector);
	private:
		/// Constructora por defecto de la clase AudioWrapper. Privada ya que es un singleton.
		AudioEngine();

		/// Puntero al motor de sonido de Irrklang desde el que se crearan todos los sonidos
		irrklang::ISoundEngine* _soundEngine = nullptr;
	};
}

#endif