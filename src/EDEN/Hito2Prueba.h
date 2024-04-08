#define _CRTDBG_MAP_ALLOC
#ifndef HITO2_PRUEBA_H
#define HITO2_PRUEBA_H

#include "Component.h"

namespace eden_ec {
	class CAudioEmitter;
	class Hito2Prueba : public Component {
	public:
		Hito2Prueba() = default;
		~Hito2Prueba() = default;

		static std::string GetID() { return _id; }

		void Init(eden_script::ComponentArguments* args) override {};

		void Start() override;

	protected:
		const static std::string _id;
	private:
		eden_ec::CAudioEmitter* _audioEmitter;
	};
}
#endif //HITO2_PRUEBA_H