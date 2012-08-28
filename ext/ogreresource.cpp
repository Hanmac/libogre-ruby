
#include "ogreresource.hpp"
#include "ogreexception.hpp"

#include "ogrestringinterface.hpp"

#define _self wrap<Ogre::Resource*>(self)
#define _singleton wrap<Ogre::ResourceManager*>(self)
VALUE rb_cOgreResource;

template <>
VALUE wrap< Ogre::ResourcePtr >(const Ogre::ResourcePtr& resource )
{
	if(resource.isNull())
		return Qnil;

	if(dynamic_cast<Ogre::Material*>(resource.get()))
		return wrap(Ogre::MaterialPtr(resource));
	if(dynamic_cast<Ogre::Mesh*>(resource.get()))
		return wrap(Ogre::MeshPtr(resource));
	if(dynamic_cast<Ogre::Texture*>(resource.get()))
		return wrap(Ogre::TexturePtr(resource));
	if(dynamic_cast<Ogre::Font*>(resource.get()))
		return wrap(Ogre::FontPtr(resource));
	if(dynamic_cast<Ogre::Skeleton*>(resource.get()))
		return wrap(Ogre::SkeletonPtr(resource));
	if(dynamic_cast<Ogre::Compositor*>(resource.get()))
		return wrap(Ogre::CompositorPtr(resource));
	if(dynamic_cast<Ogre::GpuProgram*>(resource.get()))
		return wrap(Ogre::GpuProgramPtr(resource));

	return Qnil;
}

template <>
Ogre::Resource* wrap< Ogre::Resource* >(const VALUE &vresource)
{
	if(rb_obj_is_kind_of(vresource, rb_cOgreMaterial))
		return unwrapPtr<Ogre::MaterialPtr>(vresource, rb_cOgreMaterial)->get();
	if(rb_obj_is_kind_of(vresource, rb_cOgreMesh))
		return unwrapPtr<Ogre::MeshPtr>(vresource, rb_cOgreMesh)->get();
	if(rb_obj_is_kind_of(vresource, rb_cOgreTexture))
		return unwrapPtr<Ogre::TexturePtr>(vresource, rb_cOgreTexture)->get();
	if(rb_obj_is_kind_of(vresource, rb_cOgreFont))
		return unwrapPtr<Ogre::FontPtr>(vresource, rb_cOgreFont)->get();
	if(rb_obj_is_kind_of(vresource, rb_cOgreSkeleton))
		return unwrapPtr<Ogre::SkeletonPtr>(vresource, rb_cOgreSkeleton)->get();
	if(rb_obj_is_kind_of(vresource, rb_cOgreCompositor))
		return unwrapPtr<Ogre::CompositorPtr>(vresource, rb_cOgreCompositor)->get();
	if(rb_obj_is_kind_of(vresource, rb_cOgreGpuProgram))
		return unwrapPtr<Ogre::GpuProgramPtr>(vresource, rb_cOgreGpuProgram)->get();

	rb_raise(rb_eTypeError,"Expected %s got %s!",rb_class2name(rb_cOgreResource),	rb_obj_classname(vresource));
	return NULL;
}


template <>
Ogre::ResourceManager* wrap< Ogre::ResourceManager* >(const VALUE &vclass)
{
	if(vclass==rb_cOgreMaterial)
		return Ogre::MaterialManager::getSingletonPtr();
	if(vclass==rb_cOgreMesh)
		return Ogre::MeshManager::getSingletonPtr();
	if(vclass==rb_cOgreTexture)
		return Ogre::TextureManager::getSingletonPtr();
	if(vclass==rb_cOgreFont)
		return Ogre::FontManager::getSingletonPtr();
	if(vclass==rb_cOgreCompositor)
		return Ogre::CompositorManager::getSingletonPtr();
	if(vclass==rb_cOgreSkeleton)
		return Ogre::SkeletonManager::getSingletonPtr();
	if(vclass==rb_cOgreGpuProgram)
		return Ogre::GpuProgramManager::getSingletonPtr();

	rb_raise(rb_eTypeError,"%s is not a valid Ogre::ResourceManager!",rb_class2name(vclass));
	return NULL;
}

Ogre::String unwrapResourceGroup(VALUE obj,const Ogre::String &defaultgroup)
{
	if(NIL_P(obj))
		return defaultgroup;
	if(SYMBOL_P(obj))
	{
		ID id = SYM2ID(obj);
		if(id == rb_intern("default"))
			return Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
		if(id == rb_intern("internal"))
			return Ogre::ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME;
		if(id == rb_intern("autodetect"))
			return Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME;

		return defaultgroup;
	}
	return wrap<Ogre::String>(obj);
}


