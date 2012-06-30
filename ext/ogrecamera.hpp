#ifndef __RubyOgreCamera_H__
#define __RubyOgreCamera_H__

#include "main.hpp"
void Init_OgreCamera(VALUE rb_mOgre);
extern VALUE rb_cOgreCamera;

VALUE wrap(const Ogre::Camera *camera );
#endif /* __RubyOgreCamera_H__ */
