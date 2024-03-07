#ifndef C_ANIMATOR_H
#define C_ANIMATOR_H

#include "Component.h"
#include <string>
#include <vector>

namespace eden_script {
	class ComponentArguments;
}

namespace render_wrapper {
	class Animator;
}

namespace eden_ec {

	class CMeshRenderer;
	class CAnimator : public Component
	{
	public:

		CAnimator() = default;

		virtual void Init(eden_script::ComponentArguments* args);
		virtual void InitComponent();
		virtual void Update(float t);
		static std::string GetID() { return _id; }

		void PlayAnim(std::string ID);
		void StopAnim();
		void OnAnimEnd();
		void SetOnAnimEnd(std::string animID, std::string endAnimID);
		std::string GetCurrentAnim();

	protected:
		const static std::string _id;

	private:
		render_wrapper::Animator* _animatorWrapper = nullptr;
		eden_ec::CMeshRenderer* _meshRend = nullptr;
		std::vector<std::string> _animNames;
		std::vector<std::string> _animMeshNames;
		std::vector<std::string> _nextAnim;
		std::vector<bool> _loopAnims;
	};
}

#endif // C_ANIMATOR_H