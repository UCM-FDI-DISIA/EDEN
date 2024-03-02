#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include "Component.h"
#include "Transform.h"
#include "Resources/Texture.h"

namespace eden_ec {

	/// @brief Componente de imagen para la UI
	class Image : public eden_ec::Component
	{
	public:
		/// @brief Constructora
		/// @param tx Textura
		Image(Texture* tx);

		/// @brief Destructora
		virtual ~Image() = default;

		/// @brief Inicializa el componente para coger referencias a otros componentes de su entidad
		void InitComponent() override;

		/// @brief M�todo ejecutado cada frame
		/// @param t Tiempo transcurrido desde el �ltimo frame
		void Update(float t) override;

		/// @brief Renderizado de la imagen
		void Render();

		/// @brief Anchura de la imagen
		int GetWidth() const { return _texture->width(); }

		/// @brief Altura de la imagen
		int GetHeight() const { return _texture->height(); }

		/// @brief Cambio de textura
		/// @param tx Textura
		void ChangeTexture(Texture* tx) { _texture = tx; }

		/// @brief Desactiba el renderizado
		void DisableRender() { _allowRender = false; }

		/// @brief Activa el renderizado
		void EnableRender() { _allowRender = true; }
	private:
		eden_ec::CTransform* _transform;
		Texture* _texture;

		bool _allowRender;
		SDL_Rect _rect;

	};
}
#endif