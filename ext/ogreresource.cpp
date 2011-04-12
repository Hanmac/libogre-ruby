#include "ogreresource.hpp"

#define _self wrap<Ogre::Resource*>(self)
VALUE rb_cOgreResource;



void Init_OgreResource(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);
	rb_undef_alloc_func(rb_cOgreResource);
}
