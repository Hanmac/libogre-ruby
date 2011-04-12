#ifndef __RubyOgreDegree_H__
#define __RubyOgreDegree_H__

#include "main.hpp"
void Init_OgreDegree(VALUE rb_mOgre);
extern VALUE rb_cOgreDegree;


template <>
inline VALUE wrap< Ogre::Degree >(Ogre::Degree *degree )
{
	return Data_Wrap_Struct(rb_cOgreDegree, NULL, free, degree);
}

template <>
inline VALUE wrap< Ogre::Degree >(Ogre::Degree degree )
{
	Ogre::Degree *temp = new Ogre::Degree(degree);
	return wrap(temp);
}


template <>
inline Ogre::Degree* wrap< Ogre::Degree* >(const VALUE &vdegree)
{
	if ( ! rb_obj_is_kind_of(vdegree, rb_cOgreDegree) )
		return NULL;
	Ogre::Degree *degree;
  Data_Get_Struct( vdegree, Ogre::Degree, degree);
	return degree;
}
#endif /* __RubyOgreDegree_H__ */
