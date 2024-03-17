#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletCollision/CollisionShapes/btCylinderShape.h>
#include <BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>

#include "ShapeCreator.h"
#include "Vector3.h"


btBoxShape* physics_wrapper::ShapeCreator::CreateBox(float x, float y, float z)
{
    return new btBoxShape(btVector3(x / 2, y / 2, z / 2));
}

btBoxShape* physics_wrapper::ShapeCreator::CreateBox(eden_utils::Vector3 lengths)
{
    return new btBoxShape(btVector3(lengths.GetX() / 2, lengths.GetY() / 2, lengths.GetZ() / 2));
}

btSphereShape* physics_wrapper::ShapeCreator::CreateSphere(float r)
{
    return new btSphereShape(r);
}

btCapsuleShape* physics_wrapper::ShapeCreator::CreateCapsule(float r, float h)
{
    return new btCapsuleShape(r, h);
}

btCylinderShape* physics_wrapper::ShapeCreator::CreateCylinder(float x, float y, float z)
{
    return new btCylinderShape(btVector3(x / 2, y / 2, z / 2));
}

btCylinderShape* physics_wrapper::ShapeCreator::CreateCylinder(eden_utils::Vector3 lengths)
{
    return new btCylinderShape(btVector3(lengths.GetX() / 2, lengths.GetY() / 2, lengths.GetZ() / 2));
}
