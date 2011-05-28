#ifndef __RubyOgreMaterial_H__
#define __RubyOgreMaterial_H__

#include "main.hpp"
void Init_OgreMaterial(VALUE rb_mOgre);
extern VALUE rb_cOgreMaterial;


template <>
inline VALUE wrap< Ogre::Material >(Ogre::Material *material )
{
	return Data_Wrap_Struct(rb_cOgreMaterial, NULL, NULL, material);
}

template <>
inline Ogre::Material* wrap< Ogre::Material* >(const VALUE &vmaterial)
{
	if ( ! rb_obj_is_kind_of(vmaterial, rb_cOgreMaterial) )
		return NULL;
	Ogre::Material *material;
  Data_Get_Struct( vmaterial, Ogre::Material, material);
	return material;
}
#endif /* __RubyOgreMaterial_H__ */
