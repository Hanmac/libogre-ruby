#include "ogreresourcegroup.hpp"
//#include "ogreresourcegroupmanager.hpp"
#include "ogrefileinfo.hpp"
#include "ogredatastream.hpp"
#include "ogreexception.hpp"
#define selfname wrap<ResourceGroup*>(self)->name
#define manager Ogre::ResourceGroupManager::getSingletonPtr()
VALUE rb_cOgreResourceGroup;

VALUE OgreResourceGroup_alloc(VALUE self)
{
	ResourceGroup *temp = new ResourceGroup;
	return wrap(temp);
}
/*


*/
VALUE OgreResourceGroup_initialize(int argc, VALUE *argv,VALUE self)
{
	VALUE name,inGlobalPool;
	rb_scan_args(argc, argv, "11",&name,&inGlobalPool);
	if(NIL_P(inGlobalPool))
		inGlobalPool = Qtrue;
	selfname = rb_string_value_cstr(&name);
	if(!manager->resourceGroupExists(selfname))
		manager->createResourceGroup(selfname,RTEST(inGlobalPool));
	return self;
}
/*


*/
VALUE OgreResourceGroup_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	selfname = wrap<ResourceGroup*>(other)->name;
	return result;
}
/*


*/
VALUE OgreResourceGroup_resourceLocationExists(VALUE self,VALUE name)
{
	return manager->resourceLocationExists(rb_string_value_cstr(&name),selfname) ? Qtrue : Qfalse;
}
/*


*/
VALUE OgreResourceGroup_listResourceNames(int argc,VALUE *argv,VALUE self)
{
	VALUE dirs;
	rb_scan_args(argc, argv, "01",&dirs);
	return wrap<Ogre::String>(manager->listResourceNames(selfname,RTEST(dirs)));	
}
/*


*/
VALUE OgreResourceGroup_listResourceLocations(VALUE self)
{
	return wrap<Ogre::String>(manager->listResourceLocations(selfname));
}
/*


*/
VALUE OgreResourceGroup_listResourceFileInfo(int argc,VALUE *argv,VALUE self)
{
	VALUE dirs;
	rb_scan_args(argc, argv, "01",&dirs);
	if(NIL_P(dirs))
		dirs = Qfalse;
	return wrap<Ogre::FileInfo>(manager->listResourceFileInfo(selfname,RTEST(dirs)));
}
/*


*/
VALUE OgreResourceGroup_initialised(VALUE self)
{
	return manager->isResourceGroupInitialised(selfname) ? Qtrue : Qfalse;
}
/*


*/
VALUE OgreResourceGroup_loaded(VALUE self)
{
	return manager->isResourceGroupLoaded(selfname) ? Qtrue : Qfalse;
}
/*


*/
VALUE OgreResourceGroup_exists(VALUE self)
{
	return manager->resourceGroupExists(selfname) ? Qtrue : Qfalse;
}
/*


*/
VALUE OgreResourceGroup_clear(VALUE self)
{
	manager->clearResourceGroup(selfname);
	return self;
}
/*


*/
VALUE OgreResourceGroup_destroy(VALUE self)
{
	manager->destroyResourceGroup(selfname);
	return self;
}
/*


*/
VALUE OgreResourceGroup_inGlobalPool(VALUE self)
{
	return manager->isResourceGroupInGlobalPool(selfname) ? Qtrue : Qfalse;
}
/*


*/
VALUE OgreResourceGroup_undeclareResource(VALUE self,VALUE name)
{
	manager->undeclareResource(selfname,rb_string_value_cstr(&name));
	return self;
}
/*

*/
VALUE OgreResourceGroup_unloadResourceGroup(int argc,VALUE *argv,VALUE self)
{
	VALUE reloadableOnly;
	rb_scan_args(argc, argv, "01",&reloadableOnly);
	if(NIL_P(reloadableOnly))
		reloadableOnly = Qtrue;
	manager->unloadResourceGroup(selfname,RTEST(reloadableOnly));
	return self;
}
/*

*/
VALUE OgreResourceGroup_openResources(VALUE self,VALUE file)
{
	return wrap<Ogre::DataStreamPtr>(manager->openResources(rb_string_value_cstr(&file),selfname));
}
/*


*/
VALUE OgreResourceGroup_createResource(int argc,VALUE *argv,VALUE self)
{
	VALUE file,hash,temp;
	bool overwrite;
	rb_scan_args(argc, argv, "11",&file,&hash);
	Ogre::String locationPattern;
	if(!rb_obj_is_kind_of(hash,rb_cHash) || NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("overwrite")))))
		overwrite = false;
	else
		overwrite = RTEST(temp);
	if(!rb_obj_is_kind_of(hash,rb_cHash) || NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("pattern")))))
		locationPattern = Ogre::StringUtil::BLANK;
	else
		locationPattern = rb_string_value_cstr(&temp);
	try{
		return wrap(manager->createResource(rb_string_value_cstr(&file),selfname,overwrite,locationPattern));
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
	return Qnil;
}

