#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H

#include <unordered_map>
#include <string>

#include "Singleton.h"

namespace eden_ec {
	class Component;
	class Entity;

	/// @brief Clase cuya utilidad reside en crear los componentes de las entidades del juego.
	/// Es capaz de crearlas a partir de su tipo o a partir de su ID.
	class ComponentFactory : public Singleton<ComponentFactory>
	{
		/// @brief Necesitamos acceder al m�todo 'init' de Component, que es protegido.
		friend Component;
		/// @brief Para obtener la funcionalidad del patr�n Singleton
		friend Singleton<ComponentFactory>;
	public:
		/// @brief Registra un componente dado seg�n su ID y le asocia una funci�n
		/// para poder crearlos.
		/// @tparam T Componente a registrar
		template<typename T>
		void RegisterComponent() {
			if (!ComponentExists(T::GetID()))
				_currentComponents.emplace(T::GetID(), &ComponentFactory::CreateComponentNoArgs<T>);
		};

		/// @brief Crea componentes del tipo especificado en la Template y le pasa los argumentos 
		/// correspondientes.
		/// @tparam T El tipo de componente a crear
		/// @tparam ...Ts Par�metros de construcci�n del componente de tipo T
		/// @param e Entidad que contiene el componente que se est� creando
		/// @param ...args Par�metros de construcci�n del componente de tipo T
		/// @return El componente creado
		template<typename T, typename... Ts>
		Component* CreateComponent(Ts&&... args) {
			if (!ComponentExists(T::GetID())) return nullptr;

			Component* c = new T(args...);

			return c;
		}

		/// @brief Crea un componente a partir de su ID. Lo construye por defecto,
		/// usando su constructora por defecto (no pasa par�metros)
		/// @param e Entidad que llevar� el componente a crear
		/// @param id Id del componente a crear
		/// @return Componente creado
		Component* CreateComponentByName(std::string id);
	private:
		/// @brief Componentes registrados en la Factor�a.
		/// Son IDs de componentes asociadas a las constructoras por defecto de lo mismos.
		/// Estas constructoras por defecto no son capaces de tomar argumentos, pues los m�todos
		/// con templates no pueden ser virtuales (usar�amos templates para no definir una cantidad 
		/// concreta de argumentos en sus constructoras).
		/// M�s informaci�n en 'Component.h'
		std::unordered_map<std::string, Component* (*)()> _currentComponents;

		/// @brief Constructor por defecto
		ComponentFactory() = default;

		/// @brief Comprueba si un componente existe en la factor�a
		/// @param id ID del componente a comprobar
		/// @return True = Existe | False = No existe
		bool ComponentExists(std::string id);

		/// @brief Funci�n que ser� llamada como callback para crear componentes por nombre.
		/// Esta funci�n construye los componentes por defecto, no pasa argumentos.
		/// @tparam T Componente a crear
		/// @return Componente de tipo T creado
		template<typename T>
		static Component* CreateComponentNoArgs() {
			return new T();
		}
	};
}

#endif // !COMPONENT_FACTORY_H