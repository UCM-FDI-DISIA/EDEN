#include "CMeshRenderer.h"
#include "RenderManager.h"
#include "ComponentArguments.h"
#include "MeshRenderer.h"
#include "Entity.h"
#include "Node.h"
#include "Vector3.h"
#include "Transform.h"
const std::string eden_ec::CMeshRenderer::_id = "MESH_RENDERER";

eden_ec::CMeshRenderer::CMeshRenderer(std::string mesh) : Component(),
_mesh(mesh) {

};

eden_ec::CMeshRenderer::~CMeshRenderer() {
	eden_render::RenderManager::Instance()->removeRenderEntity(_ent);
};

void eden_ec::CMeshRenderer::Init(eden_script::ComponentArguments* args)
{
	//GESTION DE ERRORES
	_mesh = args->GetValueToString("Mesh") + ".mesh";
	
	_renderWrapper = new render_wrapper::MeshRenderer(_ent->GetEntityID(), _mesh);
	_transform = _ent->GetComponent<CTransform>();
	eden_render::RenderManager::Instance()->addRenderEntity(_ent);
}

void eden_ec::CMeshRenderer::SetMaterial(const std::string material)
{
	_renderWrapper->SetMaterial(material);
}

void eden_ec::CMeshRenderer::SetInvisible(bool visibility)
{
	_renderWrapper->SetInvisible(visibility);
}

void eden_ec::CMeshRenderer::Update(float dt) {
	_transform->SetPosition(_transform->GetPosition() + eden_utils::Vector3(0, 0, 0.01 * dt));

	_renderWrapper->ActivateAnim(dt);
}
