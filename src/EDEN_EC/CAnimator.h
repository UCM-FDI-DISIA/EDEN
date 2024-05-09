#ifndef EDEN_C_ANIMATOR_H
#define EDEN_C_ANIMATOR_H

#include <string>
#include <vector>

#include "Component.h"

#include "defs.h"

namespace eden_script {
	class ComponentArguments;
}

namespace render_wrapper {
	class Animator;
}

namespace eden_ec {

	class CMeshRenderer;
	/// @brief El coponente CAnimator se encarga de manejar las animaciones, ademas de crear
	/// e inicializar el Animator Wrapper y llamar a sus metodos
	class CAnimator : public Component
	{
	public:

		EDEN_API CAnimator() = default;
		EDEN_API ~CAnimator() override;

		/// @brief Inicializa el componente, guardando los argumentos recibidos desde lua
		/// @param args los argumentos que contienen informacion sobre las animaciones
		EDEN_API void Init(eden_script::ComponentArguments* args) override;
		/// @brief Actualiza las animaciones
		/// @param dt El tiempo transcurrido desde el ultimo frame
		EDEN_API void Update(float dt) override;

		/// @brief Se usa para guardar la referencia al CMeshRenderer y registrar las animaciones
		EDEN_API void Awake() override;

		/// @brief No usado
		EDEN_API void Start() override {};
		/// @brief Devuelve el identificador del componente
		/// @return Identificador del componente
		EDEN_API static std::string GetID() { return "ANIMATOR"; }

		/// @brief Permite reproducir una animacion
		/// @param ID Identificador de la animacion que se quiera reproducir
		EDEN_API void PlayAnim(std::string ID);
		/// @brief Detiene la animacion que se estuviera reproduciendo
		EDEN_API void StopAnim();
		/// @brief Se llama al acabar una animacion y reproduce la animacion que se haya indicado en 
		/// los argumentos
		EDEN_API void OnAnimEnd();
		/// @brief Permite guardar la animacion que queremos que se reproduzca cuando otra acabe
		/// @param animID La animacion indicada
		/// @param endAnimID La animacion final
		EDEN_API void SetOnAnimEnd(std::string animID, std::string endAnimID);
		/// @brief Devuelve la animacion que se este reproduciendo actualmente
		/// @return Identificador de la animacion actual
		EDEN_API std::string GetCurrentAnim();
		/// @brief Permite saber si ha acabado la animacion
		/// @param animID Identificador de la animacion indicada 
		/// @return bool que indica si la animacion actual se esta reproduciendo o ha acabado
		EDEN_API bool IsPlaying(std::string animID);

	private:
		/// @brief Inicializa el Wrapper de animaciones y el CMeshRenderer si por alguna 
		/// razón este método fuera llamado antes que el de CMeshRenderer (ya que depende de él)
		void InitializeWrapper();

		/// @brief Referencia al Animator Wrapper
		render_wrapper::Animator* _animatorWrapper = nullptr;
		/// @brief Referencia al componente CMeshRenderer
		eden_ec::CMeshRenderer* _meshRend = nullptr;

		/// @brief Vectores donde se guardam desde los argumentos la informacion de las animaciones
		std::vector<std::string> _animNames;
		std::vector<std::string> _animMeshNames;
		std::vector<std::string> _nextAnim;
		std::vector<bool> _loopAnims;
	};
}

#endif // C_ANIMATOR_H