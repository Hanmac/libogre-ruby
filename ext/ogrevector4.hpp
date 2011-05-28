#ifndef __RubyOgreVector4_H__
#define __RubyOgreVector4_H__

#include "main.hpp"
void Init_OgreVector4(VALUE rb_mOgre);
extern VALUE rb_cOgreVector4;

#include "ogrevector3.hpp"
template <>
inline VALUE wrap< Ogre::Vector4 >(Ogre::Vector4 *vector )
{
	return Data_Wrap_Struct(rb_cOgreVector4, NULL, free, vector);
}

template <>
inline Ogre::Vector4* wrap< Ogre::Vector4* >(const VALUE &vvector)
{
	if (rb_obj_is_kind_of(vvector, rb_cOgreVector4)){
		Ogre::Vector4 *vector;
		Data_Get_Struct( vvector, Ogre::Vector4, vector);
		return vector;
	}else
	{
		Ogre::Vector4 *vector = new Ogre::Vector4;
		if(rb_obj_is_kind_of(vvector, rb_cNumeric))
			*vector = NUM2DBL(vvector);
		else if(rb_respond_to(vvector,rb_intern("to_f")))
			*vector = NUM2DBL(rb_funcall(vvector,rb_intern("to_f"),0));
		else if(rb_respond_to(vvector,rb_intern("to_i")))
			*vector = NUM2DBL(rb_funcall(vvector,rb_intern("to_i"),0));
		else if (rb_obj_is_kind_of(vvector, rb_cOgreVector3)){
			*vector = *wrap<Ogre::Vector3*>(vvector);
		}else if(rb_respond_to(vvector,rb_intern("x")) && 
		 rb_respond_to(vvector,rb_intern("y")) &&
		 rb_respond_to(vvector,rb_intern("z"))){
		 	if(rb_respond_to(vvector,rb_intern("w"))){
			 	vector->x = NUM2DBL(rb_funcall(vvector,rb_intern("x"),0));
			 	vector->y = NUM2DBL(rb_funcall(vvector,rb_intern("y"),0));
			 	vector->z = NUM2DBL(rb_funcall(vvector,rb_intern("z"),0));		 	
			 	vector->w = NUM2DBL(rb_funcall(vvector,rb_intern("w"),0));
			}else
				*vector = *wrap<Ogre::Vector3*>(vvector);
		}else
			rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector4),rb_obj_classname(vvector));
	 	return vector;
	}
}
#endif /* __RubyOgreVector4_H__ */
