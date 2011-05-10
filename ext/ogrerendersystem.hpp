#ifndef __RubyOgreRenderSystem_H__
#define __RubyOgreRenderSystem_H__

#include "main.hpp"
void Init_OgreRenderSystem(VALUE rb_mOgre);
extern VALUE rb_cOgreRenderSystem;


template <>
inline VALUE wrap< Ogre::RenderSystem >(Ogre::RenderSystem *system )
{
	return Data_Wrap_Struct(rb_cOgreRenderSystem, NULL, NULL, system);
}

template <>
inline Ogre::RenderSystem* wrap< Ogre::RenderSystem* >(const VALUE &vsystem)
{
	if ( ! rb_obj_is_kind_of(vsystem, rb_cOgreRenderSystem) )
		return NULL;
	Ogre::RenderSystem *system;
  Data_Get_Struct( vsystem, Ogre::RenderSystem, system);
	return system;
}
#endif /* __RubyOgreRenderSystem_H__ */
