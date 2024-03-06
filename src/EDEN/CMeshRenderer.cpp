#include "CMeshRenderer.h"
#include "ComponentArguments.h"
#include "MeshRenderer.h"
#include "Entity.h"

const std::string eden_ec::CMeshRenderer::_id = "MESH_RENDERER";

eden_ec::CMeshRenderer::CMeshRenderer(std::string mesh) : Component(),
_mesh(mesh) {};

void eden_ec::CMeshRenderer::Init(eden_script::ComponentArguments* args)
{
	//GESTION DE ERRORES
	_mesh = args->GetValueToString("Mesh");
	
	_renderWrapper = new render_wrapper::MeshRenderer(_ent->GetEntityID(), _mesh);
}

void eden_ec::CMeshRenderer::SetMaterial(const std::string material)
{
	_renderWrapper->SetMaterial(material);
}

void eden_ec::CMeshRenderer::SetInvisible(bool visibility)
{
	_renderWrapper->SetInvisible(visibility);
}
