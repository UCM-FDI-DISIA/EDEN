#ifndef EDEN_C_BAR_H
#define EDEN_C_BAR_H

#include <string>

#include <UIComponent.h>

#include "defs.h"

namespace Ogre {
	class Overlay;
}

namespace eden_ec {
	/// @brief Clase que representa una barra en la UI
	class EDEN_API CBar : public eden_ec::UIComponent {
	public:
		/// @brief Constructora de la clase Bar
		CBar() = default;

		/// @brief Constructora de la clase Bar
		CBar(std::string overlayName, float xPos, float yPos, float width,
			float height, std::string texture, int depth = 0);

		/// @brief Destructora de la clase Bar
		~CBar();

		/// @brief Metodo que crea la Barra
		void Create(std::string overlayName, float xPos, float yPos, float width,
			float height, std::string texture, int depth = 0);

		/// @brief Construye el componente dado unos argumentos. Se obtendran de una lectura de un .lua
		/// @param args Argumentos le�dos de .lua
		void Init(eden_script::ComponentArguments* args) override;

		/// @brief No utilizado
		void Awake() override {};

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		void Start() override {}

		/// @brief Metodo que cambia el porcentaje de la barra
		/// @param p Porcentaje nuevo a cambiar
		void SetBarPercentage(float p);

		/// @brief Metodo que devuelve el porcentaje de la barra
		float GetBarPercentage() const;

		/// @brief Definicion de metodo estatico GetID necesario para construccion de componentes
		static std::string GetID() { return "BAR"; }
	private:
		/// @brief Tamanio total de la barra
		float _totalWidth = 0;
		float _totalHeight = 0;

		/// @brief Porcentaje de la barra
		float _percentage = 100;
	};
} 

#endif 