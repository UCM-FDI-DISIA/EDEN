#ifndef EDEN_AUDIOLISTENER_H
#define EDEN_AUDIOLISTENER_H

#include "Vector3.h"

namespace audio_wrapper {
    /// Clase que se encargara de proporcionar funcionalidad a un listener. El listener es necesario para audio en 3D, y necesitara de un AudioEmitter para poder escuchar audio. En audio 2D no es necesario.
    /// Solo se podra tener un AudioListener por escena, ya que no hay soporte para multiples listeners.
    class AudioListener {
    public:
        /// @brief Constructora por defecto del listener de audio
        /// @param position Posicion del listener
        /// @param hearingDirection Direccion desde la que el listener escucha sonidos (o direccion en la que mira el listener)
        /// @param movingSpeed Velocidad de movimiento del listener (SOLO PARA EFECTO DOPPLER). (0,0,0) por defecto
        /// @param normal Vector normal del listener para saber cual es la izq. y la dcha. (0,1,0) por defecto
        AudioListener(eden_utils::Vector3 position, eden_utils::Vector3 hearingDirection, eden_utils::Vector3 movingSpeed = { 0,0,0 }, eden_utils::Vector3 normal = {0,1,0});
        
        /// @brief Destructora por defecto del listener de audio
        ~AudioListener() = default;

        /// @brief Establece la posicion del listener
        /// @param position Vector con la posicion del listener
        void SetPosition(eden_utils::Vector3 position);

        /// @brief Devuelve la posicion del listener
        /// @return Vector con la posicion del listener
        inline eden_utils::Vector3 GetPosition() const { return _listenerPosition; }

        /// @brief Establece la direccion desde la que el listener escucha o "mira"
        /// @param dir Vector con la direccion desde la que el listener escucha
        void SetHearingDirection(eden_utils::Vector3 dir);

        /// @brief Devuelve la direccion desde la que el listener escucha o "mira"
        /// @return Vector con la direccion desde la que el listener escucha
        inline eden_utils::Vector3 GetHearingDirection() const { return _hearingDirection; }

        /// @brief Establece la velocidad de movimiento (SOLO PARA EFECTO DOPPLER) del listener
        /// @param speed Vector con la velocidad de movimiento del listener
        void SetMovingSpeed(eden_utils::Vector3 speed);

        /// @brief Devuelve la velocidad de movimiento del listener
        /// @return Vector con la velocidad de movimiento del listener
        inline eden_utils::Vector3 GetSpeed() const { return _movingSpeed; }

        /// @brief Establece el vector normal del listener para que este sepa cual es su izquierda y su derecha
        /// @param normal Vector normal del listener
        void SetNormal(eden_utils::Vector3 normal);

        /// @brief Devuelve el vector normal del listener
        /// @return Vector normal del listener
        inline eden_utils::Vector3 GetNormal() const { return _normal; }
    private:
        /// @brief Posicion del listener
        eden_utils::Vector3 _listenerPosition;

        /// @brief Direccion desde la que el listener escucha
        eden_utils::Vector3 _hearingDirection;

        /// @brief Velocidad de movimiento del listener
        eden_utils::Vector3 _movingSpeed;

        /// @brief Vector normal del listener
        eden_utils::Vector3 _normal;
    };
}



#endif //AUDIOLISTENER_H
