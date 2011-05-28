#ifndef __RubyOgreRay_H__
#define __RubyOgreRay_H__

#include "main.hpp"
void Init_OgreRay(VALUE rb_mOgre);
extern VALUE rb_cOgreRay;


template <>
inline VALUE wrap< Ogre::Ray >(Ogre::Ray *ray )
{
	return Data_Wrap_Struct(rb_cOgreRay, NULL, free, ray);
}

template <>
inline Ogre::Ray* wrap< Ogre::Ray* >(const VALUE &vray)
{
	if ( ! rb_obj_is_kind_of(vray, rb_cOgreRay) )
		return NULL;
	Ogre::Ray *ray;
  Data_Get_Struct( vray, Ogre::Ray, ray);
	return ray;
}
#endif /* __RubyOgreRay_H__ */
