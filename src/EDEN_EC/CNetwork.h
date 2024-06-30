#ifndef EDEN_C_NETWORK_H_
#define EDEN_C_NETWORK_H_

#include <string>
#include "NetworkManager.h"

#include "Component.h"  // Asumiendo que tienes una clase base de entidad.

namespace eden_ec {
    class CNetwork : public Component {
    public:
        EDEN_API CNetwork() = default;
        EDEN_API ~CNetwork() override;

        /// @brief Inicializa el componente, guardando los argumentos recibidos desde lua
        /// @param args los argumentos que contienen informacion sobre ...
        EDEN_API void Init(eden_script::ComponentArguments* args) override;
        /// @brief Actualiza ...
        /// @param dt El tiempo transcurrido desde el ultimo frame
        EDEN_API void Update(float dt) override;

        /// @brief Se usa para ...
        EDEN_API void Awake() override;

        /// @brief No usado
        EDEN_API void Start() override {};
        /// @brief Devuelve el identificador del componente
        /// @return Identificador del componente
        EDEN_API static std::string GetID() { return "NETWORK"; }

        EDEN_API void Serialize(std::ostream& out) const;
        EDEN_API void Deserialize(std::istream& in);
        EDEN_API void SendState();
        EDEN_API void ReceiveState();

        uint32_t getNetworkID() const { return networkID; }
    private:
        eden_net::NetworkManager* networkManager;
        uint32_t networkID;  // Unique identifier for network purposes.
        std::string stateData;  // Serialized state data.
    };
}

#endif // EDEN_C_NETWORK_H_
