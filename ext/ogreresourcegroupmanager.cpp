#include "ogreresourcegroupmanager.hpp"
#include "ogrefileinfo.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::ResourceGroupManager*>(self)
VALUE rb_cOgreResourceGroupManager;


VALUE OgreResourceGroupManager_alloc(VALUE self)
{
	return wrap(Ogre::ResourceGroupManager::getSingletonPtr());
}

/*


*/
VALUE OgreResourceGroupManager_addResourceLocation(int argc,VALUE *argv,VALUE self)
{
	VALUE path,type,resGroup,recursive;
	rb_scan_args(argc, argv, "22",&path,&type,&resGroup,&recursive);
	Ogre::String result;
	if(NIL_P(resGroup))
		result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	else
		result = rb_string_value_cstr(&resGroup);
	try{
		_self->addResourceLocation(rb_string_value_cstr(&path),rb_string_value_cstr(&type),result,RTEST(recursive));
	}catch(Ogre::ItemIdentityException& e){
		rb_raise(rb_eOgreItemIdentityException,"%s",e.getDescription().c_str());
	}
	return self;
}
/*


*/
VALUE OgreResourceGroupManager_removeResourceLocation(int argc,VALUE *argv,VALUE self)
{
	VALUE name,resGroup;
	rb_scan_args(argc, argv, "11",&name,&resGroup);
	Ogre::String result;
	if(NIL_P(resGroup))
		result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	else
		result = rb_string_value_cstr(&resGroup);
	_self->removeResourceLocation(rb_string_value_cstr(&name),result);
	return self;
}
/*


*/
VALUE OgreResourceGroupManager_resourceLocationExists(int argc,VALUE *argv,VALUE self)
{
	VALUE name,resGroup;
	rb_scan_args(argc, argv, "11",&name,&resGroup);
	Ogre::String result;
	if(NIL_P(resGroup))
		result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	else
		result = rb_string_value_cstr(&resGroup);
	return _self->resourceLocationExists(rb_string_value_cstr(&name),result) ? Qtrue : Qfalse;
}
/*


*/
VALUE OgreResourceGroupManager_listResourceNames(int argc,VALUE *argv,VALUE self)
{
	VALUE groupname,dirs;
	rb_scan_args(argc, argv, "02",&groupname,&dirs);
	Ogre::String result;
	if(groupname == Qtrue || groupname == Qfalse){
		dirs = groupname;
		groupname = Qnil;
	}
	if(NIL_P(groupname))
		result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	else
		result = rb_string_value_cstr(&groupname);
	if(NIL_P(dirs))
		dirs = Qfalse;
	return wrap(_self->listResourceNames(result,RTEST(dirs)));
}
/*


*/
VALUE OgreResourceGroupManager_resourceExists(int argc,VALUE *argv,VALUE self)
{
	VALUE filename,groupname;
	rb_scan_args(argc, argv, "11",&filename,&groupname);
	bool result;
	if(NIL_P(groupname))
		result= _self->resourceExistsInAnyGroup(rb_string_value_cstr(&filename));
	else
		result= _self->resourceExists(rb_string_value_cstr(&groupname),rb_string_value_cstr(&filename));
	return result ? Qtrue : Qfalse;
}
/*


*/
VALUE OgreResourceGroupManager_listResourceLocations(int argc,VALUE *argv,VALUE self)
{
	VALUE groupname;
	rb_scan_args(argc, argv, "01",&groupname);
	Ogre::String result;
	if(NIL_P(groupname))
		result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	else
		result = rb_string_value_cstr(&groupname);
	return wrap(_self->listResourceLocations(result));
}
/*


*/
VALUE OgreResourceGroupManager_findResourceLocation(int argc,VALUE *argv,VALUE self)
{
	VALUE pattern,groupname;
	rb_scan_args(argc, argv, "11",&pattern,&groupname);
	Ogre::String result;
	if(NIL_P(groupname))
		result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	else
		result = rb_string_value_cstr(&groupname);
	return wrap(_self->findResourceLocation(result,rb_string_value_cstr(&pattern)));
}
/*


*/
VALUE OgreResourceGroupManager_findResourceFileInfo(int argc,VALUE *argv,VALUE self)
{
	VALUE pattern,groupname,dirs;
	rb_scan_args(argc, argv, "12",&pattern,&groupname,&dirs);
	Ogre::String result;
	if(groupname == Qtrue || groupname == Qfalse){
		dirs = groupname;
		groupname = Qnil;
	}
	if(NIL_P(groupname))
		result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	else
		result = rb_string_value_cstr(&groupname);
	if(NIL_P(dirs))
		dirs = Qfalse;
	return wrap(_self->findResourceFileInfo(result,rb_string_value_cstr(&pattern),RTEST(dirs)));
}
/*


*/
VALUE OgreResourceGroupManager_listResourceFileInfo(int argc,VALUE *argv,VALUE self)
{
	VALUE groupname,dirs;
	rb_scan_args(argc, argv, "02",&groupname,&dirs);
	Ogre::String result;
	if(groupname == Qtrue || groupname == Qfalse){
		dirs = groupname;
		groupname = Qnil;
	}
	if(NIL_P(groupname))
		result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	else
		result = rb_string_value_cstr(&groupname);
	if(NIL_P(dirs))
		dirs = Qfalse;
	return wrap(_self->listResourceFileInfo(result,RTEST(dirs)));
}
/*


*/
VALUE OgreResourceGroupManager_resourceModifiedTime(int argc,VALUE *argv,VALUE self)
{
	VALUE groupname,filename;
	rb_scan_args(argc, argv, "11",&filename,&groupname);
	Ogre::String result;
	if(NIL_P(groupname))
		result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	else
		result = rb_string_value_cstr(&groupname);
	return ULONG2NUM(_self->resourceModifiedTime(result,rb_string_value_cstr(&filename)));
}
/*


*/
VALUE OgreResourceGroupManager_isResourceGroupInitialised(VALUE self,VALUE name)
{
	return _self->isResourceGroupInitialised(rb_string_value_cstr(&name)) ? Qtrue : Qfalse;
}
/*


*/
VALUE OgreResourceGroupManager_isResourceGroupLoaded(VALUE self,VALUE name)
{
	return _self->isResourceGroupLoaded(rb_string_value_cstr(&name)) ? Qtrue : Qfalse;
}
/*


*/
VALUE OgreResourceGroupManager_ResourceGroupExists(VALUE self,VALUE name)
{
	return _self->resourceGroupExists(rb_string_value_cstr(&name)) ? Qtrue : Qfalse;
}
/*


*/
VALUE OgreResourceGroupManager_getResourceGroups(VALUE self)
{
	return wrap(_self->getResourceGroups());
}
/*


*/
VALUE OgreResourceGroupManager_clearResourceGroup(VALUE self,VALUE name)
{
	_self->clearResourceGroup(rb_string_value_cstr(&name));
	return self;
}
/*


*/
VALUE OgreResourceGroupManager_destroyResourceGroup(VALUE self,VALUE name)
{
	_self->destroyResourceGroup(rb_string_value_cstr(&name));
	return self;
}
/*


*/
VALUE OgreResourceGroupManager_isResourceGroupInGlobalPool(VALUE self,VALUE name)
{
	return _self->isResourceGroupInGlobalPool(rb_string_value_cstr(&name)) ? Qtrue : Qfalse;
}
/*


*/
VALUE OgreResourceGroupManager_createResourceGroup(int argc,VALUE *argv,VALUE self)
{
	VALUE groupname,inGlobalPool;
	rb_scan_args(argc, argv, "11",&groupname,&inGlobalPool);
	if(NIL_P(inGlobalPool))
		inGlobalPool = Qfalse;
	_self->createResourceGroup(rb_string_value_cstr(&groupname),RTEST(inGlobalPool));
	return self;
}
/*


*/
VALUE OgreResourceGroupManager_unloadResourceGroup(int argc,VALUE *argv,VALUE self)
{
	VALUE groupname,reloadableOnly;
	rb_scan_args(argc, argv, "11",&groupname,&reloadableOnly);
	if(NIL_P(reloadableOnly))
		reloadableOnly = Qfalse;
	_self->unloadResourceGroup(rb_string_value_cstr(&groupname),RTEST(reloadableOnly));
	return self;
}
/*


*/
VALUE OgreResourceGroupManager_undeclareResource(int argc,VALUE *argv,VALUE self)
{
	VALUE file,groupname;
	rb_scan_args(argc, argv, "11",&file,&groupname);
	Ogre::String result;
	if(NIL_P(groupname))
		result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	else
		result = rb_string_value_cstr(&groupname);
	_self->undeclareResource(result,rb_string_value_cstr(&file));
	return self;
}

