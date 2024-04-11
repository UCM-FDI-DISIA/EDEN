#define _CRTDBG_MAP_ALLOC
#ifndef EDEN_TRANSFORM_H
#define EDEN_TRANSFORM_H

#include <string>
#include <vector>

#include "Component.h"
#include "Vector3.h"
#include "Quaternion.h"

#include "defs.h"

namespace eden_ec {

	/// @brief Componente que tiene toda entidad que gestiona su posici�n, rotaci�n y escala
	class __declspec(dllexport) CTransform : public Component
	{
	public:
		enum AXIS_REFERENCE {AXIS_WORLD, AXIS_LOCAL};
		/// @brief Constructora por defecto del Transform
		CTransform() = default;

		/// @brief Constructora con par�metros
		/// @param position Posici�n de la entidad en la que se va a generar
		/// @param rotation Rotaci�n de la entidad con la que se va a generar
		/// @param scale Escala de la entidad con la que se va a generar
		CTransform(eden_utils::Vector3 position, eden_utils::Quaternion rotation, eden_utils::Vector3 scale);

		/// @brief Construye el componente dado unos argumentos. Se obtendrán de una lectura de un .lua
		/// @param args Argumentos leídos de .lua
		void Init(eden_script::ComponentArguments* args) override;

		/// @brief Se usa para coger referencias a otros componentes
		/// En este caso no se necesita
		void Start() override{};

		~CTransform() override = default;

		/// @brief Getter de la posici�n
		/// @return Devuelve el vector de posici�n
		inline eden_utils::Vector3 GetPosition() const { return _position; }

		/// @brief Getter de la rotaci�n
		/// @return Devuelve el cuaterni�n de la rotaci�n
		inline eden_utils::Quaternion GetRotation() const { return _rotation; }

		/// @brief Getter de la escala
		/// @return Devuelve el vector de la escala
		inline eden_utils::Vector3 GetScale() const { return _scale; }

		/// @brief Setter de la posici�n
		/// @param position Nueva posici�n del transform
		void SetPosition(eden_utils::Vector3 position);

		/// @brief Setter de la rotaci�n
		/// @param rotation Nueva rotaci�n del transform
		void SetRotation(eden_utils::Quaternion rotation);

		/// @brief Setter de la escala
		/// @param scale Nueva escala del transform
		void SetScale(eden_utils::Vector3 scale);

		/// @brief Suma la posici�n
		/// @param position Vector que se va a sumar
		void Translate(eden_utils::Vector3 position);

		/// @brief Rota el transform 
		/// @param angle �ngulo en grados 
		/// @param axis Eje sobre el que va a rotar
		void Rotate(float angle, eden_utils::Vector3 axis);

		/// @brief Rota el transform en el eje X
		/// @param angle �ngulo en grados
		void Pitch(float angle);

		/// @brief Rota el transform en el eje Y
		/// @param angle �ngulo en grados
		void Yaw(float angle);

		/// @brief Rota el transform en el eje Z
		/// @param angle �ngulo en grados
		void Roll(float angle);

		/// @brief Suma la escala del transform
		/// @param scale Vector que suma a la escala
		void Escalate(eden_utils::Vector3 scale);

		/// @brief Calcula el eje z positivo local
		/// @return Devuelve el vector forward
		eden_utils::Vector3 GetForward();

		/// @brief Calcula el eje y positivo local
		/// @return Devuelve el vector up
		eden_utils::Vector3 GetUp();

		/// @brief Calcula el eje x positivo local
		/// @return Devuelve el vector right
		eden_utils::Vector3 GetRight();

		/// @brief Ajusta el padre de un transform
		/// @param pTr Referencia al transform que queremos que sea el nuevo padre
		void SetParent(eden_ec::CTransform* pTr);

		/// @brief Devuelve el transform padre
		/// @return La función devuelve un puntero al transform del padre si existe, si no, devuelve nullptr
		eden_ec::CTransform* GetParent();

		/// @brief Añade un transform al vector del hijos
		/// @param cTr Referencia al transform del hijo que queremos añadir
		void AddChild(eden_ec::CTransform* cTr);

		/// @brief Quita un transform del vector del hijos
		/// @param cTr Referencia al transform del hijo que queremos quitar
		/// @return Devuelve true si la operación se pudo completar
		bool RemoveChild(eden_ec::CTransform* cTr);

		/// @brief Accede al transform de un hijo, si existe
		/// @param index El índice del vector de hijos que se quiere consultar
		/// @return Devuelve el transform del hijo, si no existe devuelve nullptr
		eden_ec::CTransform* GetChild(int index);

		/// @brief Devuelve el índice del hijo en el vector
		/// @param cTr El transform del hijo
		/// @return Devuelve el ínidice del hijo si existe, si no, devuelve -1
		int HasChild(eden_ec::CTransform* cTr);

		/// @brief Definición de método estático GetID necesario para construcción de componentes
		static std::string GetID() { return "TRANSFORM"; }
	private:
		/// @brief Variable de posici�n
		eden_utils::Vector3 _position;
		/// @brief Variable de rotaci�n
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

