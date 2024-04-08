#define _CRTDBG_MAP_ALLOC
#include "CImage.h"
#include <RenderManager.h>
#include <ScriptManager.h>
#include <ComponentArguments.h>
#include "Entity.h"


const std::string eden_ec::CImage::_id = "IMAGE";

eden_ec::CImage::CImage(std::string overlayName, float xPos, float yPos,
	float width, float height, std::string texture,
	int depth) {

	auto render = eden_render::RenderManager::Instance();
	int w = render->GetWindowWidth();
	int h = render->GetWindowHeight();
	float xx = w * xPos / 100;
	float yy = h * yPos / 100;
	xPos = xx - (width / 2);
	yPos = yy - (height / 2);

	CreateImage(overlayName, xPos, yPos, width, height, texture, depth);
}

eden_ec::CImage::~CImage() {}

void eden_ec::CImage::Init(eden_script::ComponentArguments* args) {
	Register(_ent->GetSceneID());

	auto render = eden_render::RenderManager::Instance();
	int xPos = args->GetValueToInt("XPos");
	int yPos = args->GetValueToInt("YPos");
	int width = args->GetValueToInt("Width");
	int height = args->GetValueToInt("Height");

	int w = render->GetWindowWidth();
	int h = render->GetWindowHeight();
	int xx = w * xPos / 100;
	int yy = h * yPos / 100;
	xPos = xx - (width / 2);
	yPos = yy - (height / 2);

	CreateImage(args->GetValueToString("OverlayName"), float(xPos), float(yPos), float(width), float(height),
		args->GetValueToString("Texture"), args->GetValueToInt("Depth"));
	
}