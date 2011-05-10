#ifndef __RubyOgreLight_H__
#define __RubyOgreLight_H__

#include "main.hpp"
void Init_OgreLight(VALUE rb_mOgre);
extern VALUE rb_cOgreLight;


template <>
inline VALUE wrap< Ogre::Light >(Ogre::Light *light )
{
	return Data_Wrap_Struct(rb_cOgreLight, NULL, NULL, light);
}

template <>
inline Ogre::Light* wrap< Ogre::Light* >(const VALUE &vlight)
{
	if ( ! rb_obj_is_kind_of(vlight, rb_cOgreLight) )
		return NULL;
	Ogre::Light *light;
  Data_Get_Struct( vlight, Ogre::Light, light);
	return light;
}
#endif /* __RubyOgreLight_H__ */
