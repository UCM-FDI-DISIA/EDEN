#include "../../dependencies/Bullet/src/src/BulletCollision/CollisionShapes/btBoxShape.h"
#include "../../dependencies/Bullet/src/src/BulletCollision/CollisionShapes/btSphereShape.h"
#include "../../dependencies/Bullet/src/src/BulletCollision/CollisionShapes/btCapsuleShape.h"
#include "../../dependencies/Bullet/src/src/BulletCollision/CollisionShapes/btCylinderShape.h"
#include "../../dependencies/Bullet/src/src/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h"

#include "../EDEN/Vector3.h"
#include "ShapeCreator.h"


btBoxShape physics_wrapper::ShapeCreator::CreateBox(float x, float y, float z)
{
    return btBoxShape(btVector3(x / 2, y / 2, z / 2));
}

btBoxShape physics_wrapper::ShapeCreator::CreateBox(eden_utils::Vector3 lengths)
{
    return btBoxShape(btVector3(lengths.GetX() / 2, lengths.GetY() / 2, lengths.GetZ() / 2));
}

btSphereShape physics_wrapper::ShapeCreator::CreateSphere(float r)
{
    return btSphereShape(r);
}

btCapsuleShape physics_wrapper::ShapeCreator::CreateCapsule(float r, float h)
{
    return btCapsuleShape(r, h);
}

btCylinderShape physics_wrapper::ShapeCreator::CreateCylinder(float x, float y, float z)
{
    return btCylinderShape(btVector3(x / 2, y / 2, z / 2));
}

btCylinderShape physics_wrapper::ShapeCreator::CreateCylinder(eden_utils::Vector3 lengths)
{
    return btCylinderShape(btVector3(lengths.GetX() / 2, lengths.GetY() / 2, lengths.GetZ() / 2));
}
