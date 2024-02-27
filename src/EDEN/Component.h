#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

namespace eden_ec {
    class Entity;
	/// @brief Clase gen�rica de component usada para la implementaci�n de los comportamientos de las entidades
	class Component
	{
    public:
        /// @brief Constructora por defecto
        Component() = default;

        /// @brief Constructora por defecto. No hace nada especial
        virtual ~Component() = default;

        /// @brief Getter de la ID. Usado para creaci�n de los componentes (ver ComponentFactory.h y Entity.h)
        /// @return ID del componente
        static const std::string GetID();

        /// @brief Da contexto al componente, asgin�ndole cu�l es su entidad
        /// @param ent Es la entidad a la que pertenece el componente
        void SetContext(Entity* ent);

        /// @brief Inicializa el componente para coger referencias a otros componentes de su entidad
        virtual void InitComponent() {};

        /// @brief M�todo ejecutado cada frame
        /// @param t Tiempo transcurrido desde el �ltimo frame
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
        const static std::string _id;

        /// @brief WIP: Este m�todo servir� para inicializar los componentes que han sido creados por
        /// su ID, en lugar de por su tipo (ver ComponentFactory.h para m�s informaci�n). Por el momento
        /// no hace nada, pues no tendremos el caso de crear componentes desde fuera del motor hasta
        /// que comencemos el desarrollo de los juegos; pero la idea ser�a que este m�todo reciba
        /// un struct gen�rico con informaci�n le�da desde un archivo '.lua' que podremos usar
        /// para inicializar los componentes con sus argumentos de constructora.
        virtual void Init(/*Struct_Info info*/) {};
	};
}
#endif // COMPONENT_H