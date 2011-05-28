#ifndef __RubyOgrePlaneBoundedVolume_H__
#define __RubyOgrePlaneBoundedVolume_H__

#include "main.hpp"
void Init_OgrePlaneBoundedVolume(VALUE rb_mOgre);
extern VALUE rb_cOgrePlaneBoundedVolume;


template <>
inline VALUE wrap< Ogre::PlaneBoundedVolume >(Ogre::PlaneBoundedVolume *box )
{
	return Data_Wrap_Struct(rb_cOgrePlaneBoundedVolume, NULL, free, box);
}

template <>
inline Ogre::PlaneBoundedVolume* wrap< Ogre::PlaneBoundedVolume* >(const VALUE &vbox)
{
	if ( ! rb_obj_is_kind_of(vbox, rb_cOgrePlaneBoundedVolume) )
		return NULL;
	Ogre::PlaneBoundedVolume *box;
  Data_Get_Struct( vbox, Ogre::PlaneBoundedVolume, box);
	return box;
}
#endif /* __RubyOgrePlaneBoundedVolume_H__ */
