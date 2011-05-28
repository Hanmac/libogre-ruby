#include "ogreresourcegroup.hpp"
#include "ogreresource.hpp"
#include "ogrefileinfo.hpp"
#include "ogredatastream.hpp"
#include "ogreexception.hpp"
#define selfname wrap<ResourceGroup*>(self)->name
#define manager Ogre::ResourceGroupManager::getSingletonPtr()
VALUE rb_cOgreResourceGroup;

VALUE OgreResourceGroup_alloc(VALUE self)
{
	return wrap(new ResourceGroup);
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
VALUE OgreResourceGroup_addResourceLocation(int argc,VALUE *argv,VALUE self)
{
	VALUE path,type,recursive;
	rb_scan_args(argc, argv, "21",&path,&type,&recursive);
	Ogre::String result;
	try{
		manager->addResourceLocation(rb_string_value_cstr(&path),rb_string_value_cstr(&type),selfname,RTEST(recursive));
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
	return self;
}
/*
*/
VALUE OgreResourceGroup_removeResourceLocation(VALUE self,VALUE name)
{
	try{
		manager->removeResourceLocation(rb_string_value_cstr(&name),selfname);
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
	return self;
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
VALUE OgreResourceGroup_findResourceLocation(VALUE self,VALUE pattern)
{
	return wrap<Ogre::String>(manager->findResourceLocation(selfname,rb_string_value_cstr(&pattern)));
}
/*
*/
VALUE OgreResourceGroup_findResourceFileInfo(int argc,VALUE *argv,VALUE self)
{
	VALUE pattern,dirs;
	rb_scan_args(argc, argv, "11",&pattern,&dirs);
	if(NIL_P(dirs))
		dirs = Qfalse;
	return wrap<Ogre::FileInfo>(manager->findResourceFileInfo(selfname,rb_string_value_cstr(&pattern),RTEST(dirs)));
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
VALUE OgreResourceGroup_unload(int argc,VALUE *argv,VALUE self)
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
VALUE OgreResourceGroup_openResource(int argc,VALUE *argv,VALUE self)
{
	VALUE file,notfound;
	rb_scan_args(argc, argv, "11",&file,&notfound);
	if(NIL_P(notfound))
		notfound = Qtrue;
	Ogre::Resource *res=NULL;
	Ogre::DataStreamPtr ptr = manager->openResource(rb_string_value_cstr(&file),selfname,RTEST(notfound),res);
	VALUE result = rb_ary_new();
	rb_ary_push(result,wrap(ptr));
	rb_ary_push(result,wrap(res));
	return result;
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

/*
*/
VALUE OgreResourceGroup_initialise(VALUE self)
{
	try{
		manager->initialiseResourceGroup(selfname);
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}	
	return self;
}



//singleton

/*
*/
VALUE OgreResourceGroup_singleton_listResourceNames(int argc,VALUE *argv,VALUE self)
{
	VALUE groupname,dirs;
	rb_scan_args(argc, argv, "01",&dirs);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(groupname == Qtrue || groupname == Qfalse){
		dirs = groupname;
		groupname = Qnil;
	}
	if(!NIL_P(groupname))
		result = rb_string_value_cstr(&groupname);
	if(NIL_P(dirs))
		dirs = Qfalse;
	return wrap<Ogre::String>(manager->listResourceNames(result,RTEST(dirs)));
}
/*
*/
VALUE OgreResourceGroup_singleton_addResourceLocation(int argc,VALUE *argv,VALUE self)
{
	VALUE path,type,resGroup,recursive;
	rb_scan_args(argc, argv, "22",&path,&type,&resGroup,&recursive);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(NIL_P(resGroup))
		result = rb_string_value_cstr(&resGroup);
	try{
		manager->addResourceLocation(rb_string_value_cstr(&path),rb_string_value_cstr(&type),result,RTEST(recursive));
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
	return self;
}
/*
*/
VALUE OgreResourceGroup_singleton_removeResourceLocation(int argc,VALUE *argv,VALUE self)
{
	VALUE name,resGroup;
	rb_scan_args(argc, argv, "11",&name,&resGroup);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(!NIL_P(resGroup))
		result = rb_string_value_cstr(&resGroup);
	manager->removeResourceLocation(rb_string_value_cstr(&name),result);
	return self;
}
/*
*/
VALUE OgreResourceGroup_singleton_listResourceLocations(int argc,VALUE *argv,VALUE self)
{
	VALUE groupname;
	rb_scan_args(argc, argv, "01",&groupname);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(!NIL_P(groupname))
		result = rb_string_value_cstr(&groupname);
	return wrap<Ogre::String>(manager->listResourceLocations(result));
}
/*
*/
VALUE OgreResourceGroup_singleton_findResourceLocation(int argc,VALUE *argv,VALUE self)
{
	VALUE pattern,groupname;
	rb_scan_args(argc, argv, "11",&pattern,&groupname);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(!NIL_P(groupname))
		result = rb_string_value_cstr(&groupname);
	return wrap<Ogre::String>(manager->findResourceLocation(result,rb_string_value_cstr(&pattern)));
}
/*
*/
VALUE OgreResourceGroup_singleton_findResourceFileInfo(int argc,VALUE *argv,VALUE self)
{
	VALUE pattern,groupname,dirs;
	rb_scan_args(argc, argv, "12",&pattern,&groupname,&dirs);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(groupname == Qtrue || groupname == Qfalse){
		dirs = groupname;
		groupname = Qnil;
	}
	if(!NIL_P(groupname))
		result = rb_string_value_cstr(&groupname);
	if(NIL_P(dirs))
		dirs = Qfalse;
	return wrap<Ogre::FileInfo>(manager->findResourceFileInfo(result,rb_string_value_cstr(&pattern),RTEST(dirs)));
}
/*
*/
VALUE OgreResourceGroup_singleton_listResourceFileInfo(int argc,VALUE *argv,VALUE self)
{
	VALUE groupname,dirs;
	rb_scan_args(argc, argv, "02",&groupname,&dirs);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(groupname == Qtrue || groupname == Qfalse){
		dirs = groupname;
		groupname = Qnil;
	}
	if(!NIL_P(groupname))
		result = rb_string_value_cstr(&groupname);
	if(NIL_P(dirs))
		dirs = Qfalse;
	return wrap<Ogre::FileInfo>(manager->listResourceFileInfo(result,RTEST(dirs)));
}

/*
*/
VALUE OgreResourceGroup_singleton_resourceLocationExists(int argc,VALUE *argv,VALUE self)
{
	VALUE name,resGroup;
	rb_scan_args(argc, argv, "11",&name,&resGroup);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(!NIL_P(resGroup))
		result = rb_string_value_cstr(&resGroup);
	return manager->resourceLocationExists(rb_string_value_cstr(&name),result) ? Qtrue : Qfalse;
}
/*
*/
VALUE OgreResourceGroup_singleton_initialiseGroup(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	try{
		if(NIL_P(name))
			manager->initialiseAllResourceGroups();
		else
			manager->initialiseResourceGroup(rb_string_value_cstr(&name));
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}	
	return self;
}

/*
*/
VALUE OgreResourceGroup_singleton_isResourceGroupInitialised(VALUE self,VALUE name)
{
	return manager->isResourceGroupInitialised(rb_string_value_cstr(&name)) ? Qtrue : Qfalse;
}
/*
*/
VALUE OgreResourceGroup_singleton_isResourceGroupLoaded(VALUE self,VALUE name)
{
	return manager->isResourceGroupLoaded(rb_string_value_cstr(&name)) ? Qtrue : Qfalse;
}
/*
*/
VALUE OgreResourceGroup_singleton_ResourceGroupExists(VALUE self,VALUE name)
{
	return manager->resourceGroupExists(rb_string_value_cstr(&name)) ? Qtrue : Qfalse;
}

/*
*/
VALUE OgreResourceGroup_singleton_getResourceGroups(VALUE self)
{
	return wrap<Ogre::String>(manager->getResourceGroups());
}
/*
*/
VALUE OgreResourceGroup_singleton_clearResourceGroup(VALUE self,VALUE name)
{
	manager->clearResourceGroup(rb_string_value_cstr(&name));
	return self;
}
/*
*/
VALUE OgreResourceGroup_singleton_destroyResourceGroup(VALUE self,VALUE name)
{
	manager->destroyResourceGroup(rb_string_value_cstr(&name));
	return self;
}
/*
*/
VALUE OgreResourceGroup_singleton_isResourceGroupInGlobalPool(VALUE self,VALUE name)
{
	return manager->isResourceGroupInGlobalPool(rb_string_value_cstr(&name)) ? Qtrue : Qfalse;
}

/*
*/
VALUE OgreResourceGroup_singleton_openResource(int argc,VALUE *argv,VALUE self)
{
	VALUE file,groupname,notfound;
	rb_scan_args(argc, argv, "12",&file,&groupname,&notfound);
	Ogre::String cgroupname = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;;
	if(!NIL_P(groupname))
		cgroupname = rb_string_value_cstr(&groupname);
	if(NIL_P(notfound))
		notfound = Qtrue;
	Ogre::Resource *res=NULL;
	Ogre::DataStreamPtr ptr = manager->openResource(rb_string_value_cstr(&file),cgroupname,RTEST(notfound),res);
	VALUE result = rb_ary_new();
	rb_ary_push(result,wrap(ptr));
	rb_ary_push(result,wrap(res));
	return result;
}

/*
*/
VALUE OgreResourceGroup_singleton_openResources(int argc,VALUE *argv,VALUE self)
{
	VALUE file,groupname;
	rb_scan_args(argc, argv, "11",&file,&groupname);
	Ogre::String result;
	if(NIL_P(groupname))
		result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	else
		result = rb_string_value_cstr(&groupname);
	return wrap<Ogre::DataStreamPtr>(manager->openResources(rb_string_value_cstr(&file),result));
}
/*
*/
VALUE OgreResourceGroup_singleton_createResource(int argc,VALUE *argv,VALUE self)
{
	VALUE file,hash,temp;
	bool overwrite = false;
	rb_scan_args(argc, argv, "11",&file,&hash);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	Ogre::String locationPattern =  Ogre::StringUtil::BLANK;
	if(rb_obj_is_kind_of(hash,rb_cHash) && !NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("group_name")))))
		result = rb_string_value_cstr(&temp);
	if(rb_obj_is_kind_of(hash,rb_cHash) && !NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("overwrite")))))
		overwrite = RTEST(temp);
	if(rb_obj_is_kind_of(hash,rb_cHash) && !NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("pattern")))))
		locationPattern = rb_string_value_cstr(&temp);
	try{
		return wrap(manager->createResource(rb_string_value_cstr(&file),result,overwrite,locationPattern));
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
	return Qnil;
}
/*
*/
VALUE OgreResourceGroup_singleton_unloadResourceGroup(int argc,VALUE *argv,VALUE self)
{
	VALUE groupname,reloadableOnly;
	rb_scan_args(argc, argv, "11",&groupname,&reloadableOnly);
	if(NIL_P(reloadableOnly))
		reloadableOnly = Qfalse;
	manager->unloadResourceGroup(rb_string_value_cstr(&groupname),RTEST(reloadableOnly));
	return self;
}
/*
*/
VALUE OgreResourceGroup_singleton_undeclareResource(int argc,VALUE *argv,VALUE self)
{
	VALUE file,groupname;
	rb_scan_args(argc, argv, "11",&file,&groupname);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(!NIL_P(groupname))
		result = rb_string_value_cstr(&groupname);
	manager->undeclareResource(result,rb_string_value_cstr(&file));
	return self;
}

