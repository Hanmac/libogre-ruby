#ifndef __RubyOgreRenderTarget_H__
#define __RubyOgreRenderTarget_H__

#include "main.hpp"
void Init_OgreRenderTarget(VALUE rb_mOgre);
extern VALUE rb_cOgreRenderTarget;


template <>
inline VALUE wrap< Ogre::RenderTarget >(Ogre::RenderTarget *target )
{
	return Data_Wrap_Struct(rb_cOgreRenderTarget, NULL, NULL, target);
}

template <>
inline Ogre::RenderTarget* wrap< Ogre::RenderTarget* >(const VALUE &vtarget)
{
	if ( ! rb_obj_is_kind_of(vtarget, rb_cOgreRenderTarget) )
		return NULL;
	Ogre::RenderTarget *target;
  Data_Get_Struct( vtarget, Ogre::RenderTarget, target);
	return target;
}
#endif /* __RubyOgreRenderTarget_H__ */
