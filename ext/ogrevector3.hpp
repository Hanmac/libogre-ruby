#ifndef __RubyOgreVector3_H__
#define __RubyOgreVector3_H__

#include "main.hpp"
void Init_OgreVector3(VALUE rb_mOgre);
extern VALUE rb_cOgreVector3;


template <>
bool wrapable< Ogre::Vector3 >(const VALUE &obj);

template <>
VALUE wrap< Ogre::Vector3 >(Ogre::Vector3 *vector );

template <>
Ogre::Vector3* wrap< Ogre::Vector3* >(const VALUE &vvector);

template <>
Ogre::Vector3 wrap< Ogre::Vector3 >(const VALUE &vvector);
#endif /* __RubyOgreVector3_H__ */
