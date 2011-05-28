#ifndef __RubyOgreVector3_H__
#define __RubyOgreVector3_H__

#include "main.hpp"
void Init_OgreVector3(VALUE rb_mOgre);
extern VALUE rb_cOgreVector3;


template <>
inline VALUE wrap< Ogre::Vector3 >(Ogre::Vector3 *vector )
{
	return Data_Wrap_Struct(rb_cOgreVector3, NULL, free, vector);
}

template <>
inline Ogre::Vector3* wrap< Ogre::Vector3* >(const VALUE &vvector)
{
	if (rb_obj_is_kind_of(vvector, rb_cOgreVector3)){
		Ogre::Vector3 *vector;
		Data_Get_Struct( vvector, Ogre::Vector3, vector);
		return vector;
	}else if(rb_respond_to(vvector,rb_intern("x")) && 
	 rb_respond_to(vvector,rb_intern("y")) &&
	 rb_respond_to(vvector,rb_intern("z"))){
	 	Ogre::Vector3 *vector = new Ogre::Vector3;
	 	vector->x = NUM2DBL(rb_funcall(vvector,rb_intern("x"),0));
	 	vector->y = NUM2DBL(rb_funcall(vvector,rb_intern("y"),0));
	 	vector->z = NUM2DBL(rb_funcall(vvector,rb_intern("z"),0));
	 	return vector;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(vvector));
		return NULL;
	}
}
#endif /* __RubyOgreVector3_H__ */
