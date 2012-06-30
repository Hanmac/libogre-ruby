#ifndef __RubyOgreMatrix4_H__
#define __RubyOgreMatrix4_H__

#include "main.hpp"
void Init_OgreMatrix4(VALUE rb_mOgre);
extern VALUE rb_cOgreMatrix4;


template <>
VALUE wrap< Ogre::Matrix4 >(Ogre::Matrix4 *matrix );

template <>
Ogre::Matrix4* wrap< Ogre::Matrix4* >(const VALUE &vmatrix);

template <>
Ogre::Matrix4 wrap< Ogre::Matrix4 >(const VALUE &vmatrix);

#endif /* __RubyOgreMatrix4_H__ */
