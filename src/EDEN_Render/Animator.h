#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <unordered_map>
#include <string>
#include <utility>

namespace Ogre {
	class AnimationState;
}

namespace render_wrapper {

	class MeshRenderer;
	class Animator
	{
	public:

		Animator(render_wrapper::MeshRenderer* meshRend);
		~Animator();

		void StopAnim();
		void PlayAnim(std::string ID);
		void OnAnimEnd();
		void SetOnAnimEnd(std::string animID, std::string endAnimID);
		void UpdateAnim(float t);
		std::string GetCurrentAnim();
		void RegisterAnim(std::string ID, std::string oldAnimName, std::string endID, bool isLooping);


	private:
		void LoopAnim(std::string ID);
		Ogre::AnimationState* FindAnim(std::string ID);

		Ogre::AnimationState* _currentAnim;
		std::string _currentAnimID;
		std::unordered_map<std::string, std::pair<Ogre::AnimationState*, std::string>> _anims;

		render_wrapper::MeshRenderer* _meshRend;
	};
}

#endif // ANIMATOR_H
