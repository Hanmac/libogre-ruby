#ifndef __RubyOgreTechnique_H__
#define __RubyOgreTechnique_H__

#include "main.hpp"
void Init_OgreTechnique(VALUE rb_mOgre);
extern VALUE rb_cOgreTechnique;


template <>
inline VALUE wrap< Ogre::Technique >(Ogre::Technique *technique )
{
	return Data_Wrap_Struct(rb_cOgreTechnique, NULL, NULL, technique);
}

template <>
inline Ogre::Technique* wrap< Ogre::Technique* >(const VALUE &vtechnique)
{
	if ( ! rb_obj_is_kind_of(vtechnique, rb_cOgreTechnique) )
		return NULL;
	Ogre::Technique *technique;
  Data_Get_Struct( vtechnique, Ogre::Technique, technique);
	return technique;
}
#endif /* __RubyOgreTechnique_H__ */
