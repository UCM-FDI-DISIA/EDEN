#define _CRTDBG_MAP_ALLOC
#include "CMeshRenderer.h"
#include <RenderManager.h>
#include <ComponentArguments.h>
#include <MeshRenderer.h>
#include <NodeManager.h>
#include "Entity.h"
#include "Vector3.h"

const std::string eden_ec::CMeshRenderer::_id = "MESH_RENDERER";

eden_ec::CMeshRenderer::CMeshRenderer(std::string mesh) : Component(),
_mesh(mesh) {};

eden_ec::CMeshRenderer::~CMeshRenderer() {
	delete _renderWrapper;
	eden_render::RenderManager::Instance()->removeRenderEntity(_ent);
};

void eden_ec::CMeshRenderer::Init(eden_script::ComponentArguments* args)
{
	//GESTION DE ERRORES
	_mesh = args->GetValueToString("Mesh") + MESH_EXTENSION;
	
	_renderWrapper = new render_wrapper::MeshRenderer(_ent->GetEntityID(), _mesh);
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