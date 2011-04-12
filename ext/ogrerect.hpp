#ifndef __RubyOgreRect_H__
#define __RubyOgreRect_H__

#include "main.hpp"
void Init_OgreRect(VALUE rb_mOgre);
extern VALUE rb_cOgreRect;


template <>
inline VALUE wrap< Ogre::Rect >(Ogre::Rect *rect )
{
	return Data_Wrap_Struct(rb_cOgreRect, NULL, free, rect);
}

template <>
inline Ogre::Rect* wrap< Ogre::Rect* >(const VALUE &vrect)
{
	if ( ! rb_obj_is_kind_of(vrect, rb_cOgreRect) )
		return NULL;
	Ogre::Rect *rect;
  Data_Get_Struct( vrect, Ogre::Rect, rect);
	return rect;
}
#endif /* __RubyOgreRect_H__ */
