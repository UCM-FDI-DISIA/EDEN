#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

namespace eden_ec {
    class Entity;
	/// @brief Clase genérica de component usada para la implementación de los comportamientos de las entidades
	class Component
	{
    protected:

        /// @brief Referencia a la entidad que contiene este componente
        Entity* _ent = nullptr;
        /// @brief Cada entidad solo puede tener 1 componente de cada tipo. Ese 'tipo'
        /// es definido por esta variable _id, que tiene que ser cambiada por cada nuevo componente creado.
        /// Se le da valor en el .cpp
        /// @warning ESTO DEBE SER REDEFINIDO EN CADA COMPONENTE!!!!!!!!
        const static std::string _id;

        /// @brief WIP: Este método servirá para inicializar los componentes que han sido creados por
        /// su ID, en lugar de por su tipo (ver ComponentFactory.h para más información). Por el momento
        /// no hace nada, pues no tendremos el caso de crear componentes desde fuera del motor hasta
        /// que comencemos el desarrollo de los juegos; pero la idea sería que este método reciba
        /// un struct genérico con información leída desde un archivo '.lua' que podremos usar
        /// para inicializar los componentes con sus argumentos de constructora.
        virtual void init(/*Struct_Info info*/) {};
    public:
        /// @brief Constructora por defecto
        Component() = default;

        /// @brief Constructora por defecto. No hace nada especial
        virtual ~Component() = default;

        /// @brief Getter de la ID. Usado para creación de los componentes (ver ComponentFactory.h y Entity.h)
        /// @return ID del componente
        static std::string GetID();

        /// @brief Da contexto al componente, asginándole cuál es su entidad
        /// @param ent Es la entidad a la que pertenece el componente
        void SetContext(Entity* ent);

        /// @brief Inicializa el componente para coger referencias a otros componentes de su entidad
        virtual void initComponent() {};

        /// @brief Método ejecutado cada frame
        /// @param t Tiempo transcurrido desde el último frame
        virtual void update(float t) {}

        /// @brief Maneja la entrada del usuario
        virtual void handleInput() {}
	};
}
#endif // COMPONENT_H