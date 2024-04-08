#define _CRTDBG_MAP_ALLOC
#include "CText.h"
#include <RenderManager.h>
#include <ScriptManager.h>
#include <ComponentArguments.h>


eden_ec::CText::CText(std::string overlayName, float xPos, float yPos,
	float tam, std::string text, std::string font, float rColor, float gColor, float bColor,
	int depth) {
	auto render = eden_render::RenderManager::Instance();
	int w = render->GetWindowWidth();
	int h = render->GetWindowHeight();
	float xx = w * xPos / 100;
	float yy = h * yPos / 100;
	xPos = xx - (tam*text.length() / 2);
	yPos = yy - (tam / 2);

	CreateText(overlayName, xPos, yPos, tam, text, font, rColor, gColor, bColor, depth);

}

eden_ec::CText::~CText() {}

void eden_ec::CText::Init(eden_script::ComponentArguments* args) {

	auto render = eden_render::RenderManager::Instance();
	int xPos = args->GetValueToInt("XPos");
	int yPos = args->GetValueToInt("YPos");
	int tam = args->GetValueToInt("Tam");

	int w = render->GetWindowWidth();
	int h = render->GetWindowHeight();
	int xx = w * xPos / 100;
	int yy = h * yPos / 100;
	xPos = (int)(xx - (tam* args->GetValueToString("Text").length() / 2));
	yPos = yy - (tam / 2);

	CreateText(args->GetValueToString("OverlayName"), float(xPos), float(yPos), float(tam),
		args->GetValueToString("Text"), args->GetValueToString("Font"), args->GetValueToVector3("Color").GetX(), 
		args->GetValueToVector3("Color").GetY(), args->GetValueToVector3("Color").GetZ(), args->GetValueToInt("Depth"));

}

void eden_ec::CText::SetNewText(const std::string& text) {
	SetText(text);
}

std::string eden_ec::CText::GetCurrentText() {
	return GetText();
}