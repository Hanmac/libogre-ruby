#include "ogreresource.hpp"
#include "ogreexception.hpp"

#include "ogrestringinterface.hpp"

#define _self wrap<Ogre::Resource*>(self)
#define _singleton wrap<Ogre::ResourceManager*>(self)
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
	try{
		_self->prepare(RTEST(backgroundThread));
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
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
	try{
		_self->load(RTEST(backgroundThread));
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
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
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE OgreResource_inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=OgreResource_getGroup(self);
	array[3]=OgreResource_getName(self);
	return rb_f_sprintf(4,array);
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



/*
*/
VALUE OgreResource_singleton_get(int argc,VALUE *argv,VALUE self)
{
	VALUE path,groupname;
	rb_scan_args(argc, argv, "11",&path,&groupname);
	Ogre::String temp;
	if(NIL_P(groupname))
		temp = Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME;
	else
		temp = rb_string_value_cstr(&groupname);
	Ogre::ResourcePtr result = _singleton->getByName(rb_string_value_cstr(&path),temp);
	return result.get() == NULL ? Qnil : wrap(result);
}


/*

*/
VALUE OgreResource_singleton_remove(VALUE self,VALUE name)
{
	_singleton->remove(rb_string_value_cstr(&name));
	return self;
}
/*

*/
VALUE OgreResource_singleton_resourceExists(VALUE self,VALUE name)
{
	return _singleton->resourceExists(rb_string_value_cstr(&name)) ? Qtrue : Qfalse;
}
/*

*/
VALUE OgreResource_singleton_unload(VALUE self,VALUE name)
{
	_singleton->unload(rb_string_value_cstr(&name));
	return self;
}
/*

*/
VALUE OgreResource_singleton_getResourceType(VALUE self)
{
	return wrap(_singleton->getResourceType());
}
/*

*/
VALUE OgreResource_singleton_getScriptPatterns(VALUE self)
{
	return wrap<Ogre::String>(_singleton->getScriptPatterns());
}
/*
*/
VALUE OgreResource_singleton_getVerbose(VALUE self)
{
	return _singleton->getVerbose() ? Qtrue : Qfalse;
}
/*
*/
VALUE OgreResource_singleton_setVerbose(VALUE self,VALUE val)
{
	_singleton->setVerbose(RTEST(val));
	return val;
}

/*
*/
VALUE OgreResource_singleton_getMemoryBudget(VALUE self)
{
	return ULONG2NUM(_singleton->getMemoryBudget());
}
/*:nodoc:
*/
VALUE OgreResource_singleton_setMemoryBudget(VALUE self,VALUE val)
{
	_singleton->setMemoryBudget(NUM2ULONG(val));
	return val;
}
/*
*/
VALUE OgreResource_singleton_create(int argc,VALUE *argv,VALUE self)
{
	VALUE path,groupname,loader,params;
	rb_scan_args(argc, argv, "22",&path,&groupname,&loader,&params);
	return wrap(_singleton->createOrRetrieve(rb_string_value_cstr(&path),rb_string_value_cstr(&groupname),false,NULL,NULL).first.get());
}

/*

prepare (const String &name, const String &group, bool isManual=false, ManualResourceLoader *loader=0, const NameValuePairList *loadParams=0, bool backgroundThread=false)
 	Generic prepare method, used to create a Resource specific to this ResourceManager without using one of the specialised 'prepare' methods (containing per-Resource-type parameters).
load (const String &name, const String &group, bool isManual=false, ManualResourceLoader *loader=0, const NameValuePairList *loadParams=0, bool backgroundThread=false)

*/

/*
*/
VALUE OgreResource_singleton_prepare(int argc,VALUE *argv,VALUE self)
{
	VALUE path,groupname,backgroundThread,loader,params;
	rb_scan_args(argc, argv, "23",&path,&groupname,&backgroundThread,&loader,&params);
	return wrap(_singleton->prepare(rb_string_value_cstr(&path),rb_string_value_cstr(&groupname),false,NULL,NULL,RTEST(backgroundThread)).get());
}
/*
*/
VALUE OgreResource_singleton_load(int argc,VALUE *argv,VALUE self)
{
	VALUE path,groupname,backgroundThread,loader,params;
	rb_scan_args(argc, argv, "23",&path,&groupname,&backgroundThread,&loader,&params);
	try{
		return wrap(_singleton->load(rb_string_value_cstr(&path),rb_string_value_cstr(&groupname),false,NULL,NULL,RTEST(backgroundThread)).get());
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
		return Qnil;
	}
}

/*
*/
VALUE OgreResource_singleton_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	Ogre::ResourceManager::ResourceMapIterator map = _singleton->getResourceIterator();
	Ogre::ResourceManager::ResourceMapIterator::iterator it;
	for (it = map.begin(); it != map.end(); ++it)
		rb_yield_values(2,ULONG2NUM(it->first),wrap(it->second));
	return self;
}

void Init_OgreResource(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	rb_define_attr(rb_cOgreResource,"background_loaded",1,1);
#endif
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);
	rb_undef_alloc_func(rb_cOgreResource);
	rb_include_module(rb_cOgreResource,rb_mOgreStringInterface);
	
	rb_define_method(rb_cOgreResource,"origin",RUBY_METHOD_FUNC(OgreResource_getOrigin),0);
	rb_define_method(rb_cOgreResource,"size",RUBY_METHOD_FUNC(OgreResource_getSize),0);
	rb_define_method(rb_cOgreResource,"group",RUBY_METHOD_FUNC(OgreResource_getGroup),0);
	rb_define_method(rb_cOgreResource,"name",RUBY_METHOD_FUNC(OgreResource_getName),0);
	rb_define_method(rb_cOgreResource,"state_count",RUBY_METHOD_FUNC(OgreResource_getStateCount),0);
	
	rb_define_method(rb_cOgreResource,"inspect",RUBY_METHOD_FUNC(OgreResource_inspect),0);
	
	rb_define_method(rb_cOgreResource,"prepare",RUBY_METHOD_FUNC(OgreResource_prepare),-1);
	rb_define_method(rb_cOgreResource,"load",RUBY_METHOD_FUNC(OgreResource_load),-1);
	
	rb_define_attr_method(rb_cOgreResource,"background_loaded",OgreResource_isBackgroundLoaded,OgreResource_setBackgroundLoaded);

	rb_define_method(rb_cOgreResource,"prepared?",RUBY_METHOD_FUNC(OgreResource_isPrepared),0);
	rb_define_method(rb_cOgreResource,"loaded?",RUBY_METHOD_FUNC(OgreResource_isLoaded),0);
	rb_define_method(rb_cOgreResource,"loading?",RUBY_METHOD_FUNC(OgreResource_isLoading),0);
	
	

	rb_define_singleton_method(rb_cOgreResource,"remove",RUBY_METHOD_FUNC(OgreResource_singleton_remove),1);
	rb_define_singleton_method(rb_cOgreResource,"resourceExists?",RUBY_METHOD_FUNC(OgreResource_singleton_resourceExists),1);
	rb_define_singleton_method(rb_cOgreResource,"unload",RUBY_METHOD_FUNC(OgreResource_singleton_unload),1);
	
	rb_define_singleton_method(rb_cOgreResource,"resourceType",RUBY_METHOD_FUNC(OgreResource_singleton_getResourceType),0);
	rb_define_singleton_method(rb_cOgreResource,"scriptPatterns",RUBY_METHOD_FUNC(OgreResource_singleton_getScriptPatterns),0);
	
	rb_define_singleton_method(rb_cOgreResource,"verbose",RUBY_METHOD_FUNC(OgreResource_singleton_getVerbose),0);
	rb_define_singleton_method(rb_cOgreResource,"verbose=",RUBY_METHOD_FUNC(OgreResource_singleton_setVerbose),1);

	rb_define_singleton_method(rb_cOgreResource,"memoryBudget",RUBY_METHOD_FUNC(OgreResource_singleton_getMemoryBudget),0);
	rb_define_singleton_method(rb_cOgreResource,"memoryBudget=",RUBY_METHOD_FUNC(OgreResource_singleton_setMemoryBudget),1);

	rb_define_singleton_method(rb_cOgreResource,"each",RUBY_METHOD_FUNC(OgreResource_singleton_each),0);
	
	rb_define_singleton_method(rb_cOgreResource,"[]",RUBY_METHOD_FUNC(OgreResource_singleton_get),-1);
	
	rb_define_singleton_method(rb_cOgreResource,"create",RUBY_METHOD_FUNC(OgreResource_singleton_create),-1);
	rb_define_singleton_method(rb_cOgreResource,"prepare",RUBY_METHOD_FUNC(OgreResource_singleton_prepare),-1);
	rb_define_singleton_method(rb_cOgreResource,"load",RUBY_METHOD_FUNC(OgreResource_singleton_load),-1);
	
	rb_extend_object(rb_cOgreResource,rb_mEnumerable);
}
