#ifndef __RubyOgreRoot_H__
#define __RubyOgreRoot_H__

#include "main.hpp"
#include <OgrePlugin.h>
void Init_OgreRoot(VALUE rb_mOgre);
extern Ogre::Root *root;

template <>
inline VALUE wrap< Ogre::Plugin >(Ogre::Plugin *man )
{
	return wrap(man->getName());
}
template <>
inline Ogre::Root* wrap< Ogre::Root* >(const VALUE &vvector)
{
	if(root==NULL)
		root = new Ogre::Root();
	return Ogre::Root::getSingletonPtr();
}
#endif /* __RubyOgreVector3_H__ */
