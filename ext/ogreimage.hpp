#ifndef __RubyOgreImage_H__
#define __RubyOgreImage_H__

#include "main.hpp"
void Init_OgreImage(VALUE rb_mOgre);
extern VALUE rb_cOgreImage;

template <>
VALUE wrap< Ogre::Image >(Ogre::Image *image );
#endif /* __RubyOgreImage_H__ */
