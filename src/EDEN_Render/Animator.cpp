#include <iostream>

#include <OgreAnimationState.h>
#include <OgreEntity.h>

#include "Animator.h"
#include <ErrorHandler.h>
#include "MeshRenderer.h"

render_wrapper::Animator::Animator(render_wrapper::MeshRenderer* meshRend) {
	_meshRend = meshRend;

	_anims = std::unordered_map<std::string, std::pair<Ogre::AnimationState*, std::string>>();
}

render_wrapper::Animator::~Animator() {
	for (auto it = _anims.begin(); it != _anims.end(); ++it) {
		delete (*it).second.first;
	}
}

void render_wrapper::Animator::StopAnim() {
	_currentAnim->setEnabled(false);
	_currentAnim->setTimePosition(0);
}

void render_wrapper::Animator::PlayAnim(std::string ID) {
	if(_currentAnim != nullptr) StopAnim();
	_currentAnim = FindAnim(ID);
	_currentAnim->setEnabled(true);
	_currentAnimID = ID;
}

void render_wrapper::Animator::LoopAnim(std::string ID) {
	FindAnim(ID)->setLoop(true);
}

void render_wrapper::Animator::OnAnimEnd() {
	PlayAnim(_anims.at(_currentAnimID).second);
	
}

void render_wrapper::Animator::SetOnAnimEnd(std::string animID, std::string endAnimID) {
	_anims.at(animID).second = endAnimID;
}

void render_wrapper::Animator::UpdateAnim(float dt) {
	_currentAnim->addTime(dt);
	if (_currentAnim->hasEnded() && _currentAnim) OnAnimEnd();
}

std::string render_wrapper::Animator::GetCurrentAnim() {
	return _currentAnimID;
}

Ogre::AnimationState* render_wrapper::Animator::FindAnim(std::string ID) {
	std::unordered_map<std::string, std::pair<Ogre::AnimationState*, std::string>>::iterator anim = _anims.find(ID);
	if (anim == _anims.end()) { 
		std::string exceptionMsg = "render_wrapper::Animator ERROR in line 44: animation with ID " + ID + " not found in _anims map";
		EDEN_EXCEPTION(exceptionMsg.c_str());
		return nullptr; 
	}
	else return anim->second.first;
}

void  render_wrapper::Animator::RegisterAnim(std::string ID, std::string oldAnimID, std::string endID, bool isLooping) {
	auto anim = _meshRend->_ent->getAnimationState(oldAnimID);
	anim->setLoop(isLooping);
	_anims.insert({ ID, {anim, endID} });
}
