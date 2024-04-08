#include <vector>

#include "CParticleEmitter.h"
#include "ParticleSystem.h"
#include "Entity.h"
#include <ComponentArguments.h>

const std::string eden_ec::CParticleEmitter::_id = "PARTICLE_EMITTER";

eden_ec::CParticleEmitter::CParticleEmitter()
{
	_time = 0;
	_elapsedTime = 0;
	_loop = false;
	_pSystem = nullptr;
}

eden_ec::CParticleEmitter::CParticleEmitter(std::string system) : Component()
{
	_pSystem = new render_wrapper::ParticleSystem(_ent->GetEntityID(), _ent->GetSceneID(), system, _ent->GetEntityID());
	_time = 0;
	_elapsedTime = 0;
	_loop = 0;
}

eden_ec::CParticleEmitter::~CParticleEmitter()
{
	delete _pSystem;
}

void eden_ec::CParticleEmitter::Init(eden_script::ComponentArguments* args)
{
	std::string name = args->GetValueToString("Name");

	_pSystem = new render_wrapper::ParticleSystem(_ent->GetEntityID(), _ent->GetSceneID(), name, _ent->GetEntityID());

	_loop = args->GetValueToBool("Loop");

	_time = args->GetValueToFloat("Time");

	SetActive(args->GetValueToBool("Started"));

	_elapsedTime = 0;

}

void eden_ec::CParticleEmitter::Update(float t)
{
	if (!_loop && IsActive()) {
		_elapsedTime += t;
		if (_elapsedTime >= _time)
			_pSystem->SetActive(false);
	}
}

bool eden_ec::CParticleEmitter::IsActive()
{
	return _pSystem->IsActive();
}

void eden_ec::CParticleEmitter::SetActive(bool active,bool sceneChanged)
{
	if (active)
	{
		if (!sceneChanged || (sceneChanged && _isEmiting)) _pSystem->SetActive(active);
	}
	else
	{
		_pSystem->SetActive(active);
	}
	if (!sceneChanged) _isEmiting = active;
}

void eden_ec::CParticleEmitter::SetVisible(bool visibility, bool sceneChanged)
{
	if (visibility)
	{
		if (!sceneChanged || (sceneChanged && _particleVisibility)) _pSystem->SetVisible(visibility);
	}
	else
	{
		_pSystem->SetVisible(visibility);
	}
	if (!sceneChanged) _particleVisibility = visibility;
}

void eden_ec::CParticleEmitter::SetMaterial(const std::string material)
{
	_pSystem->SetMaterial(material);
}

void eden_ec::CParticleEmitter::Reset()
{
	_elapsedTime = 0;
	SetActive(true);
}