/*
void loadResourceGroup(const String& name, bool loadMainResources = true, bool loadWorldGeom = true);
void unloadResourceGroup(const String& name, bool reloadableOnly = true);
void createResourceGroup(const String& name, const bool inGlobalPool = true);
void initialiseResourceGroup(const String& name);
void initialiseAllResourceGroups(void);
void prepareResourceGroup(const String& name, bool prepareMainResources = true, bool prepareWorldGeom = true);

ResourceDeclarationList getResourceDeclarationList(const String& groupName);
const LocationList& getResourceLocationList(const String& groupName);
ResourceLoadingListener *getLoadingListener();
void setLoadingListener(ResourceLoadingListener *listener);
void addResourceGroupListener(ResourceGroupListener* l);
void removeResourceGroupListener(ResourceGroupListener* l);
void undeclareResource(const String& name, const String& groupName);

const String& findGroupContainingResource(const String& filename);//XXX:RAISE Exeption
*/
void Init_OgreResourceGroupManager(VALUE rb_mOgre)
{
	#if 0
	rb_mOgre = rb_define_module("Ogre");
	#endif
	rb_cOgreResourceGroupManager = rb_define_class_under(rb_mOgre,"ResourceGroupManager",rb_cObject);
	rb_define_alloc_func(rb_cOgreResourceGroupManager,OgreResourceGroupManager_alloc);
	#if 0
	rb_include_module(rb_cOgreResourceGroupManager,rb_mSingleton);
	#endif
	rb_funcall(rb_cOgreResourceGroupManager,rb_intern("include"),1,rb_mSingleton);
	rb_define_method(rb_cOgreResourceGroupManager,"addResourceLocation",RUBY_METHOD_FUNC(OgreResourceGroupManager_addResourceLocation),2);
	
	rb_define_method(rb_cOgreResourceGroupManager,"removeResourceLocation",RUBY_METHOD_FUNC(OgreResourceGroupManager_removeResourceLocation),-1);
	rb_define_method(rb_cOgreResourceGroupManager,"resourceLocationExists?",RUBY_METHOD_FUNC(OgreResourceGroupManager_resourceLocationExists),-1);
	rb_define_method(rb_cOgreResourceGroupManager,"listResourceNames",RUBY_METHOD_FUNC(OgreResourceGroupManager_listResourceNames),-1);
	rb_define_method(rb_cOgreResourceGroupManager,"listResourceLocations",RUBY_METHOD_FUNC(OgreResourceGroupManager_listResourceLocations),-1);
	rb_define_method(rb_cOgreResourceGroupManager,"findResourceLocation",RUBY_METHOD_FUNC(OgreResourceGroupManager_findResourceLocation),-1);
	rb_define_method(rb_cOgreResourceGroupManager,"getResourceGroups",RUBY_METHOD_FUNC(OgreResourceGroupManager_getResourceGroups),0);
	rb_define_method(rb_cOgreResourceGroupManager,"listResourceFileInfo",RUBY_METHOD_FUNC(OgreResourceGroupManager_listResourceFileInfo),-1);
	rb_define_method(rb_cOgreResourceGroupManager,"findResourceFileInfo",RUBY_METHOD_FUNC(OgreResourceGroupManager_findResourceFileInfo),-1);
	
	rb_define_method(rb_cOgreResourceGroupManager,"ResourceGroupInitialised?",RUBY_METHOD_FUNC(OgreResourceGroupManager_isResourceGroupInitialised),1);
	rb_define_method(rb_cOgreResourceGroupManager,"ResourceGroupLoaded?",RUBY_METHOD_FUNC(OgreResourceGroupManager_isResourceGroupLoaded),1);
	rb_define_method(rb_cOgreResourceGroupManager,"ResourceGroupExists?",RUBY_METHOD_FUNC(OgreResourceGroupManager_ResourceGroupExists),1);
	
	rb_define_method(rb_cOgreResourceGroupManager,"clearResourceGroup",RUBY_METHOD_FUNC(OgreResourceGroupManager_clearResourceGroup),1);
	rb_define_method(rb_cOgreResourceGroupManager,"destroyResourceGroup",RUBY_METHOD_FUNC(OgreResourceGroupManager_destroyResourceGroup),1);
	rb_define_method(rb_cOgreResourceGroupManager,"inGlobalPool?",RUBY_METHOD_FUNC(OgreResourceGroupManager_isResourceGroupInGlobalPool),1);

	rb_define_method(rb_cOgreResourceGroupManager,"createResourceGroup",RUBY_METHOD_FUNC(OgreResourceGroupManager_createResourceGroup),-1);
	rb_define_method(rb_cOgreResourceGroupManager,"unloadResourceGroup",RUBY_METHOD_FUNC(OgreResourceGroupManager_unloadResourceGroup),-1);
	rb_define_method(rb_cOgreResourceGroupManager,"undeclareResource",RUBY_METHOD_FUNC(OgreResourceGroupManager_undeclareResource),-1);
}
