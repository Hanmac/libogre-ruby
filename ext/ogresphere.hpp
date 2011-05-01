#ifndef __RubyOgreSphere_H__
#define __RubyOgreSphere_H__

#include "main.hpp"
void Init_OgreSphere(VALUE rb_mOgre);
extern VALUE rb_cOgreSphere;


template <>
inline VALUE wrap< Ogre::Sphere >(Ogre::Sphere *sphere )
{
	return Data_Wrap_Struct(rb_cOgreSphere, NULL, free, sphere);
}

template <>
inline Ogre::Sphere* wrap< Ogre::Sphere* >(const VALUE &vsphere)
{
	if ( ! rb_obj_is_kind_of(vsphere, rb_cOgreSphere) )
		return NULL;
	Ogre::Sphere *sphere;
  Data_Get_Struct( vsphere, Ogre::Sphere, sphere);
	return sphere;
}
#endif /* __RubyOgreSphere_H__ */
