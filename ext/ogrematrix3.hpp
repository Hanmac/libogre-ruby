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
	if ( ! rb_obj_is_kind_of(vmatrix, rb_cOgreMatrix3) )
		return NULL;
	Ogre::Matrix3 *matrix;
  Data_Get_Struct( vmatrix, Ogre::Matrix3, matrix);
	return matrix;
}
#endif /* __RubyOgreMatrix3_H__ */
