#ifndef __RubyOgreResourceManager_H__
#define __RubyOgreResourceManager_H__

#include "main.hpp"

#include <OgreFontManager.h>
#include <OgreMeshManager.h>
#include <OgreMaterialManager.h>
#include <OgreCompositorManager.h>
#include <OgreGpuProgramManager.h>
#include <OgreHighLevelGpuProgramManager.h>
#include <OgreSkeletonManager.h>
#include <OgreTextureManager.h>

void Init_OgreResourceManager(VALUE rb_mOgre);
extern VALUE rb_cOgreResourceManager;
extern VALUE rb_cOgreFontManager;
extern VALUE rb_cOgreMeshManager;
extern VALUE rb_cOgreMaterialManager;
extern VALUE rb_cOgreCompositorManager;
extern VALUE rb_cOgreGpuProgramManager;
extern VALUE rb_cOgreHighLevelGpuProgramManager;
extern VALUE rb_cOgreSkeletonManager;
extern VALUE rb_cOgreTextureManager;
template <>
inline VALUE wrap< Ogre::ResourceManager >(Ogre::ResourceManager *man )
{
	if(man == Ogre::FontManager::getSingletonPtr())
		return rb_funcall(rb_cOgreFontManager,rb_intern("instance"),0);
	if(man == Ogre::MeshManager::getSingletonPtr())
		return rb_funcall(rb_cOgreMeshManager,rb_intern("instance"),0);
	if(man == Ogre::MaterialManager::getSingletonPtr())
		return rb_funcall(rb_cOgreMaterialManager,rb_intern("instance"),0);
	if(man == Ogre::CompositorManager::getSingletonPtr())
		return rb_funcall(rb_cOgreCompositorManager,rb_intern("instance"),0);
	if(man == Ogre::GpuProgramManager::getSingletonPtr())
		return rb_funcall(rb_cOgreGpuProgramManager,rb_intern("instance"),0);
	if(man == Ogre::HighLevelGpuProgramManager::getSingletonPtr())
		return rb_funcall(rb_cOgreHighLevelGpuProgramManager,rb_intern("instance"),0);
	if(man == Ogre::SkeletonManager::getSingletonPtr())
		return rb_funcall(rb_cOgreSkeletonManager,rb_intern("instance"),0);
	if(man == Ogre::TextureManager::getSingletonPtr())
		return rb_funcall(rb_cOgreTextureManager,rb_intern("instance"),0);
	return Data_Wrap_Struct(rb_cOgreResourceManager, NULL, NULL, man);
}

template <>
inline VALUE wrap< Ogre::FontManager >(Ogre::FontManager *man )
{
	return Data_Wrap_Struct(rb_cOgreFontManager, NULL, NULL, man);
}

template <>
inline VALUE wrap< Ogre::MeshManager >(Ogre::MeshManager *man )
{
	return Data_Wrap_Struct(rb_cOgreMeshManager, NULL, NULL, man);
}

template <>
inline VALUE wrap< Ogre::MaterialManager >(Ogre::MaterialManager *man )
{
	if(man == NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cOgreMaterialManager, NULL, NULL, man);
}

template <>
inline VALUE wrap< Ogre::CompositorManager >(Ogre::CompositorManager *man )
{
	if(man == NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cOgreCompositorManager, NULL, NULL, man);
}

template <>
inline VALUE wrap< Ogre::GpuProgramManager >(Ogre::GpuProgramManager *man )
{
	if(man == NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cOgreGpuProgramManager, NULL, NULL, man);
}

template <>
inline VALUE wrap< Ogre::HighLevelGpuProgramManager >(Ogre::HighLevelGpuProgramManager *man )
{
	if(man == NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cOgreHighLevelGpuProgramManager, NULL, NULL, man);
}

template <>
inline VALUE wrap< Ogre::SkeletonManager >(Ogre::SkeletonManager *man )
{
	if(man == NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cOgreSkeletonManager, NULL, NULL, man);
}

template <>
inline VALUE wrap< Ogre::TextureManager >(Ogre::TextureManager *man )
{
	if(man == NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cOgreTextureManager, NULL, NULL, man);
}

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
