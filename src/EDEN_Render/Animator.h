#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_ANIMATOR_H
#define EDEN_ANIMATOR_H

#include <unordered_map>
#include <string>
#include <utility>

namespace Ogre {
	class AnimationState;
}

namespace eden_error {
	class ErrorHandler;
}

namespace render_wrapper {

	class MeshRenderer;
	/// @brief La clase Animator forma parte del render_wrapper y se encarga de llamar a los métodos 
	/// específicos de Ogre para que el componente no tenga que interactuar con ellos. Usa un 
	/// unordered_map de strings (nombres de las animaciones) y pairs de AnimationStates de Ogre 
	/// (las animaciones como tal), y strings (nombres de las animaciones) que queremos que empiezen 
	/// cuando esa acabe). 
	class __declspec(dllexport) Animator
	{
	public:

		Animator(render_wrapper::MeshRenderer* meshRend);
		~Animator();

		/// @brief Desactiva la animacion actual
		void StopAnim();
		/// @brief Reproduce la animacion correspondiente
		/// @param ID Identificador de la animacion que se quiera reproducir
		void PlayAnim(std::string ID);
		/// @brief Se llama al acabar una animacion (que no este loopeando) y reproduce la
		/// animacion indicada en el mapa 
		void OnAnimEnd();
		/// @brief Guarda la animacion final de la animacion que le indiquemos
		/// @param animID Identificador de la animacion indicada
		/// @param endAnimID Identificador de la animacion final
		void SetOnAnimEnd(std::string animID, std::string endAnimID);
		/// @brief Llama al update de la animacion actual
		/// @param dt El tiempo transcurrido desde el ultimo frame
		void UpdateAnim(float dt);
		/// @brief Devuelve la animacion actual
		/// @return La animacion actual
		std::string GetCurrentAnim();
		/// @brief Permite registrar en el mapa las animaciones con sus IDs e indicando si Loopean o no
		/// @param ID Identificador de la animacion
		/// @param oldAnimName Nombre en Ogre del AnimationState
		/// @param endID Identificador de la animacion final
		/// @param isLooping Booleano que indica si la animacion correspondiente Loopea o no
		void RegisterAnim(std::string ID, std::string oldAnimName, std::string endID, bool isLooping);


	private:
		/// @brief Activa el loopeo de la animacion indicada
		/// @param ID Identificador de la animacion que se quiere loopear
		void LoopAnim(std::string ID);
		/// @brief Busca en el mapa el AnimationState de Ogre correspoindiente al ID indicado
		/// @param ID Identificador de la animacion de la cual necesitemos su AnimationState
		/// @return AnimationState de la animacion indicada
		Ogre::AnimationState* FindAnim(std::string ID);

		/// @brief Animacion actual
		Ogre::AnimationState* _currentAnim = nullptr;
		/// @brief Identificador de la animacion actual
		std::string _currentAnimID = " ";
		/// @brief Mapa de animaciones
		std::unordered_map<std::string, std::pair<Ogre::AnimationState*, std::string>> _anims;
		/// @brief Referencia al wrapper de MeshRenderer
		render_wrapper::MeshRenderer* _meshRend = nullptr;
	};
}

#endif // ANIMATOR_H
