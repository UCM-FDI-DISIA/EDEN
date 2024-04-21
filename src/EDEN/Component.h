#define _CRTDBG_MAP_ALLOC
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
	class EDEN_API Component
	{
        friend Entity;
    public:
        /// @brief Constructora por defecto
        Component() = default;

        /// @brief Constructora por defecto. No hace nada especial
        virtual ~Component() = default;

        /// @brief Da contexto al componente, asginandole cual es su entidad
        /// @param ent Es la entidad a la que pertenece el componente
        void SetContext(Entity* ent);

        /// @brief Metodo ejecutado cada frame
        /// @param t Tiempo transcurrido desde el ultimo frame
        virtual void Update(float t) {}

        /// @brief Maneja la entrada del usuario
        virtual void HandleInput() {}

    protected:
        /// @brief Referencia a la entidad que contiene este componente
        Entity* _ent = nullptr;
        /// @brief Cada entidad solo puede tener 1 componente de cada tipo. Ese 'tipo'
        /// es definido por esta variable _id, que tiene que ser cambiada por cada nuevo componente creado.
        /// Se le da valor en el .cpp
        /// @warning ESTO DEBE SER REDEFINIDO EN CADA COMPONENTE!!!!!!!!
        /// @warning TAMBIEN SE DEBE DEFINIR UN METODO ESTATICA PARA CADA CLASE QUE HEREDE DE COMPONENTE
        /// QUE SE LLAME 'GetID()' Y DEVUELVA UN 'std::string _id'
        const static std::string _id;

        /// @brief Usaremos este metodo abstracto para definir en cada clase su construccion mediante 'ID'.
        /// Cada componente debe redefinirlo para poder aceptar argumentos leidos desde un fichero .lua
        /// @param args Argumentos leidos desde un fichero .lua
        virtual void Init(eden_script::ComponentArguments* args) = 0;
        
        /// @brief Usaremos este metodo para aniadir referencias de otros componentes
        virtual void Start() = 0;
	};
}
#endif // COMPONENT_H