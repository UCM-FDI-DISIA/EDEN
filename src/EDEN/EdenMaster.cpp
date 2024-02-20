#include "EdenMaster.h"
#include <OgreRoot.h>

eden::Master::Master()
{
	_root = new Ogre::Root();
}

eden::Master::~Master()
{
	delete _root;
	Singleton::~Singleton();
}

void eden::Master::Loop()
{

}
