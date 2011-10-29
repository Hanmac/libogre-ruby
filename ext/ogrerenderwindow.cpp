#include "ogrerendertarget.hpp"
#include "ogrerenderwindow.hpp"
#define _self wrap<Ogre::RenderWindow*>(self)
VALUE rb_cOgreRenderWindow;

/*
*/
VALUE OgreRenderWindow_getName(VALUE self)
{
	return wrap(_self->getName());
}

void Init_OgreRenderWindow(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreRenderTarget = rb_define_class_under(rb_mOgre,"RenderTarget",rb_cObject);
#endif
	rb_cOgreRenderWindow = rb_define_class_under(rb_mOgre,"RenderWindow",rb_cOgreRenderTarget);

}
