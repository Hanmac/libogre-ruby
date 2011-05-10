#ifndef __RubyOgreRoot_H__
#define __RubyOgreRoot_H__

#include "main.hpp"

void Init_OgreRoot(VALUE rb_mOgre);
extern VALUE rb_cOgreRoot;
extern Ogre::Root *root;

template <>
inline VALUE wrap< Ogre::Root >(Ogre::Root *man )
{
	return Data_Wrap_Struct(rb_cOgreRoot, NULL, NULL, man);
}

template <>
inline Ogre::Root* wrap< Ogre::Root* >(const VALUE &vvector)
{
	if ( ! rb_obj_is_kind_of(vvector, rb_cOgreRoot) )
		return NULL;
	Ogre::Root *vector;
  Data_Get_Struct( vvector, Ogre::Root, vector);
	return vector;
}
#endif /* __RubyOgreVector3_H__ */