namespace RubyOgre {
namespace Resource {

macro_attr_bool(BackgroundLoaded)

singlereturn(getGroup)
singlereturn(getOrigin)
singlereturn(getSize)
singlereturn(getName)

singlereturn(isPrepared)
singlereturn(isLoaded)
singlereturn(isLoading)
singlereturn(isReloadable)

/*
*/
VALUE _prepare(int argc,VALUE *argv,VALUE self)
{
	VALUE backgroundThread;
	rb_scan_args(argc, argv, "01",&backgroundThread);
	if(!NIL_P(backgroundThread))
		backgroundThread = Qfalse;
	RUBYTRY(_self->prepare(RTEST(backgroundThread));)
	return self;
}
/*
*/
VALUE _load(int argc,VALUE *argv,VALUE self)
{
	VALUE backgroundThread;
	rb_scan_args(argc, argv, "01",&backgroundThread);
	if(!NIL_P(backgroundThread))
		backgroundThread = Qfalse;
	RUBYTRY(_self->load(RTEST(backgroundThread));)
	return self;
}
/*
*/
VALUE _getStateCount(VALUE self)
{
	return ULONG2NUM(_self->getStateCount());
}

/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=_getGroup(self);
	array[3]=_getName(self);
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
VALUE _singleton_get(int argc,VALUE *argv,VALUE self)
{
	VALUE path,groupname;
	rb_scan_args(argc, argv, "11",&path,&groupname);
	return wrap(_singleton->getByName(wrap<Ogre::String>(path),
		unwrapResourceGroup(groupname,Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME)
	));

}


/*

*/
VALUE _singleton_remove(VALUE self,VALUE name)
{
	_singleton->remove(wrap<Ogre::String>(name));
	return self;
}
/*

*/
VALUE _singleton_resourceExists(VALUE self,VALUE name)
{
	return _singleton->resourceExists(wrap<Ogre::String>(name)) ? Qtrue : Qfalse;
}
/*

*/
VALUE _singleton_unload(VALUE self,VALUE name)
{
	_singleton->unload(wrap<Ogre::String>(name));
	return self;
}
/*

*/
VALUE _singleton_getResourceType(VALUE self)
{
	return wrap(_singleton->getResourceType());
}
/*

*/
VALUE _singleton_getScriptPatterns(VALUE self)
{
	return wrap<Ogre::String>(_singleton->getScriptPatterns());
}
/*
*/
VALUE _singleton_getVerbose(VALUE self)
{
	return _singleton->getVerbose() ? Qtrue : Qfalse;
}
/*
*/
VALUE _singleton_setVerbose(VALUE self,VALUE val)
{
	_singleton->setVerbose(RTEST(val));
	return val;
}

/*
*/
VALUE _singleton_getMemoryBudget(VALUE self)
{
	return ULONG2NUM(_singleton->getMemoryBudget());
}
/*:nodoc:
*/
VALUE _singleton_setMemoryBudget(VALUE self,VALUE val)
{
	_singleton->setMemoryBudget(NUM2ULONG(val));
	return val;
}
/*
*/
VALUE _singleton_create(int argc,VALUE *argv,VALUE self)
{
	VALUE path,groupname,loader,params;
	rb_scan_args(argc, argv, "13",&path,&groupname,&loader,&params);
	RUBYTRY(
		return wrap(_singleton->createOrRetrieve(wrap<Ogre::String>(path),
			unwrapResourceGroup(groupname,Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME),
			false,NULL,wrap<Ogre::NameValuePairList*>(params)).first
		);
	)
	return Qnil;
}

/*

prepare (const String &name, const String &group, bool isManual=false, ManualResourceLoader *loader=0, const NameValuePairList *loadParams=0, bool backgroundThread=false)
 	Generic prepare method, used to create a Resource specific to this ResourceManager without using one of the specialised 'prepare' methods (containing per-Resource-type parameters).
load (const String &name, const String &group, bool isManual=false, ManualResourceLoader *loader=0, const NameValuePairList *loadParams=0, bool backgroundThread=false)

*/

/*
*/
VALUE _singleton_prepare(int argc,VALUE *argv,VALUE self)
{
	VALUE path,groupname,backgroundThread,loader,params;
	rb_scan_args(argc, argv, "23",&path,&groupname,&backgroundThread,&loader,&params);
	RUBYTRY(
		return wrap(_singleton->prepare(wrap<Ogre::String>(path),
			unwrapResourceGroup(groupname,Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME),
			false,NULL,wrap<Ogre::NameValuePairList*>(params),RTEST(backgroundThread))
		);
	)
	return Qnil;
}
/*
*/
VALUE _singleton_load(int argc,VALUE *argv,VALUE self)
{
	VALUE path,groupname,backgroundThread,loader,params;
	rb_scan_args(argc, argv, "23",&path,&groupname,&backgroundThread,&loader,&params);
	RUBYTRY(
		return wrap(_singleton->load(wrap<Ogre::String>(path),
			unwrapResourceGroup(groupname,Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME),
			false,NULL,NULL,RTEST(backgroundThread))
		);
	)
	return Qnil;
}

/*
*/
VALUE _singleton_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	Ogre::ResourceManager::ResourceMapIterator map = _singleton->getResourceIterator();
	Ogre::ResourceManager::ResourceMapIterator::iterator it;
	for (it = map.begin(); it != map.end(); ++it)
		rb_yield_values(2,ULONG2NUM(it->first),wrap(it->second));
	return self;
}

}
}

