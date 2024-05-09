#ifndef EDEN_EDEN_SCENE_H
#define EDEN_EDEN_SCENE_H

#include "Component.h"

namespace eden_ec {
	class CEDENScene : public Component {
	public:
		CEDENScene() = default;
		~CEDENScene() = default;

		void Init(eden_script::ComponentArguments* args) override {}

		void Awake() override {}

		void Start() override {}

		void Update(float dt) override;

		static std::string GetID() { return "CEDEN_SCENE_COMP"; }
	private:
		float _totalTime = 0.0f;

	};
}

#endif