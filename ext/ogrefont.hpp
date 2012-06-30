#ifndef __RubyOgreFont_H__
#define __RubyOgreFont_H__

#include "main.hpp"
#include <OgreFont.h>
#include <OgreFontManager.h>
void Init_OgreFont(VALUE rb_mOgre);
extern VALUE rb_cOgreFont;


template <>
VALUE wrap< Ogre::FontPtr >(Ogre::FontPtr *font );

template <>
Ogre::Font* wrap< Ogre::Font* >(const VALUE &vfont);

#endif /* __RubyOgreFont_H__ */
