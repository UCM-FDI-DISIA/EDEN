#ifndef EDEN_EDEN_SCENE_H
#define EDEN_EDEN_SCENE_H

#include "Component.h"

namespace eden_ec {
	/// @brief Componente que se encarga de la reproduccion de la escena inicial que contiene el logotipo de Cube Studios y del motor EDEN
	class CEDENScene : public Component {
	public:
		/// @brief Constructora por defecto
		CEDENScene() = default;

		/// @brief Destructora por defecto
		~CEDENScene() = default;

		/// @brief Construye el componente dado unos argumentos. Se obtendran de una lectura de un .lua
		/// @param args Argumentos leidos de .lua
		void Init(eden_script::ComponentArguments* args) override {}

		/// @brief No usado
		void Awake() override {}

		/// @brief Se usa para coger referencias a otros componentes
		void Start() override;

		/// @brief Metodo update heredado de component 
		void Update(float dt) override;

		/// @brief Definicion de metodo estatico GetID necesario para construccion de componentes
		static std::string GetID() { return "CEDEN_SCENE_COMP"; }
	private:
		/// @brief Tiempo total que se mantiene la escena en pantalla
		float _totalTime = 0.0f;
	};
}

#endif