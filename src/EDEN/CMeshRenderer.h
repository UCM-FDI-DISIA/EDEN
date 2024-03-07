#ifndef C_MESH_RENDERER_H
#define C_MESH_RENDERER_H

#define MESH_ROUTE "assets\\mesh\\"
#define MATERIAL_ROUTE "assets\\material\\"

#include <string>

#include "Component.h"


namespace render_wrapper
{
	class MeshRenderer;
}

namespace eden_ec {
	class CTransform;
	class CAnimator;
	class CMeshRenderer : public Component
	{
		friend eden_ec::CAnimator;
	public:
		/// @brief Constructora por defecto del CMeshRenderer
		CMeshRenderer() = default;

		CMeshRenderer(std::string mesh);

		virtual void Init(eden_script::ComponentArguments* args);

		~CMeshRenderer();

		void SetMaterial(const std::string material);

		void SetInvisible(bool visibility);
		static std::string GetID() { return _id; }

		void Update(float dt);
	protected:
		const static std::string _id;
	private:
		render_wrapper::MeshRenderer* _renderWrapper = nullptr;

		std::string _mesh; 

		CTransform* _transform;
	};
}
#endif // C_MESH_RENDERER_H
