#ifndef __RubyOgreColor_H__
#define __RubyOgreColor_H__

#include "main.hpp"
void Init_OgreColor(VALUE rb_mOgre);
extern VALUE rb_cOgreColor;

template <>
VALUE wrap< Ogre::ColourValue >(Ogre::ColourValue *color );

template <>
Ogre::ColourValue* wrap< Ogre::ColourValue* >(const VALUE &vcolor);

template <>
Ogre::ColourValue wrap< Ogre::ColourValue >(const VALUE &vcolor);

#endif /* __RubyOgreColor_H__ */
