#ifndef __RubyOgrePlane_H__
#define __RubyOgrePlane_H__

#include "main.hpp"
void Init_OgrePlane(VALUE rb_mOgre);
extern VALUE rb_cOgrePlane;


template <>
inline VALUE wrap< Ogre::Plane >(Ogre::Plane *plane )
{
	return Data_Wrap_Struct(rb_cOgrePlane, NULL, free, plane);
}

template <>
inline VALUE wrap< Ogre::Plane::Side >(const Ogre::Plane::Side &side )
{
	ID result;
	switch(side){
	case Ogre::Plane::NO_SIDE:
		result = rb_intern("no_side");
		break;
	case Ogre::Plane::POSITIVE_SIDE:
		result = rb_intern("positive_side");
		break;
	case Ogre::Plane::NEGATIVE_SIDE:
		result = rb_intern("negative_side");
		break;
	case Ogre::Plane::BOTH_SIDE:
		result = rb_intern("both_side");
		break;
	}
	return ID2SYM(result);
}


template <>
inline Ogre::Plane* wrap< Ogre::Plane* >(const VALUE &vplane)
{
	if ( ! rb_obj_is_kind_of(vplane, rb_cOgrePlane) )
		return NULL;
	Ogre::Plane *plane;
	Data_Get_Struct( vplane, Ogre::Plane, plane);
	return plane;
}
#endif /* __RubyOgrePlane_H__ */
