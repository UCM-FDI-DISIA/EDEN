#include "CMeshRenderer.h"
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

void eden_ec::CMeshRenderer::Init(eden_script::ComponentArguments* args)
{
	//GESTION DE ERRORES
	_mesh = args->GetValueToString("Mesh") + ".mesh";
	
	_renderWrapper = new render_wrapper::MeshRenderer(_ent->GetEntityID(), _mesh);
	_transform = _ent->GetComponent<CTransform>();

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
	render_wrapper::Node::Instance()->SetPosition(_transform->GetPosition(), _ent->GetEntityID());
	render_wrapper::Node::Instance()->Scale(_transform->GetScale(), _ent->GetEntityID());
	render_wrapper::Node::Instance()->SetOrientation(_transform->GetRotation(), _ent->GetEntityID());

	_renderWrapper->ActivateAnim(dt);
}
