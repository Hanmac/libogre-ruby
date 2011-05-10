#include "ogrerendersystem.hpp"

#define _self wrap<Ogre::RenderSystem*>(self)
VALUE rb_cOgreRenderSystem;


/*
*/
VALUE OgreRenderSystem_getName(VALUE self)
{
	return wrap(_self->getName());
}

void Init_OgreRenderSystem(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreRenderSystem = rb_define_class_under(rb_mOgre,"RenderSystem",rb_cObject);
	rb_undef_alloc_func(rb_cOgreRenderSystem);

	rb_define_method(rb_cOgreRenderSystem,"name",RUBY_METHOD_FUNC(OgreRenderSystem_getName),0);
}
