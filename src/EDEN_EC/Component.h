#ifndef EDEN_COMPONENT_H
#define EDEN_COMPONENT_H

#include <string>

#include "defs.h"

namespace eden_script {
    class ComponentArguments;
}

namespace eden_ec {
    class Entity;
	/// @brief Clase generica de component usada para la implementacion de los comportamientos de las entidades
	class Component
	{
        friend Entity;
    public:
        /// @brief Constructora por defecto
        EDEN_API Component() = default;

        /// @brief Constructora por defecto. No hace nada especial
        EDEN_API virtual ~Component() = default;

        /// @brief Da contexto al componente, asginandole cual es su entidad
        /// @param ent Es la entidad a la que pertenece el componente
        EDEN_API void SetContext(Entity* ent);

        /// @brief Metodo ejecutado cada frame
        /// @param t Tiempo transcurrido desde el ultimo frame
        EDEN_API virtual void Update(float t) {}

        /// @brief Metodo que desactiva el componente (No se llama su update)
        /// @param active Booleano para activar o desactivar el componente
        EDEN_API inline void SetActive(bool active) {
            _active = active;
        }

        /// @brief Comprueba si el componente esta activo
        /// @return True si el componente esta activo, false en caso contrario
        EDEN_API inline bool IsActive() {
            return _active;
        }

    protected:
        /// @brief Referencia a la entidad que contiene este componente
        Entity* _ent = nullptr;
        /// @brief Cada entidad solo puede tener 1 componente de cada tipo. Ese 'tipo'
        /// es definido por esta variable _id, que tiene que ser cambiada por cada nuevo componente creado.
        /// Se le da valor en el .cpp
        /// @warning ESTO DEBE SER REDEFINIDO EN CADA COMPONENTE!!!!!!!!
        /// @warning TAMBIEN SE DEBE DEFINIR UN METODO ESTATICA PARA CADA CLASE QUE HEREDE DE COMPONENTE
        /// QUE SE LLAME 'GetID()' Y DEVUELVA UN 'std::string _id'

        /// @brief Usaremos este metodo abstracto para definir en cada clase su construccion mediante 'ID'.
        /// Cada componente debe redefinirlo para poder aceptar argumentos leidos desde un fichero .lua
        /// @param args Argumentos leidos desde un fichero .lua
        virtual void Init(eden_script::ComponentArguments* args) = 0;
        
        /// @brief Llamado despu�s de la creaci�n de un componente, usado para inicilizar objetos importantes para el funcionamiento de este componente,
        /// y que puedan ser llamados desde otro componente en su Start.
        virtual void Awake() = 0;

        /// @brief Usaremos este m�todo para a�adir referencias de otros componentes
        virtual void Start() = 0;

        /// @brief Booleano para saber si el componente esta activo
        bool _active = true;
	};
}
#endif // COMPONENT_H