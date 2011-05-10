#ifndef __RubyOgreResource_H__
#define __RubyOgreResource_H__

#include "main.hpp"
void Init_OgreResource(VALUE rb_mOgre);
extern VALUE rb_cOgreResource;


template <>
inline VALUE wrap< Ogre::Resource >(Ogre::Resource *resource )
{
	return Data_Wrap_Struct(rb_cOgreResource, NULL, NULL, resource);
}

template <>
inline Ogre::Resource* wrap< Ogre::Resource* >(const VALUE &vresource)
{
	if ( ! rb_obj_is_kind_of(vresource, rb_cOgreResource) )
		return NULL;
	Ogre::Resource *resource;
  Data_Get_Struct( vresource, Ogre::Resource, resource);
	return resource;
}
#endif /* __RubyOgreResource_H__ */
