#define _CRTDBG_MAP_ALLOC

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
	class __declspec(dllexport) CAnimator : public Component
	{
	public:

		CAnimator() = default;
		~CAnimator() override;

		/// @brief Inicializa el componente, guardando los argumentos recibidos desde lua
		/// @param args los argumentos que contienen informacion sobre las animaciones
		void Init(eden_script::ComponentArguments* args) override;
		/// @brief Actualiza las animaciones
		/// @param dt El tiempo transcurrido desde el ultimo frame
		void Update(float dt) override;
		/// @brief Se usa para guardar la referencia al CMeshRenderer y registrar las animaciones
		void Start() override;
		/// @brief Devuelve el identificador del componente
		/// @return Identificador del componente
		static std::string GetID() { return "ANIMATOR"; }

		/// @brief Permite reproducir una animacion
		/// @param ID Identificador de la animacion que se quiera reproducir
		void PlayAnim(std::string ID);
		/// @brief Detiene la animacion que se estuviera reproduciendo
		void StopAnim();
		/// @brief Se llama al acabar una animacion y reproduce la animacion que se haya indicado en 
		/// los argumentos
		void OnAnimEnd();
		/// @brief Permite guardar la animacion que queremos que se reproduzca cuando otra acabe
		/// @param animID La animacion indicada
		/// @param endAnimID La animacion final
		void SetOnAnimEnd(std::string animID, std::string endAnimID);
		/// @brief Devuelve la animacion que se este reproduciendo actualmente
		/// @return Identificador de la animacion actual
		std::string GetCurrentAnim();

	private:
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