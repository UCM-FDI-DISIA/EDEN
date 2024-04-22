#define _CRTDBG_MAP_ALLOC
#ifndef HITO1_PRUEBA_H
#define HITO1_PRUEBA_H

#include "Component.h"

#include "defs.h"

namespace eden_input {
	class InputManager;
}

namespace eden_ec {
	class CTransform;
	class CAnimator;
	class CText;
	class CAudioEmitter;
	class CAudioListener;

	class EDEN_API Hito1Prueba : public Component {
	public:
		Hito1Prueba();
		~Hito1Prueba() = default;

		static std::string GetID() { return "PRUEBA"; }

		void Init(eden_script::ComponentArguments* args) override;

		/// @brief No usado
		void Awake() override {};

		void Start() override;

		void Update(float t) override;

		void HandleInput() override;
		void StartGame();

	private:

		eden_input::InputManager* inputManager;
		eden_ec::CTransform* transform;
		eden_ec::CAnimator* animator;
		eden_ec::CText* _text;
		eden_ec::CAudioEmitter* _audioEmitter;
		bool keyPressed = false;
		bool jump = false;
		bool idle = true;

		int _clicks = 0;
	};
}
#endif //HITO1_PRUEBA_H