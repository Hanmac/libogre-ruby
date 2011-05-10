#include "ogrerendertarget.hpp"
#include "ogrerenderwindow.hpp"
#define _self wrap<Ogre::RenderWindow*>(self)
VALUE rb_cOgreRenderWindow;

/*
getName
virtual unsigned int 	getWidth (void) const
virtual unsigned int 	getHeight (void) const
virtual unsigned int 	getColourDepth (void) const 
*/

/*

*/
VALUE OgreRenderWindow_getName(VALUE self)
{
	return wrap(_self->getName());
}
/*

*/
VALUE OgreRenderWindow_getWidth(VALUE self)
{
	return UINT2NUM(_self->getWidth());
}
/*

*/
VALUE OgreRenderWindow_getHeight(VALUE self)
{
	return UINT2NUM(_self->getHeight());
}
/*

*/
VALUE OgreRenderWindow_getColorDepth(VALUE self)
{
	return UINT2NUM(_self->getColourDepth());
}

void Init_OgreRenderWindow(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreRenderTarget = rb_define_class_under(rb_mOgre,"RenderTarget",rb_cObject);
#endif
	rb_cOgreRenderWindow = rb_define_class_under(rb_mOgre,"RenderWindow",rb_cOgreRenderTarget);

	rb_define_method(rb_cOgreRenderWindow,"name",RUBY_METHOD_FUNC(OgreRenderWindow_getName),0);
	rb_define_method(rb_cOgreRenderWindow,"width",RUBY_METHOD_FUNC(OgreRenderWindow_getWidth),0);
	rb_define_method(rb_cOgreRenderWindow,"height",RUBY_METHOD_FUNC(OgreRenderWindow_getHeight),0);
	rb_define_method(rb_cOgreRenderWindow,"colordepth",RUBY_METHOD_FUNC(OgreRenderWindow_getColorDepth),0);
}
