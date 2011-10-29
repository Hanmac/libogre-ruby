#ifndef __RubyOgrePlane_H__
#define __RubyOgrePlane_H__

#include "main.hpp"
#include "ogremovableplane.hpp"
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
inline Ogre::Plane::Side wrap< Ogre::Plane::Side >(const VALUE &arg)
{
	ID id = rb_to_id(arg);
	if(id==rb_intern("no_side"))
		return Ogre::Plane::NO_SIDE;
	else if(id==rb_intern("positive_side"))
		return Ogre::Plane::POSITIVE_SIDE;
	else if(id==rb_intern("negative_side"))
		return Ogre::Plane::NEGATIVE_SIDE;
	else if(id==rb_intern("both_side"))
		return Ogre::Plane::BOTH_SIDE;
	else
		return Ogre::Plane::NO_SIDE;
}


template <>
inline Ogre::Plane* wrap< Ogre::Plane* >(const VALUE &vplane)
{
	if ( ! rb_obj_is_kind_of(vplane, rb_cOgrePlane) )
		return NULL;
	if (rb_obj_is_kind_of(vplane, rb_cOgreMovablePlane) )
		return wrap<Ogre::MovablePlane*>(vplane);
	Ogre::Plane *plane;
	Data_Get_Struct( vplane, Ogre::Plane, plane);
	return plane;
}
#endif /* __RubyOgrePlane_H__ */