//void initialiseResourceGroup(const String& name);

void Init_OgreResourceGroup(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreResourceGroup = rb_define_class_under(rb_mOgre,"ResourceGroup",rb_cObject);
	rb_define_alloc_func(rb_cOgreResourceGroup,OgreResourceGroup_alloc);
	rb_define_private_method(rb_cOgreResourceGroup,"initialize_copy",RUBY_METHOD_FUNC(OgreResourceGroup_initialize_copy),1);
	
	rb_define_method(rb_cOgreResourceGroup,"initialize",RUBY_METHOD_FUNC(OgreResourceGroup_initialize),-1);
	rb_define_method(rb_cOgreResourceGroup,"resourceLocationExists?",RUBY_METHOD_FUNC(OgreResourceGroup_resourceLocationExists),1);
	rb_define_method(rb_cOgreResourceGroup,"listResourceNames",RUBY_METHOD_FUNC(OgreResourceGroup_listResourceNames),1);
	rb_define_method(rb_cOgreResourceGroup,"listResourceLocations",RUBY_METHOD_FUNC(OgreResourceGroup_listResourceLocations),0);
	rb_define_method(rb_cOgreResourceGroup,"listResourceFileInfo",RUBY_METHOD_FUNC(OgreResourceGroup_listResourceFileInfo),-1);
	
	rb_define_method(rb_cOgreResourceGroup,"clear",RUBY_METHOD_FUNC(OgreResourceGroup_clear),0);
	rb_define_method(rb_cOgreResourceGroup,"destroy",RUBY_METHOD_FUNC(OgreResourceGroup_destroy),0);
	rb_define_method(rb_cOgreResourceGroup,"initialised?",RUBY_METHOD_FUNC(OgreResourceGroup_initialised),0);
	rb_define_method(rb_cOgreResourceGroup,"loaded?",RUBY_METHOD_FUNC(OgreResourceGroup_loaded),0);
	rb_define_method(rb_cOgreResourceGroup,"exist?",RUBY_METHOD_FUNC(OgreResourceGroup_exists),0);
	rb_define_method(rb_cOgreResourceGroup,"inGlobalPool?",RUBY_METHOD_FUNC(OgreResourceGroup_inGlobalPool),0);
	rb_define_method(rb_cOgreResourceGroup,"undeclareResource",RUBY_METHOD_FUNC(OgreResourceGroup_undeclareResource),1);
	rb_define_method(rb_cOgreResourceGroup,"unloadResourceGroup",RUBY_METHOD_FUNC(OgreResourceGroup_unloadResourceGroup),-1);
	
	rb_define_method(rb_cOgreResourceGroup,"openResources",RUBY_METHOD_FUNC(OgreResourceGroup_openResources),1);
	rb_define_method(rb_cOgreResourceGroup,"createResource",RUBY_METHOD_FUNC(OgreResourceGroup_createResource),-1);
}
