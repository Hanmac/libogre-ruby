#ifndef __RubyOgreVector2_H__
#define __RubyOgreVector2_H__

#include "main.hpp"
void Init_OgreVector2(VALUE rb_mOgre);
extern VALUE rb_cOgreVector2;


template <>
inline VALUE wrap< Ogre::Vector2 >(Ogre::Vector2 *vector )
{
	return Data_Wrap_Struct(rb_cOgreVector2, NULL, free, vector);
}

template <>
inline Ogre::Vector2* wrap< Ogre::Vector2* >(const VALUE &vvector)
{
	if ( ! rb_obj_is_kind_of(vvector, rb_cOgreVector2) )
		return NULL;
	Ogre::Vector2 *vector;
  Data_Get_Struct( vvector, Ogre::Vector2, vector);
	return vector;
}
template <>
inline Ogre::Vector2 wrap< Ogre::Vector2 >(const VALUE &vvector)
{
	return *wrap< Ogre::Vector2* >(vvector);
}
#endif /* __RubyOgreVector2_H__ */
