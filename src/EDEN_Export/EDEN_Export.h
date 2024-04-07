#ifndef EDEN_EXPORT_H_
#define EDEN_EXPORT_H_

namespace eden_render {
	class RenderManager;
}
namespace eden_input {
	class InputManager;
}

namespace physics_manager {
	class PhysicsManager;
}

namespace eden_script {
	class ScriptManager;
}

eden_render::RenderManager* renderMngr;
eden_input::InputManager* inputMngr;
physics_manager::PhysicsManager* physicsMngr;
eden_script::ScriptManager* scriptMngr;

void initEngine();
void deleteEngine();
void runEngine();

#endif EDEN_EXPORT_H_