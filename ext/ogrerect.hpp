#ifndef __RubyOgreRect_H__
#define __RubyOgreRect_H__

#include "main.hpp"
void Init_OgreRect(VALUE rb_mOgre);
extern VALUE rb_cOgreRect;


template <>
VALUE wrap< Ogre::Rect >(Ogre::Rect *rect );

#endif /* __RubyOgreRect_H__ */
