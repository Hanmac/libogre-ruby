#ifndef __RubyOgreVector2_H__
#define __RubyOgreVector2_H__

#include "main.hpp"
void Init_OgreVector2(VALUE rb_mOgre);
extern VALUE rb_cOgreVector2;

template <>
inline bool wrapable< Ogre::Vector2 >(const VALUE &obj)
{
	return rb_obj_is_kind_of(obj, rb_cOgreVector2) || (
	rb_respond_to(obj,rb_intern("x")) &&
	rb_respond_to(obj,rb_intern("y")));
}


template <>
inline VALUE wrap< Ogre::Vector2 >(Ogre::Vector2 *vector )
{
	return Data_Wrap_Struct(rb_cOgreVector2, NULL, free, vector);
}

template <>
inline Ogre::Vector2* wrap< Ogre::Vector2* >(const VALUE &vvector)
{
	if ( ! rb_obj_is_kind_of(vvector, rb_cOgreVector2) &&
		rb_respond_to(vvector,rb_intern("x")) &&
		rb_respond_to(vvector,rb_intern("y"))){
		 	Ogre::Vector2 *vector = new Ogre::Vector2;
		 	vector->x = NUM2DBL(rb_funcall(vvector,rb_intern("x"),0));
		 	vector->y = NUM2DBL(rb_funcall(vvector,rb_intern("y"),0));
		return vector;
	}else
		return unwrapPtr<Ogre::Vector2>(vvector,rb_cOgreVector2);
}
template <>
inline Ogre::Vector2 wrap< Ogre::Vector2 >(const VALUE &vvector)
{
	return *wrap< Ogre::Vector2* >(vvector);
}
#endif /* __RubyOgreVector2_H__ */
