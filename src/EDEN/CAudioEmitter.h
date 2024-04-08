#ifndef EDEN_AUDIO_EMITTER
#define EDEN_AUDIO_EMITTER

#include <string>
#include <queue>

#include "Vector3.h"
#include "Component.h"


class CTransform;

namespace audio_wrapper {
	class SoundClip;
	class Sound;
}
namespace eden_ec {
	/// @brief Componente que se encargara de emitir audio tanto en 2D como en 3D y controlarlo. Para el audio en 3D es necesario que haya un listener
	/// en la misma escena.
	class CAudioEmitter : public eden_ec::Component {
	public:
		/// @brief Constructora por defecto del emisor de audio
		CAudioEmitter() = default;

		/// @brief Constructora por defecto del emisor de audio
		/// @param name Nombre del fichero de sonido
		/// @param is3D Si el sonido es o no es espacial/tridimensional
		CAudioEmitter(std::string name, bool is3D);

		/// @brief Destructora por defecto del emisor de audio
		~CAudioEmitter() override;

		/// @brief Construye el componente dado unos argumentos. Se obtendrán de una lectura de un .lua
		/// @param args Argumentos leídos de .lua
		void Init(eden_script::ComponentArguments* args) override;

		/// @brief Usaremos este método para añadir referencias de otros componentes
		void Start() override;

		/// @brief Metodo ejecutado cada frame
		/// @param t Tiempo transcurrido desde el ultimo frame
		void Update(float t) override;

		/// @brief Reproduce un sonido tanto en 2D como en 3D. La deteccion 2D/3D se hace automatica y desde la constructora del emisor de sonido,
		/// ya que no tiene mucho sentido poder cambiar un emisor de no espacial a espacial.
		void Play();

		/// @brief Pausa un sonido
		void Pause();

		/// @brief Reanuda un sonido
		void Resume();

		/// @brief Para completamente la emision de un sonido
		void Stop();

		/// @brief Reinicia la emision de un sonido
		void Restart();

		/// @brief Devuelve el clip de sonido que esta asociado a este emisor
		/// @return Puntero al clip de sonido asociado al emisor
		inline audio_wrapper::SoundClip* GetSoundClip() const { return _soundClip; }

		/// @brief Permite cambiar el clip de sonido del emisor
		/// @param name String con el nombre del archivo de sonido al que se desea cambiar
		void ChangeClip(std::string name);

		/// @brief Devuelve el sonido (que no clip) que tiene ahora mismo el emisor (puede estar reproduciendo, pausado, etc...)
		/// @return Puntero a un sonido
		audio_wrapper::Sound* GetSound() const;

		/// @brief Definición de método estático GetID necesario para construcción de componentes
		inline static std::string GetID() { return _id; }

	private:
		/// @brief Id del componente necesaria para la construccion de este
		const static std::string _id;

		/// @brief Clip de sonido asociado al emisor
		audio_wrapper::SoundClip* _soundClip;

		/// @brief Sonido asociado al emisor creado a partir del clip de sonido
		audio_wrapper::Sound* _sound;

		/// @brief Identifica si el sonido es espacial o no
		bool _3D;
		
		/// @brief Identifica si el sonido esta en bucle o no
		bool _loop;

		/// @brief Transform de la entidad sobre la que se engancha el listener
		eden_ec::CTransform* _transform;
	};
}

#endif