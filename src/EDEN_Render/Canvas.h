#ifndef EDEN_CANVAS_H
#define EDEN_CANVAS_H

#include <unordered_set>

#include "Singleton.h"

namespace eden_ec {
	class UIComponent;
}
namespace eden_canvas {
	class Canvas :public Singleton<Canvas>
	{
	public:
		friend Singleton<Canvas>;

		/// @brief Actualiza el tamaño y posicion de los componentes
		void Resize();

		/// @brief Inicializa los valores base de los componentes
		void InitCanvas();

		/// @brief Destructora
		~Canvas() = default;

		/// @brief Añade un puntero a un componente de UI
		/// para actualizar su posición y tamaño
		/// @param ent Entidad cuya posición va a actualizarse
		void addRenderEntity(eden_ec::UIComponent* ent);

		/// @brief Quita el componente para dejar de actualizar su posición
		/// @param ent Entidad que se va a quitar
		void removeRenderEntity(eden_ec::UIComponent* ent);
	private:
		/// @brief Constructora
		Canvas() = default;
		/// @brief Conjunto de componentes para actualizar su posición
		std::unordered_set<eden_ec::UIComponent*> _entities;
	};
}
#endif __CANVAS_H__
