#ifndef EDEN_TRANSFORM_H
#define EDEN_TRANSFORM_H

#include <string>
#include <vector>

#include "Component.h"
#include "Vector3.h"
#include "Quaternion.h"

#include "defs.h"

namespace eden_ec {

	/// @brief Componente que tiene toda entidad que gestiona su posicion, rotacion y escala
	class CTransform : public Component
	{
	public:
		enum AXIS_REFERENCE {AXIS_WORLD, AXIS_LOCAL};
		/// @brief Constructora por defecto del Transform
		EDEN_API CTransform() = default;

		/// @brief Constructora con parametros
		/// @param position Posicion de la entidad en la que se va a generar
		/// @param rotation Rotacion de la entidad con la que se va a generar
		/// @param scale Escala de la entidad con la que se va a generar
		EDEN_API CTransform(eden_utils::Vector3 position, eden_utils::Quaternion rotation, eden_utils::Vector3 scale);

		/// @brief Construye el componente dado unos argumentos. Se obtendran de una lectura de un .lua
		/// @param args Argumentos leidos de .lua
		EDEN_API void Init(eden_script::ComponentArguments* args) override;

		/// @brief No usado
		EDEN_API void Awake() override {};

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		EDEN_API void Start() override{};

		EDEN_API ~CTransform() override = default;

		/// @brief Getter de la posicion
		/// @return Devuelve el vector de posicion
		EDEN_API inline eden_utils::Vector3 GetPosition() const { return _position; }

		/// @brief Getter de la rotacion
		/// @return Devuelve el cuaternion de la rotacion
		EDEN_API inline eden_utils::Quaternion GetRotation() const { return _rotation; }

		/// @brief Getter de la escala
		/// @return Devuelve el vector de la escala
		EDEN_API inline eden_utils::Vector3 GetScale() const { return _scale; }

		/// @brief Setter de la posicion
		/// @param position Nueva posicion del transform
		EDEN_API void SetPosition(eden_utils::Vector3 position);

		/// @brief Setter de la rotacion
		/// @param rotation Nueva rotacion del transform
		EDEN_API void SetRotation(eden_utils::Quaternion rotation);

		/// @brief Setter de la escala
		/// @param scale Nueva escala del transform
		EDEN_API void SetScale(eden_utils::Vector3 scale);

		/// @brief Suma la posicion
		/// @param position Vector que se va a sumar
		EDEN_API void Translate(eden_utils::Vector3 position, bool isGlobal = false);

		/// @brief Rota el transform 
		/// @param angle angulo en grados 
		/// @param axis Eje sobre el que va a rotar
		EDEN_API void Rotate(float angle, eden_utils::Vector3 axis);
		EDEN_API void LocalRotate(float angle, eden_utils::Vector3 axis);

		/// @brief Rota el transform en el eje X
		/// @param angle angulo en grados
		EDEN_API void Pitch(float angle);
		EDEN_API void LocalPitch(float angle);

		/// @brief Rota el transform en el eje Y
		/// @param angle angulo en grados
		EDEN_API void Yaw(float angle);
		EDEN_API void LocalYaw(float angle);

		/// @brief Rota el transform en el eje Z
		/// @param angle angulo en grados
		EDEN_API void Roll(float angle);
		EDEN_API void LocalRoll(float angle);

		/// @brief Suma la escala del transform
		/// @param scale Vector que suma a la escala
		EDEN_API void Escalate(eden_utils::Vector3 scale);

		/// @brief Calcula el eje z positivo local
		/// @return Devuelve el vector forward
		EDEN_API eden_utils::Vector3 GetForward();

		/// @brief Calcula el eje y positivo local
		/// @return Devuelve el vector up
		EDEN_API eden_utils::Vector3 GetUp();

		/// @brief Calcula el eje x positivo local
		/// @return Devuelve el vector right
		EDEN_API eden_utils::Vector3 GetRight();

		/// @brief Ajusta el padre de un transform
		/// @param pTr Referencia al transform que queremos que sea el nuevo padre
		EDEN_API void SetParent(eden_ec::CTransform* pTr);

		/// @brief Devuelve el transform padre
		/// @return La funcion devuelve un puntero al transform del padre si existe, si no, devuelve nullptr
		EDEN_API eden_ec::CTransform* GetParent();

		/// @brief Aniade un transform al vector del hijos
		/// @param cTr Referencia al transform del hijo que queremos aniadir
		EDEN_API void AddChild(eden_ec::CTransform* cTr);

		/// @brief Quita un transform del vector del hijos
		/// @param cTr Referencia al transform del hijo que queremos quitar
		/// @return Devuelve true si la operación se pudo completar
		EDEN_API bool RemoveChild(eden_ec::CTransform* cTr);

		/// @brief Accede al transform de un hijo, si existe
		/// @param index El indice del vector de hijos que se quiere consultar
		/// @return Devuelve el transform del hijo, si no existe devuelve nullptr
		EDEN_API eden_ec::CTransform* GetChild(int index);

		/// @brief Devuelve el índice del hijo en el vector
		/// @param cTr El transform del hijo
		/// @return Devuelve el ínidice del hijo si existe, si no, devuelve -1
		EDEN_API int HasChild(eden_ec::CTransform* cTr);

		/// @brief Definición de método estático GetID necesario para construcción de componentes
		EDEN_API static std::string GetID() { return "TRANSFORM"; }

		/// @brief Rota la entidad con respecto un transform
		/// @param other Transform alrededor de la que rota
		/// @param angle Angulo que rota
		/// @param axis Eje sobre el que rota
		EDEN_API void RotateAroundObject(CTransform* other, float angle, eden_utils::Vector3 axis);
		EDEN_API void LocalRotateAroundObject(CTransform* other, float angle, eden_utils::Vector3 axis);
	private:
		/// @brief Variable de posicion
		eden_utils::Vector3 _position;
		/// @brief Variable de rotacion
		eden_utils::Quaternion _rotation;
		/// @brief Variable de escala
		eden_utils::Vector3 _scale;
		/// @brief Vector de transform hijos
		std::vector<eden_ec::CTransform*> _childrenVector;
		/// @brief Referencia al padre de un transform
		eden_ec::CTransform* _parentTransform = nullptr;
	};
}
#endif

