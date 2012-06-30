#ifndef __RubyOgreRoot_H__
#define __RubyOgreRoot_H__

#include "main.hpp"
#include <OgrePlugin.h>
void Init_OgreRoot(VALUE rb_mOgre);
extern Ogre::Root *root;

template <>
VALUE wrap< Ogre::Plugin >(Ogre::Plugin *man );
template <>
Ogre::Root* wrap< Ogre::Root* >(const VALUE &vvector);
#endif /* __RubyOgreVector3_H__ */
