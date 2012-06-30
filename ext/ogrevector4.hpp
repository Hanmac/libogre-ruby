#ifndef __RubyOgreVector4_H__
#define __RubyOgreVector4_H__

#include "main.hpp"
void Init_OgreVector4(VALUE rb_mOgre);
extern VALUE rb_cOgreVector4;

template <>
bool wrapable< Ogre::Vector4 >(const VALUE &obj);

template <>
VALUE wrap< Ogre::Vector4 >(Ogre::Vector4 *vector );

template <>
Ogre::Vector4* wrap< Ogre::Vector4* >(const VALUE &vvector);

template <>
Ogre::Vector4 wrap< Ogre::Vector4 >(const VALUE &vvector);

#endif /* __RubyOgreVector4_H__ */
