#ifndef C_MESH_RENDERER_H
#define C_MESH_RENDERER_H

#include <string>

#include "Component.h"

namespace render_wrapper
{
	class MeshRenderer;
}

namespace eden_ec {
	class CMeshRenderer : public Component
	{
	public:
		/// @brief Constructora por defecto del CMeshRenderer
		CMeshRenderer() = default;

		CMeshRenderer(std::string mesh);

		virtual void Init(eden_script::ComponentArguments* args);

		~CMeshRenderer() = default;

		void SetMaterial(const std::string material);

		void SetInvisible(bool visibility);
	private:
		render_wrapper::MeshRenderer* _renderWrapper = nullptr;

		std::string _mesh; 
	};
}
#endif // C_MESH_RENDERER_H