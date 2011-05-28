#ifndef __RubyOgreQuaternion_H__
#define __RubyOgreQuaternion_H__

#include "main.hpp"
void Init_OgreQuaternion(VALUE rb_mOgre);
extern VALUE rb_cOgreQuaternion;


template <>
inline VALUE wrap< Ogre::Quaternion >(Ogre::Quaternion *matrix )
{
	return Data_Wrap_Struct(rb_cOgreQuaternion, NULL, free, matrix);
}

template <>
inline Ogre::Quaternion* wrap< Ogre::Quaternion* >(const VALUE &vmatrix)
{
	if ( ! rb_obj_is_kind_of(vmatrix, rb_cOgreQuaternion) )
		return NULL;
	Ogre::Quaternion *matrix;
  Data_Get_Struct( vmatrix, Ogre::Quaternion, matrix);
	return matrix;
}
#endif /* __RubyOgreQuaternion_H__ */
