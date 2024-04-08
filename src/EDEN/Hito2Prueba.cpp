#include "Hito2Prueba.h"
#define _CRTDBG_MAP_ALLOC
#include "Entity.h"
#include "CAudioEmitter.h"
#include <string>
#include "Sound.h"

const std::string eden_ec::Hito2Prueba::_id = "PRUEBA2";
void eden_ec::Hito2Prueba::Start() {
	_audioEmitter = _ent->GetComponent<CAudioEmitter>();
	_audioEmitter->Play();
	_audioEmitter->SetLoop(true);
}
