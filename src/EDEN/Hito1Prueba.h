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
		Hito1Prueba() = default;
		~Hito1Prueba() = default;

		void InitComponent() override;

		static std::string GetID() { return _id; }

		void Init(eden_script::ComponentArguments* args) override {};

		void Update(float t) override;

		void HandleInput() override;

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