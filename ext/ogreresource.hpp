#ifndef __RubyOgreResource_H__
#define __RubyOgreResource_H__

#include "main.hpp"
void Init_OgreResource(VALUE rb_mOgre);
extern VALUE rb_cOgreResource;

#include "ogrematerial.hpp"
#include "ogremesh.hpp"
template <>
inline VALUE wrap< Ogre::Resource >(Ogre::Resource *resource )
{
	Ogre::Material* material = dynamic_cast<Ogre::Material*>(resource);
	if(material != NULL)
		return wrap(material);
	
	Ogre::Mesh* mesh = dynamic_cast<Ogre::Mesh*>(resource);
	if(mesh != NULL)
		return wrap(mesh);
	
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


template <>
inline Ogre::ResourceManager* wrap< Ogre::ResourceManager* >(const VALUE &vclass)
{
	if(vclass==rb_cOgreMaterial)
		return Ogre::MaterialManager::getSingletonPtr();
	if(vclass==rb_cOgreMesh)
		return Ogre::MeshManager::getSingletonPtr();
	rb_raise(rb_eTypeError,"%s is not a valid Ogre::ResourceManager!",rb_class2name(vclass));
	return NULL;
}

#endif /* __RubyOgreResource_H__ */
