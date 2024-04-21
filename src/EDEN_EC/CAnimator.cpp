#define _CRTDBG_MAP_ALLOC
#include "CAnimator.h"
#include <ScriptManager.h>
#include <ComponentArguments.h>
#include <Animator.h>
#include "CMeshRenderer.h"
#include "Entity.h"
#include <RenderManager.h>

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

void eden_ec::CAnimator::InitializeWrapper() {
	if (_animatorWrapper) return;
	_meshRend = _ent->GetComponent<CMeshRenderer>();
	_animatorWrapper = new render_wrapper::Animator(_meshRend->_renderWrapper);

	for (int i = 0; i < _animNames.size(); ++i) {
		_animatorWrapper->RegisterAnim(_animNames[i], _animMeshNames[i], _nextAnim[i], _loopAnims[i]);
	}
}

void eden_ec::CAnimator::Start() {
	InitializeWrapper();
}

void eden_ec::CAnimator::Update(float dt) {
	InitializeWrapper();

	_animatorWrapper->UpdateAnim(dt);
}

void eden_ec::CAnimator::PlayAnim(std::string ID) {
	InitializeWrapper();

	_animatorWrapper->PlayAnim(ID);
}

void eden_ec::CAnimator::StopAnim() {
	InitializeWrapper();

	_animatorWrapper->StopAnim();
}

void eden_ec::CAnimator::OnAnimEnd() {
	InitializeWrapper();

	_animatorWrapper->OnAnimEnd();
}

void eden_ec::CAnimator::SetOnAnimEnd(std::string animID, std::string endAnimID) {
	InitializeWrapper();

	_animatorWrapper->SetOnAnimEnd(animID, endAnimID);
}

std::string eden_ec::CAnimator::GetCurrentAnim() {
	InitializeWrapper();

	return _animatorWrapper->GetCurrentAnim();
}