void Init_OgreResource(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	rb_define_attr(rb_cOgreResource,"background_loaded",1,1);
#endif
	using namespace RubyOgre::Resource;

	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);
	rb_undef_alloc_func(rb_cOgreResource);
	rb_include_module(rb_cOgreResource,rb_mOgreStringInterface);
	
	rb_define_method(rb_cOgreResource,"origin",RUBY_METHOD_FUNC(_getOrigin),0);
	rb_define_method(rb_cOgreResource,"size",RUBY_METHOD_FUNC(_getSize),0);
	rb_define_method(rb_cOgreResource,"group",RUBY_METHOD_FUNC(_getGroup),0);
	rb_define_method(rb_cOgreResource,"name",RUBY_METHOD_FUNC(_getName),0);
	rb_define_method(rb_cOgreResource,"state_count",RUBY_METHOD_FUNC(_getStateCount),0);
	
	rb_define_method(rb_cOgreResource,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	
	rb_define_method(rb_cOgreResource,"prepare",RUBY_METHOD_FUNC(_prepare),-1);
	rb_define_method(rb_cOgreResource,"load",RUBY_METHOD_FUNC(_load),-1);
	
	rb_define_attr_method(rb_cOgreResource,"background_loaded",_getBackgroundLoaded,_setBackgroundLoaded);

	rb_define_method(rb_cOgreResource,"prepared?",RUBY_METHOD_FUNC(_isPrepared),0);
	rb_define_method(rb_cOgreResource,"loaded?",RUBY_METHOD_FUNC(_isLoaded),0);
	rb_define_method(rb_cOgreResource,"loading?",RUBY_METHOD_FUNC(_isLoading),0);
	rb_define_method(rb_cOgreResource,"reloadable?",RUBY_METHOD_FUNC(_isReloadable),0);
	
	

	rb_define_singleton_method(rb_cOgreResource,"remove",RUBY_METHOD_FUNC(_singleton_remove),1);
	rb_define_singleton_method(rb_cOgreResource,"exists?",RUBY_METHOD_FUNC(_singleton_resourceExists),1);
	rb_define_singleton_method(rb_cOgreResource,"unload",RUBY_METHOD_FUNC(_singleton_unload),1);
	
	rb_define_singleton_method(rb_cOgreResource,"type",RUBY_METHOD_FUNC(_singleton_getResourceType),0);
	rb_define_singleton_method(rb_cOgreResource,"script_patterns",RUBY_METHOD_FUNC(_singleton_getScriptPatterns),0);
	
	rb_define_singleton_method(rb_cOgreResource,"verbose",RUBY_METHOD_FUNC(_singleton_getVerbose),0);
	rb_define_singleton_method(rb_cOgreResource,"verbose=",RUBY_METHOD_FUNC(_singleton_setVerbose),1);

	rb_define_singleton_method(rb_cOgreResource,"memoryBudget",RUBY_METHOD_FUNC(_singleton_getMemoryBudget),0);
	rb_define_singleton_method(rb_cOgreResource,"memoryBudget=",RUBY_METHOD_FUNC(_singleton_setMemoryBudget),1);

	rb_define_singleton_method(rb_cOgreResource,"each",RUBY_METHOD_FUNC(_singleton_each),0);
	
	rb_define_singleton_method(rb_cOgreResource,"[]",RUBY_METHOD_FUNC(_singleton_get),-1);
	
	rb_define_singleton_method(rb_cOgreResource,"create",RUBY_METHOD_FUNC(_singleton_create),-1);
	rb_define_singleton_method(rb_cOgreResource,"prepare",RUBY_METHOD_FUNC(_singleton_prepare),-1);
	rb_define_singleton_method(rb_cOgreResource,"load",RUBY_METHOD_FUNC(_singleton_load),-1);
	
	rb_extend_object(rb_cOgreResource,rb_mEnumerable);
}
