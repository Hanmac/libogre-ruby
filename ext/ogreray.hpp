#ifndef __RubyOgreRay_H__
#define __RubyOgreRay_H__

#include "main.hpp"
void Init_OgreRay(VALUE rb_mOgre);
extern VALUE rb_cOgreRay;

template <>
VALUE wrap< Ogre::Ray >(Ogre::Ray *ray );
#endif /* __RubyOgreRay_H__ */
