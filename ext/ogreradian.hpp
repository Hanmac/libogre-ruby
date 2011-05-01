#ifndef __RubyOgreRadian_H__
#define __RubyOgreRadian_H__

#include "main.hpp"
void Init_OgreRadian(VALUE rb_mOgre);
extern VALUE rb_cOgreRadian;


template <>
inline VALUE wrap< Ogre::Radian >(Ogre::Radian *radian )
{
	return Data_Wrap_Struct(rb_cOgreRadian, NULL, free, radian);
}

template <>
inline Ogre::Radian* wrap< Ogre::Radian* >(const VALUE &vradian)
{
	if ( ! rb_obj_is_kind_of(vradian, rb_cOgreRadian) )
		return NULL;
	Ogre::Radian *radian;
  Data_Get_Struct( vradian, Ogre::Radian, radian);
	return radian;
}
#endif /* __RubyOgreRadian_H__ */
