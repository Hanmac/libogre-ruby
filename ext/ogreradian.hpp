#ifndef __RubyOgreRadian_H__
#define __RubyOgreRadian_H__

#include "main.hpp"
void Init_OgreRadian(VALUE rb_mOgre);

//#include "ogredegree.hpp"
template <>
inline VALUE wrap< Ogre::Radian >(Ogre::Radian *radian )
{
	return Data_Wrap_Struct(rb_cOgreRadian, NULL, free, radian);
}

template <>
inline Ogre::Radian* wrap< Ogre::Radian* >(const VALUE &vradian)
{
	if (rb_obj_is_kind_of(vradian, rb_cOgreRadian))
	{
		Ogre::Radian *radian;
		Data_Get_Struct( vradian, Ogre::Radian, radian);
		return radian;
	}else if(rb_obj_is_kind_of(vradian,rb_cOgreDegree)){
		return new Ogre::Radian(*rb_to_degree(vradian));
	}else if(rb_obj_is_kind_of(vradian,rb_cNumeric)){
		return new Ogre::Radian(NUM2DBL(vradian));
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreRadian),rb_obj_classname(vradian));
		return NULL;
	}
}
template <>
inline Ogre::Radian wrap< Ogre::Radian >(const VALUE &vradian)
{
	return *wrap< Ogre::Radian* >(vradian);
}
#endif /* __RubyOgreRadian_H__ */
