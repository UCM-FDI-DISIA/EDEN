#ifndef SHAPE_CREATOR_H
#define SHAPE_CREATOR_H

class btBoxShape;
class btSphereShape;
class btCapsuleShape;
class btCylinderShape;

namespace eden_utils {
	class Vector3;
}

namespace physics_manager {
	/// @brief Clase para construir formas para el RigidBody
	class ShapeCreator
	{
	public:
		/// @brief Crea la clase btBoxShape
		/// @param x Longitud en el eje x
		/// @param y Longitud en el eje y
		/// @param z Longitud en el eje z
		/// @return Devuelve una instancia de btBoxShape
		static btBoxShape CreateBox(float x, float y, float z);

		/// @brief Crea la clase btBoxShape a partir de un Vector3
		/// @param lengths Vector con las longitudes
		/// @return Devuelve una instancia de btBoxShape
		static btBoxShape CreateBox(eden_utils::Vector3 lengths);

		/// @brief Crea la clase btSphereShape
		/// @param r Radio de la esfera
		/// @return Devuelve una instancia de btSphereShape
		static btSphereShape CreateSphere(float r);

		/// @brief Crea la clase btCapsuleShape
		/// @param r Radio de la cápsula
		/// @param h Altura de la cápsula
		/// @return Devuelve una instancia de btCapsuleShape
		static btCapsuleShape CreateCapsule(float r, float h);

		/// @brief Crea la clase btCylinderShape
		/// @param x Longitud en el eje x
		/// @param y Longitud en el eje y
		/// @param z Longitud en el eje z
		/// @return Devuelve una instancia de btCylinderShape
		static btCylinderShape CreateCylinder(float x, float y, float z);

		/// @brief Crea la clase btCylinderShape a partir de un Vector3
		/// @param lengths Vector con las longitudes
		/// @return Devuelve una instancia de btCylinderShape
		static btCylinderShape CreateCylinder(eden_utils::Vector3 lengths);
	};
}

#endif // !_SHAPE_CREATOR_H


