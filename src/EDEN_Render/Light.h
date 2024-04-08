//#define _CRTDBG_MAP_ALLOC
//#ifndef EDEN_LIGHT_H
//#define EDEN_LIGHT_H
//
//#include "RenderObject.h"
//#include <string>
//
//namespace eden_utils {
//	class Vector3;
//	class Quaternion;
//}
//
//namespace Ogre {
//	class Light;
//}
//
//namespace render_wrapper
//{
//	class Light : public RenderObject
//	{
//	public:
//		/// @brief enumerado que indica el tipo de luz 
//		/// @brief Constructora del Wrapper de libreria de renderizado de luces
//		/// @param enetityID Nombre de la entidad asociada 
//		Light(const std::string entityID, const std::string sceneID, const std::string type);
//		~Light() {};
//
//		/// @brief Setea la visibilidad de la luz
//		/// @param visibility True -> Visible, False -> No visible
//		inline void SetVisible(bool visibility);
//		/// @brief Devuelve si la luz es visible o no
//		inline bool isVisible();
//		/// @brief 
//		/// @param color Variable de color
//		inline void SetDiffuse(eden_utils::Vector3 color);
//		/// @brief 
//		/// @param color Variable de color
//		inline void SetSpecular(eden_utils::Vector3 color);
//		/// @brief Setea la direccion de la luz
//		/// @param dir Vector de direccion de la luz
//		inline void SetDirection(eden_utils::Vector3 dir);
//		/// @brief Setea la posicion de la luz
//		/// @param dir Vector de posicion de la luz
//		inline void SetPosition(eden_utils::Vector3 dir);
//		/// @brief Setea la orientacion de la luz
//		/// @param dir Quaternion de orientacion de la luz
//		inline void SetOrientation(eden_utils::Quaternion dir);
//
//	private:
//		/// @brief Puntero a la luz de la libreria de renderizado
//		Ogre::Light* _light = nullptr;
//		/// @brief Variable de visibilidad
//		bool _visibility = true;
//		/// @brief Identificador de la entidad asociada
//		std::string _entityID = "";
//
//		/// @brief Devuelve el puntero de la luz
//		Ogre::MovableObject* GetRenderObject() override;
//	};
//}
//#endif // LIGHT_H