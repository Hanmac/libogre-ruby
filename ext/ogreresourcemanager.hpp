#ifndef __RubyOgreResourceManager_H__
#define __RubyOgreResourceManager_H__

#include "main.hpp"
void Init_OgreResourceManager(VALUE rb_mOgre);
extern VALUE rb_cOgreResourceManager;

/*
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
*/

template <>
inline Ogre::ResourceManager* wrap< Ogre::ResourceManager* >(const VALUE &vvector)
{
	if ( ! rb_obj_is_kind_of(vvector, rb_cOgreResourceManager) )
		return NULL;
	Ogre::ResourceManager *vector;
  Data_Get_Struct( vvector, Ogre::ResourceManager, vector);
	return vector;
}
#endif /* __RubyOgreVector3_H__ */
