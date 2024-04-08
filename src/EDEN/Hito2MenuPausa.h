#define _CRTDBG_MAP_ALLOC
#ifndef HITO2_MENU_PAUSA_H
#define HITO2_MENU_PAUSA_H

#include "Component.h"

namespace eden_input {
	class InputManager;
}

namespace eden_ec {
	class CTransform;
	class CAnimator;
	class CText;
	class CAudioEmitter;
	class CAudioListener;
	class Hito2MenuPausa : public Component {
	public:
		Hito2MenuPausa();
		~Hito2MenuPausa() = default;

		static std::string GetID() { return _id; }

		void Init(eden_script::ComponentArguments* args) override;

		void Start() override;

		void Update(float t) override;

		void HandleInput() override;

		void ResumeGame();

		void ExitGame();

		void BackToMenu();

	protected:
		const static std::string _id;
	private:

		eden_input::InputManager* inputManager;
	};
}
#endif //HITO2_MENU_PAUSA_H