#include "ogreresource.hpp"
#include "ogreresourcemanager.hpp"
#define _self wrap<Ogre::Resource*>(self)
VALUE rb_cOgreResource;

/*

*/
VALUE OgreResource_getGroup(VALUE self)
{
	return wrap(_self->getGroup());
}
/*

*/
VALUE OgreResource_getOrigin(VALUE self)
{
	return wrap(_self->getOrigin());
}
/*

*/
VALUE OgreResource_getSize(VALUE self)
{
	return ULONG2NUM(_self->getSize());
}
/*

*/
VALUE OgreResource_getName(VALUE self)
{
	return wrap(_self->getName());
}
/*

*/
VALUE OgreResource_isPrepared(VALUE self)
{
	return _self->isPrepared() ? Qtrue : Qfalse;
}
/*

*/
VALUE OgreResource_isLoaded(VALUE self)
{
	return _self->isLoaded() ? Qtrue : Qfalse;
}
/*

*/
VALUE OgreResource_isLoading(VALUE self)
{
	return _self->isLoading() ? Qtrue : Qfalse;
}
/*

*/
VALUE OgreResource_prepare(int argc,VALUE *argv,VALUE self)
{
	VALUE backgroundThread;
	rb_scan_args(argc, argv, "01",&backgroundThread);
	if(!NIL_P(backgroundThread))
		backgroundThread = Qfalse;
	_self->prepare(RTEST(backgroundThread));
	return self;
}
/*

*/
VALUE OgreResource_load(int argc,VALUE *argv,VALUE self)
{
	VALUE backgroundThread;
	rb_scan_args(argc, argv, "01",&backgroundThread);
	if(!NIL_P(backgroundThread))
		backgroundThread = Qfalse;
	_self->load(RTEST(backgroundThread));
	return self;
}
/*

*/
VALUE OgreResource_getStateCount(VALUE self)
{
	return ULONG2NUM(_self->getStateCount());
}
/*

*/
VALUE OgreResource_isBackgroundLoaded(VALUE self)
{
	return _self->isBackgroundLoaded() ? Qtrue : Qfalse;
}
/*

*/
VALUE OgreResource_setBackgroundLoaded(VALUE self,VALUE val)
{
	_self->setBackgroundLoaded(RTEST(val));
	return val;
}
/*

prepare (bool backgroundThread=false)
 	Prepares the resource for load, if it is not already.
virtual void 	load (bool backgroundThread=false)
 	Loads the resource, if it is not already.
virtual void 	reload (void)
 	Reloads the resource, if it is already loaded.
virtual bool 	isReloadable (void) const
 	Returns true if the Resource is reloadable, false otherwise.
virtual bool 	isManuallyLoaded (void) const
 	Is this resource manually loaded? 
 	
virtual const String & 	getGroup (void)
 	Gets the group which this resource is a member of.
virtual void 	changeGroupOwnership (const String &newGroup)
 	Change the resource group ownership of a Resource.
virtual ResourceManager * 	getCreator (void)
 	Gets the manager which created this resource.
virtual const String & 	getOrigin (void) 

virtual size_t 	getSize (void) const
 	Retrieves info about the size of the resource.
virtual void 	touch (void)
 	'Touches' the resource to indicate it has been used.
virtual const String & 	getName (void) const
 	Gets resource name.
virtual ResourceHandle 	getHandle (void) const
virtual bool 	isPrepared (void) const
 	Returns true if the Resource has been prepared, false otherwise.
virtual bool 	isLoaded (void) const
 	Returns true if the Resource has been loaded, false otherwise.
virtual bool 	isLoading () const
*/
void Init_OgreResource(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);
	rb_undef_alloc_func(rb_cOgreResource);
	
	rb_define_method(rb_cOgreResource,"origin",RUBY_METHOD_FUNC(OgreResource_getOrigin),0);
	rb_define_method(rb_cOgreResource,"size",RUBY_METHOD_FUNC(OgreResource_getSize),0);
	rb_define_method(rb_cOgreResource,"name",RUBY_METHOD_FUNC(OgreResource_getName),0);
	rb_define_method(rb_cOgreResource,"state_count",RUBY_METHOD_FUNC(OgreResource_getStateCount),0);
	
	rb_define_method(rb_cOgreResource,"prepare",RUBY_METHOD_FUNC(OgreResource_prepare),-1);
	rb_define_method(rb_cOgreResource,"load",RUBY_METHOD_FUNC(OgreResource_load),-1);
	
	rb_define_method(rb_cOgreResource,"background_loaded",RUBY_METHOD_FUNC(OgreResource_isBackgroundLoaded),0);	
	rb_define_method(rb_cOgreResource,"background_loaded=",RUBY_METHOD_FUNC(OgreResource_setBackgroundLoaded),1);

	rb_define_method(rb_cOgreResource,"prepared?",RUBY_METHOD_FUNC(OgreResource_isPrepared),0);
	rb_define_method(rb_cOgreResource,"loaded?",RUBY_METHOD_FUNC(OgreResource_isLoaded),0);
	rb_define_method(rb_cOgreResource,"loading?",RUBY_METHOD_FUNC(OgreResource_isLoading),0);
}
