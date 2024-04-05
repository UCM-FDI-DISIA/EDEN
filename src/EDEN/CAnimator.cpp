#define _CRTDBG_MAP_ALLOC
#include "CAnimator.h"
#include <ScriptManager.h>
#include <ComponentArguments.h>
#include <Animator.h>
#include "CMeshRenderer.h"
#include "Entity.h"
#include <RenderManager.h>

const std::string eden_ec::CAnimator::_id = "ANIMATOR";

eden_ec::CAnimator::~CAnimator() {
	eden_render::RenderManager::Instance()->removeRenderEntity(_ent);
	delete _animatorWrapper;
	//_animatorWrapper = nullptr;
}

void eden_ec::CAnimator::Init(eden_script::ComponentArguments* args) {
	_animNames = args->GetValueToStringVector("AnimNames");
	_animMeshNames = args->GetValueToStringVector("AnimMeshNames");
	_nextAnim = args->GetValueToStringVector("NextAnim");
	_loopAnims = args->GetValueToBoolVector("LoopAnims");
	eden_render::RenderManager::Instance()->addRenderEntity(_ent);
}

void eden_ec::CAnimator::Start() {
	_meshRend = _ent->GetComponent<CMeshRenderer>();
	_animatorWrapper = new render_wrapper::Animator(_meshRend->_renderWrapper);

	for (int i = 0; i < _animNames.size(); ++i) {
		_animatorWrapper->RegisterAnim(_animNames[i], _animMeshNames[i], _nextAnim[i], _loopAnims[i]);
	}
}

void eden_ec::CAnimator::Update(float dt) {
	_animatorWrapper->UpdateAnim(dt);
}

void eden_ec::CAnimator::PlayAnim(std::string ID) {
	_animatorWrapper->PlayAnim(ID);
}

void eden_ec::CAnimator::StopAnim() {
	_animatorWrapper->StopAnim();
}

void eden_ec::CAnimator::OnAnimEnd() {
	_animatorWrapper->OnAnimEnd();
}

void eden_ec::CAnimator::SetOnAnimEnd(std::string animID, std::string endAnimID) {
	_animatorWrapper->SetOnAnimEnd(animID, endAnimID);
}

std::string eden_ec::CAnimator::GetCurrentAnim() {
	return _animatorWrapper->GetCurrentAnim();
}
