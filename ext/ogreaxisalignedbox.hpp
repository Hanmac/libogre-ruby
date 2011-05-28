#ifndef __RubyOgreAxisAlignedBox_H__
#define __RubyOgreAxisAlignedBox_H__

#include "main.hpp"
void Init_OgreAxisAlignedBox(VALUE rb_mOgre);
extern VALUE rb_cOgreAxisAlignedBox;


template <>
inline VALUE wrap< Ogre::AxisAlignedBox >(Ogre::AxisAlignedBox *box )
{
	return Data_Wrap_Struct(rb_cOgreAxisAlignedBox, NULL, free, box);
}

template <>
inline Ogre::AxisAlignedBox* wrap< Ogre::AxisAlignedBox* >(const VALUE &vbox)
{
	if ( ! rb_obj_is_kind_of(vbox, rb_cOgreAxisAlignedBox) )
		return NULL;
	Ogre::AxisAlignedBox *box;
  Data_Get_Struct( vbox, Ogre::AxisAlignedBox, box);
	return box;
}
#endif /* __RubyOgreAxisAlignedBox_H__ */
