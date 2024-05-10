#ifndef EDEN_ENTITY_H
#define EDEN_ENTITY_H

#include <unordered_map>

#include "Component.h"
#include "ComponentFactory.h"

#include "defs.h"

namespace eden_script {
    struct EntityInfo;
    struct ComponentInfo;
    class ComponentArguments;
    class LuaManager;
}

namespace eden_ec {
	/// @brief Clase que define las Entidades de nuestro juego como contenedores de Componentes,
    /// que definiran el comportamiento y las distinguiran de otras entidades.
    /// Se encarga de gestionar sus componentes, haciendo las llamdas pertinentes a los mismo
	class Entity
	{
        friend class eden_script::LuaManager;
	public:
		/// @brief Construye una entidad generica
        EDEN_API Entity() = default;

        /// @brief Construye una entidad generica y le da nombre
        /// @param id El nombre que queremos darle a la entidad
        EDEN_API inline Entity(std::string id, std::string sceneID) { _ID = id; _sceneID = sceneID; }

        /// @brief Destruye la entidad y sus componentes asociados
        EDEN_API ~Entity();

        /// @brief Devuelve el nombre identificativo de la entidad
        EDEN_API inline std::string GetEntityID() const { return _ID;}

		/// @brief Dice si la entidad esta o no viva
		/// @return True = Viva | False = Muerta
        EDEN_API inline bool IsAlive() const { return _alive; }

		/// @brief Permite cambiar el estado de vida de una entidad.
		/// @param alive Si se pasa 'true' la entidad estara viva. Si se pasa 'false', la entidad morira y el siguiente frame no existira
        EDEN_API inline void SetAlive(bool alive) { _alive = alive; }

		/// @brief Metodo que dice si la entidad esta activa o no. 
		/// @return True = Activa | False = Inactiva
        EDEN_API inline bool IsActive() const { return _active; }

		/// @brief Permite cambiar el estado de una entidad entre activa e inactiva
		/// @param active True = Activa la entidad | False = Desactiva la entidad
        EDEN_API inline void SetActive(bool active) { _active = active; }

        /// @brief Quita un componente de la entidad dada su id
        /// @param id El ID del componente a quitar
        EDEN_API inline void RemoveComponent(std::string id);

        template <typename T, typename... Ts>
        inline void RemoveComponent(Ts&&... args) {
            RemoveComponent(T::GetID());
        }

        /// @brief Aniade un componente a la entidad dado su tipo y los argumentos que requiera el
        /// componente dado
        /// @tparam ...Ts Tipos de los argumentos que se requieren para la creacion del componente
        /// @tparam T Tipo del componente
        /// @param ...args Argumentos para el componente
        /// @return Componente creado
        template <typename T, typename... Ts>
        EDEN_API inline Component* AddComponent(Ts&&... args) {
            
            Component* c = new T(args...);
            _components.emplace(T::GetID(), c);
            c->SetContext(this);
            return c;
        }

        /// @brief Aniade un componente segun la informacion leida en un mapa. 
        /// @param info Informacion leida desde un mapa .lua.
        EDEN_API Component* AddComponentByRead(eden_script::ComponentArguments* info);

        /// @brief Crea todos los componentes de la entidad
        /// @param info Struct que da valor al nombre y a los componentes de una entidad. Se construye a traves
        /// de la lectura de archivos .lua. Ver el proyecto de EDEN_Script para m�s informacion (ScriptManager.h)
        EDEN_API void AddComponents(eden_script::EntityInfo* info);

        /// @brief Llama al m�todo Start de todos los componentes
        /// Llamado al final del frame donde la entidad ha sido creada
        EDEN_API void AwakeComponents();

        /// @brief Llama al m�todo Start de todos los componentes
        /// Se llama al inicializar las entidades en la escena, durante el primer instante del frame siguiente al que han sido creadas, que es cuando
        /// las entidades comienzan a formar parte del loop 
        EDEN_API void StartComponents();

        /// @brief Nos devuelve un componente asociado a una entidad dada su ID
        /// @param T Tipo del componente
        /// @return Puntero a la instancia del componente asociada a la entidad
        EDEN_API Component* GetComponent(std::string id);
        
        /// @brief Devuelve el ID de la escena a la que pertenece
        /// @return Devuelve el ID de la escena a la que pertenece
        EDEN_API std::string GetSceneID();

        /// @brief Nos devuelve un componente asociado a una entidad dado su tipo
        /// @param T Tipo del componente
        /// @return Puntero a la instancia del componente asociada a la entidad
        template<typename T>
        EDEN_API T* GetComponent() {
            return static_cast<T*>(GetComponent(T::GetID()));
        };

        /// @brief Comprueba si una entidad tiene cierto componente dada su ID
        /// @return Un booleano indicando si la entidad tiene o no el componente pedido
        EDEN_API bool HasComponent(std::string id);

        /// @brief Comprueba si una entidad tiene cierto componente dado su tipo
        /// @param T Tipo del componente
        /// @return Un booleano indicando si la entidad tiene o no el componente pedido
        template<typename T>
        EDEN_API bool HasComponent() {
            return HasComponent(T::GetID());
        };

        /// @brief Llama al update de todos los componentes de una entidad
        EDEN_API void Update(float t);

    private:
        /// @brief Variable que indica si una entidad esta viva o no. En caso de no estarlo, debera
        /// ser borrada en el siguiente update
        bool _alive = true;
        /// @brief Variable que indica si una entidad esta activa o no. En caso de no estarlo,
        /// no llamara a los metodos de sus componentes
        bool _active = true;

        /// @brief Mapa desordenado que contiene un componente segun la ID del componente
        std::unordered_map<std::string, Component*> _components;

        /// @brief Variable que identifica a la entidad por nombre 
        std::string _ID = "ENTITY_NEEDS_NEW_NAME";

        /// @brief ID de la escena a la que pertenece
        std::string _sceneID;
	};
}

#endif //NOMRBE_DEL_ARCHIVO_H