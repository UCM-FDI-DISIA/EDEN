#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

namespace eden_ec {
    class Entity;
	/// @brief Clase gen�rica de component usada para la implementaci�n de los comportamientos de las entidades
	class Component
	{
    protected:

        /// @brief Referencia a la entidad que contiene este componente
        Entity* _ent = nullptr;
        /// @brief Cada entidad solo puede tener 1 componente de cada tipo. Ese 'tipo'
        /// es definido por esta variable _id, que tiene que ser cambiada por cada nuevo componente creado.
        /// Se le da valor en el .cpp
        const static std::string _id;

        /// ���AVISO!!!
        /// TODOS LOS COMPONENTES CREADOS DEBEN TENER UN M�TODO EST�TICO QUE HAGA LO SIGUIENTE:

        /// static std::string GetID() { return _id; };

        /// PARA PODER CREARSE DESDE LA FACTOR�A. 

        /// @brief WIP: Este m�todo servir� para inicializar los componentes que han sido creados por
        /// su ID, en lugar de por su tipo (ver ComponentFactory.h para m�s informaci�n). Por el momento
        /// no hace nada, pues no tendremos el caso de crear componentes desde fuera del motor hasta
        /// que comencemos el desarrollo de los juegos; pero la idea ser�a que este m�todo reciba
        /// un struct gen�rico con informaci�n le�da desde un archivo '.lua' que podremos usar
        /// para inicializar los componentes con sus argumentos de constructora.
        virtual void init(Entity* e/*, Struct_Info info*/) {};
    public:
        /// @brief Constructora por defecto
        Component() = default;

        /// @brief Constructora por defecto. No hace nada especial
        virtual ~Component() = default;

        /// @brief Getter de la ID. Usado para creaci�n de los componentes (ver ComponentFactory.h y Entity.h)
        /// @return ID del componente
        static std::string GetID();

        /// @brief Da contexto al componente, asgin�ndole cu�l es su entidad
        /// @param ent Es la entidad a la que pertenece el componente
        void SetContext(Entity* ent);

        /// @brief Inicializa el componente para coger referencias a otros componentes de su entidad
        virtual void initComponent() {};

        /// @brief M�todo ejecutado cada frame
        /// @param t Tiempo transcurrido desde el �ltimo frame
        virtual void update(float t) {}

        /// @brief Maneja la entrada del usuario
        virtual void handleInput() {}
	};
}
#endif // COMPONENT_H