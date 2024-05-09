#ifndef EDEN_AUDIOLISTENER_H
#define EDEN_AUDIOLISTENER_H

#include "Vector3.h"
#include "Component.h"

#include "defs.h"

namespace eden_ec {
    class CTransform;
    /// Clase que se encargara de proporcionar funcionalidad a un listener. El listener es necesario para audio en 3D, y necesitara de un AudioEmitter para poder escuchar audio.
    /// Solo se podra tener un AudioListener por escena, ya que no hay soporte para multiples listeners.
    class CAudioListener : public eden_ec::Component {
    public:
        /// @brief Constructora por defecto del listener de audio
        EDEN_API CAudioListener() = default;
        
        /// @brief Destructora por defecto del listener de audio
        EDEN_API ~CAudioListener() = default;

        /// @brief Construye el componente dado unos argumentos. Se obtendr�n de una lectura de un .lua
        /// @param args Argumentos le�dos de .lua
        EDEN_API void Init(eden_script::ComponentArguments* args) override {};
        
        /// @brief No usado
        EDEN_API void Awake() override {};

        /// @brief Usaremos este metodo para aniadir referencias de otros componentes
        EDEN_API void Start() override;

        /// @brief Metodo ejecutado cada frame
        /// @param t Tiempo transcurrido desde el ultimo frame
        EDEN_API void Update(float t) override;

        /// @brief Definici�n de m�todo est�tico GetID necesario para construcci�n de componentes
        EDEN_API inline static std::string GetID() { return "AUDIO_LISTENER"; }
    private:

        /// @brief Transform de la entidad sobre la que se engancha el listener
        eden_ec::CTransform* _transform = nullptr;
    };
}



#endif //AUDIOLISTENER_H
