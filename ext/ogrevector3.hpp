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
inline VALUE wrap< Ogre::Vector3 >(Ogre::Vector3 vector )
{
	Ogre::Vector3 *temp = new Ogre::Vector3(vector);
	return wrap(temp);
}


template <>
inline Ogre::Vector3* wrap< Ogre::Vector3* >(const VALUE &vvector)
{
	if ( ! rb_obj_is_kind_of(vvector, rb_cOgreVector3) )
		return NULL;
	Ogre::Vector3 *vector;
  Data_Get_Struct( vvector, Ogre::Vector3, vector);
	return vector;
}
#endif /* __RubyOgreVector3_H__ */
