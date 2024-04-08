#define _CRTDBG_MAP_ALLOC
#include "CMeshRenderer.h"
#include <RenderManager.h>
#include <ComponentArguments.h>
#include <MeshRenderer.h>
#include <NodeManager.h>
#include "ResourcesManager.h"
#include "Entity.h"
#include "Vector3.h"

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
	
	_renderWrapper = new render_wrapper::MeshRenderer(_ent->GetEntityID(), _ent->GetSceneID(), _mesh);
	eden_render::RenderManager::Instance()->addRenderEntity(_ent);
	
	//SetMaterial("test");
}

void eden_ec::CMeshRenderer::SetMaterial(const std::string material)
{
	if(eden_resources::ResourcesManager::Instance()->FileExist(material,eden_resources::ResourcesManager::Materials))
		_renderWrapper->SetMaterial(material);
	else if (eden_resources::ResourcesManager::Instance()->FileExist("default.png", eden_resources::ResourcesManager::Default))
		_renderWrapper->SetMaterial("default.png");
}

void eden_ec::CMeshRenderer::SetInvisible(bool visibility)
{
	_renderWrapper->SetInvisible(visibility);
}