#ifndef EDEN_C_MESH_RENDERER_H
#define EDEN_C_MESH_RENDERER_H

#ifdef _MSC_VER
#define MESH_ROUTE "assets\\mesh\\"
#define MATERIAL_ROUTE "assets\\material\\"
#endif
#ifdef __APPLE__
#define MESH_ROUTE "assets/mesh/"
#define MATERIAL_ROUTE "assets/material/"
#endif

// Librerias de C++
#include <string>

// Archivos del proyecto
#include "Component.h"

namespace render_wrapper
{
	class MeshRenderer;
}

namespace eden_ec {
	class CAnimator;
	class CMeshRenderer : public Component
	{
		friend eden_ec::CAnimator;
	public:
		/// @brief Constructora por defecto del CMeshRenderer
		CMeshRenderer() = default;

		/// @brief Constructora con parametros
		/// @param mesh Nombre del archivo de la malla .mesh
		CMeshRenderer(std::string mesh);

		/// @brief Construye el componente dado unos argumentos. Se obtendr�n de una lectura de un .lua
		/// @param args Argumentos le�dos de .lua
		virtual void Init(eden_script::ComponentArguments* args);

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		void Start() override {}

		~CMeshRenderer();

		/// @brief Pone un material a la malla
		/// @param material Nombre del archivo del material
		inline void SetMaterial(const std::string material);

		/// @brief Setea la la visibilidad de la malla
		/// @param visibility True -> Visible, False -> No visible
		inline void SetInvisible(bool visibility);

		/// @brief Devuelve el identificador del componente
		static std::string GetID() { return _id; }

		/// @brief 
		/// @param dt Variable delta time
		void Update(float dt);

	protected:
		const static std::string _id;

	private:
		/// @brief Puntero al wrapper del mesh renderer de la libreria
		render_wrapper::MeshRenderer* _renderWrapper = nullptr;
		/// @brief Variable del archivo de la malla
		std::string _mesh; 
	};
}
#endif // C_MESH_RENDERER_H
