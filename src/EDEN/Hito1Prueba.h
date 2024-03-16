#ifndef HITO1_PRUEBA_H
#define HITO1_PRUEBA_H

#include "Component.h"

namespace eden_input {
	class InputManager;
}

namespace eden_ec {
	class CTransform;
	class CAnimator;
	class Hito1Prueba : public Component {
	public:
		Hito1Prueba();
		~Hito1Prueba() = default;

		static std::string GetID() { return _id; }

		void Init(eden_script::ComponentArguments* args) override;

		void Start() override;

		void Update(float t) override;

		void HandleInput() override;

		void Jump();

	protected:
		const static std::string _id;
	private:

		eden_input::InputManager* inputManager;
		eden_ec::CTransform* transform;
		eden_ec::CAnimator* animator;
		bool keyPressed = false;
		bool jump = false;
		bool idle = true;
	};
}
#endif //HITO1_PRUEBA_H