#ifndef __RubyOgreRadian_H__
#define __RubyOgreRadian_H__

#include "main.hpp"
extern VALUE rb_cOgreRadian;
void Init_OgreRadian(VALUE rb_mOgre);

template <>
VALUE wrap< Ogre::Radian >(Ogre::Radian *radian );

template <>
Ogre::Radian wrap< Ogre::Radian >(const VALUE &vradian);

#endif /* __RubyOgreRadian_H__ */
