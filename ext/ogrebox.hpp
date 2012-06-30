#ifndef __RubyOgreBox_H__
#define __RubyOgreBox_H__

#include "main.hpp"
void Init_OgreBox(VALUE rb_mOgre);
extern VALUE rb_cOgreBox;


template <>
VALUE wrap< Ogre::Box >(Ogre::Box *box );

#endif /* __RubyOgreBox_H__ */
