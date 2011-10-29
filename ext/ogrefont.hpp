#ifndef __RubyOgreFont_H__
#define __RubyOgreFont_H__

#include "main.hpp"
#include <OgreFont.h>
#include <OgreFontManager.h>
void Init_OgreFont(VALUE rb_mOgre);
extern VALUE rb_cOgreFont;


template <>
inline VALUE wrap< Ogre::Font >(Ogre::Font *font )
{
	return Data_Wrap_Struct(rb_cOgreFont, NULL, NULL, font);
}

template <>
inline Ogre::Font* wrap< Ogre::Font* >(const VALUE &vfont)
{
	if ( ! rb_obj_is_kind_of(vfont, rb_cOgreFont) )
		return NULL;
	Ogre::Font *font;
  Data_Get_Struct( vfont, Ogre::Font, font);
	return font;
}
#endif /* __RubyOgreFont_H__ */