/*
*/
VALUE OgreResourceGroup_singleton_each_ResourceManager(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	Ogre::ResourceGroupManager::ResourceManagerIterator map = manager->getResourceManagerIterator();
	for (Ogre::ResourceGroupManager::ResourceManagerIterator::iterator it = map.begin(); it != map.end(); ++it)
		rb_yield(wrap(it->first));
	return self;
}

void Init_OgreResourceGroup(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreResourceGroup = rb_define_class_under(rb_mOgre,"ResourceGroup",rb_cObject);
	rb_define_alloc_func(rb_cOgreResourceGroup,OgreResourceGroup_alloc);
	rb_define_private_method(rb_cOgreResourceGroup,"initialize_copy",RUBY_METHOD_FUNC(OgreResourceGroup_initialize_copy),1);
	
	rb_define_method(rb_cOgreResourceGroup,"initialize",RUBY_METHOD_FUNC(OgreResourceGroup_initialize),-1);
	rb_define_method(rb_cOgreResourceGroup,"locationExists?",RUBY_METHOD_FUNC(OgreResourceGroup_resourceLocationExists),1);

	rb_define_method(rb_cOgreResourceGroup,"addLocation",RUBY_METHOD_FUNC(OgreResourceGroup_addResourceLocation),-1);
	rb_define_method(rb_cOgreResourceGroup,"removeLocation",RUBY_METHOD_FUNC(OgreResourceGroup_removeResourceLocation),1);


	rb_define_method(rb_cOgreResourceGroup,"listResourceNames",RUBY_METHOD_FUNC(OgreResourceGroup_listResourceNames),1);
	rb_define_method(rb_cOgreResourceGroup,"listLocations",RUBY_METHOD_FUNC(OgreResourceGroup_listResourceLocations),0);
	rb_define_method(rb_cOgreResourceGroup,"listFileInfo",RUBY_METHOD_FUNC(OgreResourceGroup_listResourceFileInfo),-1);

	rb_define_method(rb_cOgreResourceGroup,"findLocation",RUBY_METHOD_FUNC(OgreResourceGroup_findResourceLocation),1);
	rb_define_method(rb_cOgreResourceGroup,"findFileInfo",RUBY_METHOD_FUNC(OgreResourceGroup_findResourceFileInfo),-1);
	
	rb_define_method(rb_cOgreResourceGroup,"clear",RUBY_METHOD_FUNC(OgreResourceGroup_clear),0);
	rb_define_method(rb_cOgreResourceGroup,"destroy",RUBY_METHOD_FUNC(OgreResourceGroup_destroy),0);
	rb_define_method(rb_cOgreResourceGroup,"initialise",RUBY_METHOD_FUNC(OgreResourceGroup_initialise),0);
	rb_define_method(rb_cOgreResourceGroup,"initialised?",RUBY_METHOD_FUNC(OgreResourceGroup_initialised),0);
	rb_define_method(rb_cOgreResourceGroup,"loaded?",RUBY_METHOD_FUNC(OgreResourceGroup_loaded),0);
	rb_define_method(rb_cOgreResourceGroup,"exist?",RUBY_METHOD_FUNC(OgreResourceGroup_exists),0);
	rb_define_method(rb_cOgreResourceGroup,"inGlobalPool?",RUBY_METHOD_FUNC(OgreResourceGroup_inGlobalPool),0);
	rb_define_method(rb_cOgreResourceGroup,"undeclareResource",RUBY_METHOD_FUNC(OgreResourceGroup_undeclareResource),1);
	rb_define_method(rb_cOgreResourceGroup,"unload",RUBY_METHOD_FUNC(OgreResourceGroup_unload),-1);

	rb_define_method(rb_cOgreResourceGroup,"openResource",RUBY_METHOD_FUNC(OgreResourceGroup_openResource),-1);
	rb_define_method(rb_cOgreResourceGroup,"openResources",RUBY_METHOD_FUNC(OgreResourceGroup_openResources),1);
	rb_define_method(rb_cOgreResourceGroup,"createResource",RUBY_METHOD_FUNC(OgreResourceGroup_createResource),-1);
	

	rb_define_singleton_method(rb_cOgreResourceGroup,"addLocation",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_addResourceLocation),-1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"removeLocation",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_removeResourceLocation),-1);

	rb_define_singleton_method(rb_cOgreResourceGroup,"locationExists?",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_resourceLocationExists),-1);

	rb_define_singleton_method(rb_cOgreResourceGroup,"listResourceNames",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_listResourceNames),-1);

	rb_define_singleton_method(rb_cOgreResourceGroup,"listLocations",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_listResourceLocations),-1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"listFileInfo",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_listResourceFileInfo),-1);

	rb_define_singleton_method(rb_cOgreResourceGroup,"findLocation",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_findResourceLocation),-1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"findFileInfo",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_findResourceFileInfo),-1);

	rb_define_singleton_method(rb_cOgreResourceGroup,"initialiseGroup",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_initialiseGroup),-1);

	rb_define_singleton_method(rb_cOgreResourceGroup,"getGroups",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_getResourceGroups),0);
	
	rb_define_singleton_method(rb_cOgreResourceGroup,"groupInitialised?",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_isResourceGroupInitialised),1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"groupLoaded?",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_isResourceGroupLoaded),1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"groupExists?",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_ResourceGroupExists),1);

	rb_define_singleton_method(rb_cOgreResourceGroup,"clearGroup",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_clearResourceGroup),1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"destroyGroup",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_destroyResourceGroup),1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"inGlobalPool?",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_isResourceGroupInGlobalPool),1);


	rb_define_singleton_method(rb_cOgreResourceGroup,"openResource",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_openResource),-1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"openResources",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_openResources),-1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"createResource",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_createResource),-1);


	rb_define_singleton_method(rb_cOgreResourceGroup,"unloadGroup",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_unloadResourceGroup),-1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"undeclareResource",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_undeclareResource),-1);
	
	rb_define_singleton_method(rb_cOgreResourceGroup,"each_ResourceManager",RUBY_METHOD_FUNC(OgreResourceGroup_singleton_each_ResourceManager),0);
}
