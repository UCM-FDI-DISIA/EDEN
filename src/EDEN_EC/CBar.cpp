#define _CRTDBG_MAP_ALLOC
#include "CBar.h"
#include <RenderManager.h>
#include <ScriptManager.h>
#include <ComponentArguments.h>
#include "Entity.h"


eden_ec::CBar::CBar(std::string overlayName, float xPos, float yPos,
	float width, float height, std::string texture,
	int depth) {

	if(_ent!=nullptr)Register(_ent->GetSceneID());
	Create(overlayName, xPos, yPos, width, height, texture, depth);
}

void eden_ec::CBar::Create(std::string overlayName, float xPos, float yPos,
	float width, float height, std::string texture,
	int depth)
{
	auto render = eden_render::RenderManager::Instance();
	int w = render->GetWindowWidth();
	int h = render->GetWindowHeight();

	if (width > 100)width = 100;
	else if (width < 0)width = 0;
	width = w * (width / 100);

	if (height > 100)height = 100;
	else if (height < 0)height = 0;
	height = h * (height / 100);

	if (xPos > 100)xPos = 100;
	else if (xPos < 0)xPos = 0;
	int xx = w * (xPos / 100);

	if (yPos > 100)yPos = 100;
	else if (yPos < 0)yPos = 0;
	int yy = h * (yPos / 100);

	xPos = xx - (width / 2);
	yPos = yy - (height / 2);

	CreateImage(overlayName, (float)xPos, (float)yPos, (float)width, (float)height, texture, depth);
	_totalWidth = (float)width;
}

eden_ec::CBar::~CBar() {}

void eden_ec::CBar::Init(eden_script::ComponentArguments* args) {

	int xPos = args->GetValueToInt("XPos");
	int yPos = args->GetValueToInt("YPos");
	int width = args->GetValueToInt("Width");
	int height = args->GetValueToInt("Height");

	Create(args->GetValueToString("OverlayName"), float(xPos), float(yPos), float(width), float(height),
		args->GetValueToString("Texture"), args->GetValueToInt("Depth"));
	Register(_ent->GetSceneID());
}

void eden_ec::CBar::SetBarPercentage(float p)
{
	_totalWidth = (100 * _oWidth) / _percentage;
	if (p < 0)p = 1;
	else if (p > 100)p = 100;
	_percentage = p;
	SetDimensions(_totalWidth * (p / 100), _oHeight);
}

float eden_ec::CBar::GetBarPercentage() const
{
	return _percentage;
}
