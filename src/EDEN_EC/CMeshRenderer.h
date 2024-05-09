#ifndef EDEN_C_MESH_RENDERER_H
#define EDEN_C_MESH_RENDERER_H

#ifdef _MSC_VER
#define MESH_ROUTE "assets\\meshes\\"
#define MATERIAL_ROUTE "assets\\materials\\"
#endif
#ifdef __APPLE__
#define MESH_ROUTE "assets/meshes/"
#define MATERIAL_ROUTE "assets/materials/"
#endif

#define MESH_EXTENSION ".mesh"

// Librerias de C++
#include <string>

// Archivos del proyecto
#include "Component.h"

#include "defs.h"

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
		EDEN_API CMeshRenderer() = default;

		/// @brief Constructora con parametros
		/// @param mesh Nombre del archivo de la malla .mesh
		EDEN_API CMeshRenderer(std::string mesh);

		/// @brief Construye el componente dado unos argumentos. Se obtendran de una lectura de un .lua
		/// @param args Argumentos leidos de .lua
		EDEN_API void Init(eden_script::ComponentArguments* args) override;

		/// @brief Crea el wrapper de meshRenderer
		EDEN_API void Awake() override;

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		EDEN_API void Start() override {}

		EDEN_API ~CMeshRenderer() override;

		/// @brief Pone un material a la malla
		/// @param material Nombre del archivo del material
		EDEN_API inline void SetMaterial(const std::string material);

		/// @brief Setea la la visibilidad de la malla
		/// @param visibility True -> Visible, False -> No visible
		EDEN_API inline void SetInvisible(bool visibility, bool sceneChanged = false);

		/// @brief Devuelve el identificador del componente
		EDEN_API static std::string GetID() { return "MESH_RENDERER"; }

	private:
		/// @brief Inicializa el Wrapper de MeshRenderer
		void InitializeWrapper();

		/// @brief Puntero al wrapper del mesh renderer de la libreria
		render_wrapper::MeshRenderer* _renderWrapper = nullptr;
		/// @brief Variable del archivo de la malla
		std::string _mesh;
		/// @brief 
		bool _meshVisibility = true;
		
	};
}
#endif // C_MESH_RENDERER_H
