#ifndef __RubyOgreMatrix4_H__
#define __RubyOgreMatrix4_H__

#include "main.hpp"
void Init_OgreMatrix4(VALUE rb_mOgre);
extern VALUE rb_cOgreMatrix4;


template <>
inline VALUE wrap< Ogre::Matrix4 >(Ogre::Matrix4 *matrix )
{
	return Data_Wrap_Struct(rb_cOgreMatrix4, NULL, free, matrix);
}

template <>
inline Ogre::Matrix4* wrap< Ogre::Matrix4* >(const VALUE &vmatrix)
{
	if ( ! rb_obj_is_kind_of(vmatrix, rb_cOgreMatrix4) )
		return NULL;
	Ogre::Matrix4 *matrix;
  Data_Get_Struct( vmatrix, Ogre::Matrix4, matrix);
	return matrix;
}
#endif /* __RubyOgreMatrix4_H__ */
