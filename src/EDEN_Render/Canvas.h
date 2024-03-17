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

		/// @brief Actualiza el tama�o y posicion de los componentes
		void Resize();

		/// @brief Inicializa los valores base de los componentes
		void InitCanvas();

		/// @brief Constructora
		Canvas() = default;

		/// @brief Destructora
		~Canvas();

		/// @brief A�ade un puntero a un componente de UI
		/// para actualizar su posici�n y tama�o
		/// @param ent Entidad cuya posici�n va a actualizarse
		void addRenderEntity(eden_ec::UIComponent* ent);

		/// @brief Quita el componente para dejar de actualizar su posici�n
		/// @param ent Entidad que se va a quitar
		void removeRenderEntity(eden_ec::UIComponent* ent);
	private:
		/// @brief Conjunto de componentes para actualizar su posici�n
		std::unordered_set<eden_ec::UIComponent*> _entities;
	};
}
#endif __CANVAS_H__
