#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include "Component.h"
#include "ComponentFactory.h"

namespace eden_ec {
	/// @brief Clase que define las Entidades de nuestro juego como contenedores de Componentes,
    /// que definirán el comportamiento y las distinguirán de otras entidades.
    /// Se encarga de gestionar sus componentes, haciendo las llamdas pertinentes a los mismo
	class Entity
	{
	public:
		/// @brief Construye una entidad genérica
		Entity() = default;

        ~Entity();

        /// @brief Devuelve el nombre identificativo de la entidad
        inline std::string GetEntityID() const { return _ID;}

		/// @brief Dice si la entidad está o no viva
		/// @return True = Viva | False = Muerta
		inline bool IsAlive() const { return _alive; }

		/// @brief Permite cambiar el estado de vida de una entidad.
		/// @param alive Si se pasa 'true' la entidad estará viva. Si se pasa 'false', la entidad morirá y el siguiente frame no existirá
		inline void SetAlive(bool alive) { _alive = alive; }

		/// @brief Método que dice si la entidad está activa o no. 
		/// @return True = Activa | False = Inactiva
		inline bool IsActive() const { return _active; }

		/// @brief Permite cambiar el estado de una entidad entre activa e inactiva
		/// @param active True = Activa la entidad | False = Desactiva la entidad
		inline void SetActive(bool active) { _active = active; }

        /// @brief Quita un componente de la entidad dada su id
        /// @param id El ID del componente a quitar
        inline void RemoveComponent(std::string id);

        /// @brief Añade un componente a la entidad dado su tipo y los argumentos que requiera el
        /// componente dado
        /// @tparam ...Ts Tipos de los argumentos que se requieren para la creación del componente
        /// @tparam T Tipo del componente
        /// @param ...args Argumentos para el componente
        /// @return Componente creado
        template <typename T, typename... Ts>
        inline Component* AddComponent(Ts&&... args) {

            Component* c = ComponentFactory::Instance()->CreateComponent<T>(args...);
            _components.emplace(T::GetID(), c);
            c->SetContext(this);
            c->InitComponent();

            return c;
        }

        /// @brief Añade un nuevo componente a la entidad según su ID.
        /// Cabe destacar que este apartado está en WIP (ver más información en Component.h
        /// y ComponentFactory.h), ya que no tenemos el struct de información definido para poder
        /// inicializar un componente con sus correspondientes argumentos de construcción.
        /// @param id Id del componente
        /// @return Componente creado
        Component* AddComponentByName(std::string id/*, Struct_Info info*/);

        /// @brief Nos devuelve un componente asociado a una entidad dada su ID
        /// \tparam T Tipo del componente
        /// \return Puntero a la instancia del componente asociada a la entidad
        Component* GetComponent(std::string id);

        /// @brief Nos devuelve un componente asociado a una entidad dado su tipo
        /// @tparam T Tipo del componente
        /// @return Puntero a la instancia del componente asociada a la entidad
        template<typename T>
        Component* GetComponent() {
            return getComponent(T::GetID());
        };

        /// @brief Comprueba si una entidad tiene cierto componente dada su ID
        /// @return Un booleano indicando si la entidad tiene o no el componente pedido
        bool HasComponent(std::string id);

        /// @brief Comprueba si una entidad tiene cierto componente dado su tipo
        /// @param T Tipo del componente
        /// @return Un booleano indicando si la entidad tiene o no el componente pedido
        template<typename T>
        Component* HasComponent() {
            return hasComponent(T::GetID());
        };

        /// @brief Llama al update de todos los componentes de una entidad
        void Update(float t);

        /// @brief Llama al handleInput de todos los componentes de una entidad
        void HandleInput();

    private:
        /// @brief Variable que indica si una entidad está viva o no. En caso de no estarlo, deberá
        /// ser borrada en el siguiente update
        bool _alive = true;
        /// @brief Variable que indica si una entidad está activa o no. En caso de no estarlo,
        /// no llamará a los métodos de sus componentes
        bool _active = true;

        /// @brief Mapa desordenado que contiene un componente según la ID del componente
        std::unordered_map<std::string, Component*> _components;

        /// @brief Variable que identifica a la entidad por nombre 
        std::string _ID;
	};
}

#endif //NOMRBE_DEL_ARCHIVO_H