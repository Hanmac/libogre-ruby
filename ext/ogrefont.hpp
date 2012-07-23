#ifndef __RubyOgreFont_H__
#define __RubyOgreFont_H__

#include "main.hpp"
#include <OgreFont.h>
#include <OgreFontManager.h>
void Init_OgreFont(VALUE rb_mOgre);
extern VALUE rb_cOgreFont;


template <>
VALUE wrap< Ogre::FontPtr >(const Ogre::FontPtr &font );

template <>
Ogre::FontPtr wrap< Ogre::FontPtr >(const VALUE &vfont);

#endif /* __RubyOgreFont_H__ */
