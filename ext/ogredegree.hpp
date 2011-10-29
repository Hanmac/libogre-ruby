#ifndef __RubyOgreDegree_H__
#define __RubyOgreDegree_H__

#include "main.hpp"
void Init_OgreDegree(VALUE rb_mOgre);


//#include "ogreradian.hpp"
template <>
inline VALUE wrap< Ogre::Degree >(Ogre::Degree *degree )
{
	return Data_Wrap_Struct(rb_cOgreDegree, NULL, free, degree);
}

template <>
inline Ogre::Degree* wrap< Ogre::Degree* >(const VALUE &vdegree)
{
	if(rb_obj_is_kind_of(vdegree, rb_cOgreDegree))
	{
		Ogre::Degree *degree;
		Data_Get_Struct( vdegree, Ogre::Degree, degree);
		return degree;
	}else if(rb_obj_is_kind_of(vdegree,rb_cOgreRadian)){
		return new Ogre::Degree(*rb_to_radian(vdegree));
	}else if(rb_obj_is_kind_of(vdegree,rb_cNumeric)){
		return new Ogre::Degree(NUM2DBL(vdegree));
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreDegree),rb_obj_classname(vdegree));
		return NULL;
	}
}
#endif /* __RubyOgreDegree_H__ */
