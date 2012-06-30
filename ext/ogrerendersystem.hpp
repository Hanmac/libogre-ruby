#ifndef __RubyOgreRenderSystem_H__
#define __RubyOgreRenderSystem_H__

#include "main.hpp"
void Init_OgreRenderSystem(VALUE rb_mOgre);
extern VALUE rb_cOgreRenderSystem;


template <>
inline VALUE wrap< Ogre::RenderSystem >(Ogre::RenderSystem *system )
{
	if(system==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cOgreRenderSystem, NULL, NULL, system);
}

template <>
inline Ogre::RenderSystem* wrap< Ogre::RenderSystem* >(const VALUE &vsystem)
{
	return unwrapPtr<Ogre::RenderSystem>(vsystem, rb_cOgreRenderSystem);
}
#endif /* __RubyOgreRenderSystem_H__ */
