#ifndef __RubyOgreMatrix3_H__
#define __RubyOgreMatrix3_H__

#include "main.hpp"
void Init_OgreMatrix3(VALUE rb_mOgre);
extern VALUE rb_cOgreMatrix3;


template <>
inline VALUE wrap< Ogre::Matrix3 >(Ogre::Matrix3 *matrix )
{
	return Data_Wrap_Struct(rb_cOgreMatrix3, NULL, free, matrix);
}

template <>
inline Ogre::Matrix3* wrap< Ogre::Matrix3* >(const VALUE &vmatrix)
{
	return unwrapPtr<Ogre::Matrix3>(vmatrix, rb_cOgreMatrix3);
}

template <>
inline Ogre::Matrix3 wrap< Ogre::Matrix3 >(const VALUE &vmatrix)
{
	return *wrap< Ogre::Matrix3* >(vmatrix);
}
#endif /* __RubyOgreMatrix3_H__ */
