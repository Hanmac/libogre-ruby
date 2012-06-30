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
	return unwrapPtr<Ogre::AxisAlignedBox>(vbox, rb_cOgreAxisAlignedBox);
}

template <>
inline Ogre::AxisAlignedBox wrap< Ogre::AxisAlignedBox >(const VALUE &vbox)
{
	return *wrap< Ogre::AxisAlignedBox* >(vbox);
}

#endif /* __RubyOgreAxisAlignedBox_H__ */
