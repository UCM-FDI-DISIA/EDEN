#ifndef EDEN_AUDIO_EMITTER
#define EDEN_AUDIO_EMITTER

#include <string>
#include <queue>

#include "Vector3.h"
#include "Component.h"
#include "AudioManager.h"

#include "defs.h"

namespace audio_wrapper {
	class SoundClip;
	class Sound;
}

namespace eden_ec {
	class CTransform;
	/// @brief Componente que se encargara de emitir audio tanto en 2D como en 3D y controlarlo. Para el audio en 3D es necesario que haya un listener
	/// en la misma escena.
	class EDEN_API CAudioEmitter : public eden_ec::Component {
		friend class eden_audio::AudioManager;
	public:
		/// @brief Constructora por defecto del emisor de audio
		CAudioEmitter() = default;


		/// @brief Constructora por defecto del emisor de audio
		/// @param name Nombre del fichero de sonido
		/// @param is3D Si el sonido es o no es espacial/tridimensional
		CAudioEmitter(std::string name, bool is3D);

		/// @brief Destructora por defecto del emisor de audio
		~CAudioEmitter() override;

		/// @brief Construye el componente dado unos argumentos. Se obtendr�n de una lectura de un .lua
		/// @param args Argumentos le�dos de .lua
		void Init(eden_script::ComponentArguments* args) override;

		/// @brief No usado
		void Awake() override {};

		/// @brief Usaremos este m�todo para a�adir referencias de otros componentes
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

		/// @brief Permite cambiar el clip de sonido del emisor
		/// @param name String con el nombre del archivo de sonido al que se desea cambiar
		void ChangeClip(std::string name);

		/// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
		inline static std::string GetID() { return "AUDIO_EMITTER"; }

	private:

		/// @brief Enumerado que representa el estado de un sonido
		enum class SoundState : uint8_t {
			PLAYING,
			PAUSED,
			STOPPED
		};

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

		/// @brief Estado actual del sonido, por defecto parado
		SoundState _currentState = SoundState::STOPPED;

		/// @brief Estado anterior del sonido, por defecto parado
		SoundState _previousState = SoundState::STOPPED;

		/// @brief Devuelve el clip de sonido que esta asociado a este emisor
		/// @return Puntero al clip de sonido asociado al emisor
		inline audio_wrapper::SoundClip* GetSoundClip() const { return _soundClip; }

		/// @brief Devuelve el sonido (que no clip) que tiene ahora mismo el emisor (puede estar reproduciendo, pausado, etc...)
		/// @return Puntero a un sonido
		audio_wrapper::Sound* GetSound() const;

		/// @brief Devuelve el estado actual de sonido
		/// @return Estado actual de sonido
		inline SoundState GetCurrentState() const { return _currentState; }

		/// @brief Devuelve el estado anterior de sonido
		/// @return Estado anterior de sonido
		inline SoundState GetPreviousState() const { return _previousState; }
	};
}

#endif