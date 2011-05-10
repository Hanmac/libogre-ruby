#include "ogrerendertarget.hpp"

#define _self wrap<Ogre::RenderTarget*>(self)
VALUE rb_cOgreRenderTarget;

void Init_OgreRenderTarget(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreRenderTarget = rb_define_class_under(rb_mOgre,"RenderTarget",rb_cObject);
	rb_undef_alloc_func(rb_cOgreRenderTarget);

}
