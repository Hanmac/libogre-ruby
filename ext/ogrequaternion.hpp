#ifndef __RubyOgreQuaternion_H__
#define __RubyOgreQuaternion_H__

#include "main.hpp"
void Init_OgreQuaternion(VALUE rb_mOgre);
extern VALUE rb_cOgreQuaternion;


template <>
VALUE wrap< Ogre::Quaternion >(Ogre::Quaternion *quaternion );

template <>
Ogre::Quaternion* wrap< Ogre::Quaternion* >(const VALUE &vquaternion);

template <>
Ogre::Quaternion wrap< Ogre::Quaternion >(const VALUE &vquaternion);

#endif /* __RubyOgreQuaternion_H__ */
