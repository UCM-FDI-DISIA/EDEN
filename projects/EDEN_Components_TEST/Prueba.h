#ifndef PRUEBA_H
#define PRUEBA_H

#include "Component.h"


namespace eden_input {
	class InputManager;
}

namespace eden_ec {
	class CTransform;
	class CPrueba : public Component {
	public:
		CPrueba() = default;
		~CPrueba() = default;

		void InitComponent() override;

		static std::string GetID() { return _id; }

		void Init(eden_script::ComponentArguments* args) override {};

		void Update(float t) override;

		void HandleInput() override;

	protected:
		const static std::string _id;
		eden_input::InputManager* inputManager;
		eden_ec::CTransform* transform;
		bool keyPressed = false;
	};
}
#endif //PRUEBA_H