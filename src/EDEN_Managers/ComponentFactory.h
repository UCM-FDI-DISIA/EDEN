#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_COMPONENT_FACTORY_H
#define EDEN_COMPONENT_FACTORY_H

#include <unordered_map>
#include <string>

#include "Singleton.h"

#include "defs.h"

namespace eden_ec {
	class Component;
	class Entity;

	/// @brief Clase cuya utilidad reside en crear los componentes de las entidades del juego.
	/// Es capaz de crearlas a partir de su tipo o a partir de su ID.
	class ComponentFactory : public Singleton<ComponentFactory>
	{
		/// @brief Necesitamos acceder al metodo 'init' de Component, que es protegido.
		friend Component;
		/// @brief Para obtener la funcionalidad del patron Singleton
		friend Singleton<ComponentFactory>;
	public:
		/// @brief Registra un componente dado segun su ID y le asocia una funcion
		/// para poder crearlos.
		/// @tparam T Componente a registrar
		template<typename T>
		EDEN_API void RegisterComponent() {
			if (!ComponentExists(T::GetID()))
				_currentComponents.emplace(T::GetID(), &ComponentFactory::CreateComponentNoArgs<T>);
		};

		/// @brief Crea componentes del tipo especificado en la Template y le pasa los argumentos 
		/// correspondientes.
		/// @tparam T El tipo de componente a crear
		/// @tparam ...Ts Parametros de construccion del componente de tipo T
		/// @param e Entidad que contiene el componente que se esta creando
		/// @param ...args Parametros de construccion del componente de tipo T
		/// @return El componente creado
		template<typename T, typename... Ts>
		EDEN_API Component* CreateComponent(Ts&&... args) {
			if (!ComponentExists(T::GetID())) return nullptr;

			Component* c = new T(args...);

			return c;
		}

		/// @brief Crea un componente a partir de su ID. Lo construye por defecto,
		/// usando su constructora por defecto (no pasa parametros)
		/// @param e Entidad que llevara el componente a crear
		/// @param id Id del componente a crear
		/// @return Componente creado
		EDEN_API Component* CreateComponentByName(std::string id);
	private:
		/// @brief Componentes registrados en la Factoria.
		/// Son IDs de componentes asociadas a las constructoras por defecto de lo mismos.
		/// Estas constructoras por defecto no son capaces de tomar argumentos, pues los metodos
		/// con templates no pueden ser virtuales (usaramos templates para no definir una cantidad 
		/// concreta de argumentos en sus constructoras).
		/// M�s informacion en 'Component.h'
		std::unordered_map<std::string, Component* (*)()> _currentComponents;

		/// @brief Constructor por defecto
		EDEN_API ComponentFactory() = default;

		/// @brief Comprueba si un componente existe en la factoria
		/// @param id ID del componente a comprobar
		/// @return True = Existe | False = No existe
		EDEN_API bool ComponentExists(std::string id);

		/// @brief Funcion que sera llamada como callback para crear componentes por nombre.
		/// Esta funcion construye los componentes por defecto, no pasa argumentos.
		/// @tparam T Componente a crear
		/// @return Componente de tipo T creado
		template<typename T>
		static Component* CreateComponentNoArgs() {
			return new T();
		}
	};
}

#endif // !COMPONENT_FACTORY_H