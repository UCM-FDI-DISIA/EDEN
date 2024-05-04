#define _CRTDBG_MAP_ALLOC
#include "CText.h"
#include <RenderManager.h>
#include <ScriptManager.h>
#include <ComponentArguments.h>
#include "Entity.h"

eden_ec::CText::CText(std::string overlayName, float xPos, float yPos,
	float tam, std::string text, std::string font, float rColor, float gColor, float bColor,
	int depth) {

	if(_ent!=nullptr)Register(_ent->GetSceneID());
	Create(overlayName, xPos, yPos, tam, text, font, rColor, gColor, bColor, depth);
}

eden_ec::CText::~CText() {}

void eden_ec::CText::Create(std::string overlayName, float xPos, float yPos, float tam, std::string text, std::string font, float rColor, float gColor, float bColor, int depth)
{
	
	auto render = eden_render::RenderManager::Instance();
	int w = render->GetWindowWidth();
	int h = render->GetWindowHeight();

	if (tam > 100)tam = 100;
	else if (tam < 0)tam = 0;
	tam = h * (tam / 100);

	if (xPos > 100)xPos = 100;
	else if (xPos < 0)xPos = 0;
	int xx = w * (xPos / 100);

	if (yPos > 100)yPos = 100;
	else if (yPos < 0)yPos = 0;
	int yy = h * (yPos / 100);


	xPos = xx - (tam * text.length() / 2);
	yPos = yy - (tam / 2);


	CreateText(overlayName, xPos, yPos, tam, text, font, rColor, gColor, bColor, depth);

}

void eden_ec::CText::Init(eden_script::ComponentArguments* args) {

	int xPos = args->GetValueToInt("XPos");
	int yPos = args->GetValueToInt("YPos");
	int tam = args->GetValueToInt("Tam");

	Create(args->GetValueToString("OverlayName"), float(xPos), float(yPos), float(tam),
		args->GetValueToString("Text"), args->GetValueToString("Font"), args->GetValueToVector3("Color").GetX(), 
		args->GetValueToVector3("Color").GetY(), args->GetValueToVector3("Color").GetZ(), args->GetValueToInt("Depth"));
	Register(_ent->GetSceneID());

}

void eden_ec::CText::SetNewText(const std::string& text, bool resize) {
	SetText(text,resize);
}

std::string eden_ec::CText::GetCurrentText() {
	return GetText();
}