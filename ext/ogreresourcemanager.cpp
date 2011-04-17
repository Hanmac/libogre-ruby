#include "ogreresourcemanager.hpp"
#define _self wrap<Ogre::ResourceManager*>(self)
VALUE rb_cOgreResourceManager;
/*

*/
VALUE OgreResourceManager_remove(VALUE self,VALUE name)
{
	_self->remove(rb_string_value_cstr(&name));
	return self;
}
/*

*/
VALUE OgreResourceManager_resourceExists(VALUE self,VALUE name)
{
	return _self->resourceExists(rb_string_value_cstr(&name)) ? Qtrue : Qfalse;
}
/*

*/
VALUE OgreResourceManager_unload(VALUE self,VALUE name)
{
	_self->unload(rb_string_value_cstr(&name));
	return self;
}
/*

*/
VALUE OgreResourceManager_getResourceType(VALUE self)
{
	return wrap(_self->getResourceType());
}
/*

*/
VALUE OgreResourceManager_getScriptPatterns(VALUE self)
{
	return wrap(_self->getScriptPatterns());
}
/*

*/
VALUE OgreResourceManager_getVerbose(VALUE self)
{
	return _self->getVerbose() ? Qtrue : Qfalse;
}
/*

*/
VALUE OgreResourceManager_setVerbose(VALUE self,VALUE val)
{
	_self->setVerbose(RTEST(val));
	return val;
}

void Init_OgreResourceManager(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreResourceManager = rb_define_class_under(rb_mOgre,"ResourceManager",rb_cObject);
	rb_undef_alloc_func(rb_cOgreResourceManager);
//	rb_define_alloc_func(rb_cOgreResourceManager,OgreResourceManager_alloc);

	rb_define_method(rb_cOgreResourceManager,"remove",RUBY_METHOD_FUNC(OgreResourceManager_remove),1);
	rb_define_method(rb_cOgreResourceManager,"resourceExists?",RUBY_METHOD_FUNC(OgreResourceManager_resourceExists),1);
	rb_define_method(rb_cOgreResourceManager,"unload",RUBY_METHOD_FUNC(OgreResourceManager_unload),1);
	
	rb_define_method(rb_cOgreResourceManager,"resourceType",RUBY_METHOD_FUNC(OgreResourceManager_getResourceType),0);
	rb_define_method(rb_cOgreResourceManager,"scriptPatterns",RUBY_METHOD_FUNC(OgreResourceManager_getScriptPatterns),0);
	
	rb_define_method(rb_cOgreResourceManager,"verbose",RUBY_METHOD_FUNC(OgreResourceManager_getVerbose),0);
	rb_define_method(rb_cOgreResourceManager,"verbose=",RUBY_METHOD_FUNC(OgreResourceManager_setVerbose),1);
}
