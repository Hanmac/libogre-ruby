#ifndef __RubyOgreColor_H__
#define __RubyOgreColor_H__

#include "main.hpp"
void Init_OgreColor(VALUE rb_mOgre);
extern VALUE rb_cOgreColor;


template <>
inline VALUE wrap< Ogre::ColourValue >(Ogre::ColourValue *color )
{
	return Data_Wrap_Struct(rb_cOgreColor, NULL, free, color);
}

template <>
inline Ogre::ColourValue* wrap< Ogre::ColourValue* >(const VALUE &vcolor)
{
	if ( ! rb_obj_is_kind_of(vcolor, rb_cOgreColor) )
		return NULL;
	Ogre::ColourValue *color;
  Data_Get_Struct( vcolor, Ogre::ColourValue, color);
	return color;
}
#endif /* __RubyOgreColor_H__ */
