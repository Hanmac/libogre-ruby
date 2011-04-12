#ifndef __RubyOgreBox_H__
#define __RubyOgreBox_H__

#include "main.hpp"
void Init_OgreBox(VALUE rb_mOgre);
extern VALUE rb_cOgreBox;


template <>
inline VALUE wrap< Ogre::Box >(Ogre::Box *box )
{
	return Data_Wrap_Struct(rb_cOgreBox, NULL, free, box);
}

template <>
inline Ogre::Box* wrap< Ogre::Box* >(const VALUE &vbox)
{
	if ( ! rb_obj_is_kind_of(vbox, rb_cOgreBox) )
		return NULL;
	Ogre::Box *box;
  Data_Get_Struct( vbox, Ogre::Box, box);
	return box;
}
#endif /* __RubyOgreBox_H__ */
