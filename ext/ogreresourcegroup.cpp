#include "ogreresourcegroup.hpp"
#include "ogreresource.hpp"
#include "ogrefileinfo.hpp"
#include "ogredatastream.hpp"
#include "ogreexception.hpp"
#define selfname wrap<RubyResourceGroup*>(self)->name
#define manager Ogre::ResourceGroupManager::getSingletonPtr()
VALUE rb_cOgreResourceGroup;


template <>
VALUE wrap< RubyResourceGroup >(RubyResourceGroup *resgroup )
{
	return Data_Wrap_Struct(rb_cOgreResourceGroup, NULL, free, resgroup);
}

template <>
RubyResourceGroup* wrap< RubyResourceGroup* >(const VALUE &vresgroup)
{
	return unwrapPtr<RubyResourceGroup>(vresgroup, rb_cOgreResourceGroup);
}


namespace RubyOgre {
namespace ResourceGroup {

VALUE _alloc(VALUE self)
{
	return wrap(new RubyResourceGroup);
}
/*
*/
VALUE _initialize(int argc, VALUE *argv,VALUE self)
{
	VALUE name,inGlobalPool;
	rb_scan_args(argc, argv, "11",&name,&inGlobalPool);
	if(NIL_P(inGlobalPool))
		inGlobalPool = Qtrue;
	selfname = wrap<Ogre::String>(name);
	if(!manager->resourceGroupExists(selfname))
		manager->createResourceGroup(selfname,RTEST(inGlobalPool));
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	selfname = wrap<RubyResourceGroup*>(other)->name;
	return result;
}

/*
*/
VALUE _addResourceLocation(int argc,VALUE *argv,VALUE self)
{
	VALUE path,type,recursive;
	rb_scan_args(argc, argv, "21",&path,&type,&recursive);
	Ogre::String result;
	RUBYTRY(manager->addResourceLocation(wrap<Ogre::String>(path),wrap<Ogre::String>(type),selfname,RTEST(recursive));)
	return self;
}
/*
*/
VALUE _removeResourceLocation(VALUE self,VALUE name)
{
	RUBYTRY(manager->removeResourceLocation(wrap<Ogre::String>(name),selfname););
	return self;
}
/*
*/
VALUE _resourceLocationExists(VALUE self,VALUE name)
{
	return manager->resourceLocationExists(wrap<Ogre::String>(name),selfname) ? Qtrue : Qfalse;
}
/*
*/
VALUE _listResourceNames(int argc,VALUE *argv,VALUE self)
{
	VALUE dirs;
	rb_scan_args(argc, argv, "01",&dirs);
	return wrap<Ogre::String>(manager->listResourceNames(selfname,RTEST(dirs)));	
}
/*
*/
VALUE _listResourceLocations(VALUE self)
{
	return wrap<Ogre::String>(manager->listResourceLocations(selfname));
}
/*
*/
VALUE _listResourceFileInfo(int argc,VALUE *argv,VALUE self)
{
	VALUE dirs;
	rb_scan_args(argc, argv, "01",&dirs);
	if(NIL_P(dirs))
		dirs = Qfalse;
	return wrap<Ogre::FileInfo>(manager->listResourceFileInfo(selfname,RTEST(dirs)));
}
/*
*/
VALUE _findResourceLocation(VALUE self,VALUE pattern)
{
	return wrap<Ogre::String>(manager->findResourceLocation(selfname,wrap<Ogre::String>(pattern)));
}
/*
*/
VALUE _findResourceFileInfo(int argc,VALUE *argv,VALUE self)
{
	VALUE pattern,dirs;
	rb_scan_args(argc, argv, "11",&pattern,&dirs);
	if(NIL_P(dirs))
		dirs = Qfalse;
	return wrap<Ogre::FileInfo>(manager->findResourceFileInfo(selfname,wrap<Ogre::String>(pattern),RTEST(dirs)));
}
/*
*/
VALUE _initialised(VALUE self)
{
	return manager->isResourceGroupInitialised(selfname) ? Qtrue : Qfalse;
}
/*
*/
VALUE _loaded(VALUE self)
{
	return manager->isResourceGroupLoaded(selfname) ? Qtrue : Qfalse;
}
/*
*/
VALUE _exists(VALUE self)
{
	return manager->resourceGroupExists(selfname) ? Qtrue : Qfalse;
}
/*
*/
VALUE _clear(VALUE self)
{
	manager->clearResourceGroup(selfname);
	return self;
}
/*
*/
VALUE _destroy(VALUE self)
{
	manager->destroyResourceGroup(selfname);
	return self;
}
/*
*/
VALUE _inGlobalPool(VALUE self)
{
	return manager->isResourceGroupInGlobalPool(selfname) ? Qtrue : Qfalse;
}
/*
*/
VALUE _undeclareResource(VALUE self,VALUE name)
{
	manager->undeclareResource(selfname,wrap<Ogre::String>(name));
	return self;
}
/*

*/
VALUE _unload(int argc,VALUE *argv,VALUE self)
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
VALUE _openResource(int argc,VALUE *argv,VALUE self)
{
	VALUE file,notfound;
	rb_scan_args(argc, argv, "11",&file,&notfound);
	if(NIL_P(notfound))
		notfound = Qtrue;
	Ogre::Resource *res=NULL;
	Ogre::DataStreamPtr ptr = manager->openResource(wrap<Ogre::String>(file),selfname,RTEST(notfound),res);
	VALUE result = rb_ary_new();
	rb_ary_push(result,wrap(ptr));
	rb_ary_push(result,wrap(res));
	return result;
}
/*
*/
VALUE _openResources(VALUE self,VALUE file)
{
	return wrap<Ogre::DataStreamPtr>(manager->openResources(wrap<Ogre::String>(file),selfname));
}
/*
*/
VALUE _createResource(int argc,VALUE *argv,VALUE self)
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
		locationPattern = wrap<Ogre::String>(temp);
	RUBYTRY(return wrap(manager->createResource(wrap<Ogre::String>(file),selfname,overwrite,locationPattern));)
	return Qnil;
}

//void initialiseResourceGroup(const String& name);

/*
*/
VALUE _initialise(VALUE self)
{
	RUBYTRY(manager->initialiseResourceGroup(selfname););
	return self;
}



//singleton

/*
*/
VALUE _singleton_listResourceNames(int argc,VALUE *argv,VALUE self)
{
	VALUE groupname,dirs;
	rb_scan_args(argc, argv, "01",&dirs);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(groupname == Qtrue || groupname == Qfalse){
		dirs = groupname;
		groupname = Qnil;
	}
	if(!NIL_P(groupname))
		result = wrap<Ogre::String>(groupname);
	if(NIL_P(dirs))
		dirs = Qfalse;
	return wrap<Ogre::String>(manager->listResourceNames(result,RTEST(dirs)));
}
/*
*/
VALUE _singleton_addResourceLocation(int argc,VALUE *argv,VALUE self)
{
	VALUE path,type,resGroup,recursive;
	rb_scan_args(argc, argv, "22",&path,&type,&resGroup,&recursive);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(NIL_P(resGroup))
		result = wrap<Ogre::String>(resGroup);
	RUBYTRY(manager->addResourceLocation(wrap<Ogre::String>(path),wrap<Ogre::String>(type),result,RTEST(recursive));)
	return self;
}
/*
*/
VALUE _singleton_removeResourceLocation(int argc,VALUE *argv,VALUE self)
{
	VALUE name,resGroup;
	rb_scan_args(argc, argv, "11",&name,&resGroup);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(!NIL_P(resGroup))
		result = wrap<Ogre::String>(resGroup);
	manager->removeResourceLocation(wrap<Ogre::String>(name),result);
	return self;
}
/*
*/
VALUE _singleton_listResourceLocations(int argc,VALUE *argv,VALUE self)
{
	VALUE groupname;
	rb_scan_args(argc, argv, "01",&groupname);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(!NIL_P(groupname))
		result = wrap<Ogre::String>(groupname);
	return wrap<Ogre::String>(manager->listResourceLocations(result));
}
/*
*/
VALUE _singleton_findResourceLocation(int argc,VALUE *argv,VALUE self)
{
	VALUE pattern,groupname;
	rb_scan_args(argc, argv, "11",&pattern,&groupname);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(!NIL_P(groupname))
		result = wrap<Ogre::String>(groupname);
	return wrap<Ogre::String>(manager->findResourceLocation(result,wrap<Ogre::String>(pattern)));
}
/*
*/
VALUE _singleton_findResourceFileInfo(int argc,VALUE *argv,VALUE self)
{
	VALUE pattern,groupname,dirs;
	rb_scan_args(argc, argv, "12",&pattern,&groupname,&dirs);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(groupname == Qtrue || groupname == Qfalse){
		dirs = groupname;
		groupname = Qnil;
	}
	if(!NIL_P(groupname))
		result = wrap<Ogre::String>(groupname);
	if(NIL_P(dirs))
		dirs = Qfalse;
	return wrap<Ogre::FileInfo>(manager->findResourceFileInfo(result,wrap<Ogre::String>(pattern),RTEST(dirs)));
}
/*
*/
VALUE _singleton_listResourceFileInfo(int argc,VALUE *argv,VALUE self)
{
	VALUE groupname,dirs;
	rb_scan_args(argc, argv, "02",&groupname,&dirs);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(groupname == Qtrue || groupname == Qfalse){
		dirs = groupname;
		groupname = Qnil;
	}
	if(!NIL_P(groupname))
		result = wrap<Ogre::String>(groupname);
	if(NIL_P(dirs))
		dirs = Qfalse;
	return wrap<Ogre::FileInfo>(manager->listResourceFileInfo(result,RTEST(dirs)));
}

/*
*/
VALUE _singleton_resourceLocationExists(int argc,VALUE *argv,VALUE self)
{
	VALUE name,resGroup;
	rb_scan_args(argc, argv, "11",&name,&resGroup);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(!NIL_P(resGroup))
		result = wrap<Ogre::String>(resGroup);
	return manager->resourceLocationExists(wrap<Ogre::String>(name),result) ? Qtrue : Qfalse;
}
/*
*/
VALUE _singleton_initialiseGroup(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	RUBYTRY(
		if(NIL_P(name))
			manager->initialiseAllResourceGroups();
		else
			manager->initialiseResourceGroup(wrap<Ogre::String>(name));
	)
	return self;
}

/*
*/
VALUE _singleton_isResourceGroupInitialised(VALUE self,VALUE name)
{
	return manager->isResourceGroupInitialised(wrap<Ogre::String>(name)) ? Qtrue : Qfalse;
}
/*
*/
VALUE _singleton_isResourceGroupLoaded(VALUE self,VALUE name)
{
	return manager->isResourceGroupLoaded(wrap<Ogre::String>(name)) ? Qtrue : Qfalse;
}
/*
*/
VALUE _singleton_ResourceGroupExists(VALUE self,VALUE name)
{
	return manager->resourceGroupExists(wrap<Ogre::String>(name)) ? Qtrue : Qfalse;
}

/*
*/
VALUE _singleton_getResourceGroups(VALUE self)
{
	return wrap<Ogre::String>(manager->getResourceGroups());
}
/*
*/
VALUE _singleton_clearResourceGroup(VALUE self,VALUE name)
{
	manager->clearResourceGroup(wrap<Ogre::String>(name));
	return self;
}
/*
*/
VALUE _singleton_destroyResourceGroup(VALUE self,VALUE name)
{
	manager->destroyResourceGroup(wrap<Ogre::String>(name));
	return self;
}
/*
*/
VALUE _singleton_isResourceGroupInGlobalPool(VALUE self,VALUE name)
{
	return manager->isResourceGroupInGlobalPool(wrap<Ogre::String>(name)) ? Qtrue : Qfalse;
}

/*
*/
VALUE _singleton_openResource(int argc,VALUE *argv,VALUE self)
{
	VALUE file,groupname,notfound;
	rb_scan_args(argc, argv, "12",&file,&groupname,&notfound);
	Ogre::String cgroupname = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;;
	if(!NIL_P(groupname))
		cgroupname = wrap<Ogre::String>(groupname);
	if(NIL_P(notfound))
		notfound = Qtrue;
	Ogre::Resource *res=NULL;
	Ogre::DataStreamPtr ptr = manager->openResource(wrap<Ogre::String>(file),cgroupname,RTEST(notfound),res);
	VALUE result = rb_ary_new();
	rb_ary_push(result,wrap(ptr));
	rb_ary_push(result,wrap(res));
	return result;
}

/*
*/
VALUE _singleton_openResources(int argc,VALUE *argv,VALUE self)
{
	VALUE file,groupname;
	rb_scan_args(argc, argv, "11",&file,&groupname);
	Ogre::String result;
	if(NIL_P(groupname))
		result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	else
		result = wrap<Ogre::String>(groupname);
	return wrap<Ogre::DataStreamPtr>(manager->openResources(wrap<Ogre::String>(file),result));
}
/*
*/
VALUE _singleton_createResource(int argc,VALUE *argv,VALUE self)
{
	VALUE file,hash,temp;
	bool overwrite = false;
	rb_scan_args(argc, argv, "11",&file,&hash);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	Ogre::String locationPattern =  Ogre::StringUtil::BLANK;
	if(rb_obj_is_kind_of(hash,rb_cHash) && !NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("group_name")))))
		result = wrap<Ogre::String>(temp);
	if(rb_obj_is_kind_of(hash,rb_cHash) && !NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("overwrite")))))
		overwrite = RTEST(temp);
	if(rb_obj_is_kind_of(hash,rb_cHash) && !NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("pattern")))))
		locationPattern = wrap<Ogre::String>(temp);
	RUBYTRY(return wrap(manager->createResource(wrap<Ogre::String>(file),result,overwrite,locationPattern));)
	return Qnil;
}
/*
*/
VALUE _singleton_unloadResourceGroup(int argc,VALUE *argv,VALUE self)
{
	VALUE groupname,reloadableOnly;
	rb_scan_args(argc, argv, "11",&groupname,&reloadableOnly);
	if(NIL_P(reloadableOnly))
		reloadableOnly = Qfalse;
	manager->unloadResourceGroup(wrap<Ogre::String>(groupname),RTEST(reloadableOnly));
	return self;
}
/*
*/
VALUE _singleton_undeclareResource(int argc,VALUE *argv,VALUE self)
{
	VALUE file,groupname;
	rb_scan_args(argc, argv, "11",&file,&groupname);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(!NIL_P(groupname))
		result = wrap<Ogre::String>(groupname);
	manager->undeclareResource(result,wrap<Ogre::String>(file));
	return self;
}

/*
*/
VALUE _singleton_each_ResourceManager(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	Ogre::ResourceGroupManager::ResourceManagerIterator map = manager->getResourceManagerIterator();
	for (Ogre::ResourceGroupManager::ResourceManagerIterator::iterator it = map.begin(); it != map.end(); ++it)
		rb_yield(wrap(it->first));
	return self;
}

}}

void Init_OgreResourceGroup(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	using namespace RubyOgre::ResourceGroup;

	rb_cOgreResourceGroup = rb_define_class_under(rb_mOgre,"ResourceGroup",rb_cObject);
	rb_define_alloc_func(rb_cOgreResourceGroup,_alloc);
	rb_define_private_method(rb_cOgreResourceGroup,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);
	
	rb_define_method(rb_cOgreResourceGroup,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_method(rb_cOgreResourceGroup,"locationExists?",RUBY_METHOD_FUNC(_resourceLocationExists),1);

	rb_define_method(rb_cOgreResourceGroup,"addLocation",RUBY_METHOD_FUNC(_addResourceLocation),-1);
	rb_define_method(rb_cOgreResourceGroup,"removeLocation",RUBY_METHOD_FUNC(_removeResourceLocation),1);


	rb_define_method(rb_cOgreResourceGroup,"listResourceNames",RUBY_METHOD_FUNC(_listResourceNames),1);
	rb_define_method(rb_cOgreResourceGroup,"listLocations",RUBY_METHOD_FUNC(_listResourceLocations),0);
	rb_define_method(rb_cOgreResourceGroup,"listFileInfo",RUBY_METHOD_FUNC(_listResourceFileInfo),-1);

	rb_define_method(rb_cOgreResourceGroup,"findLocation",RUBY_METHOD_FUNC(_findResourceLocation),1);
	rb_define_method(rb_cOgreResourceGroup,"findFileInfo",RUBY_METHOD_FUNC(_findResourceFileInfo),-1);
	
	rb_define_method(rb_cOgreResourceGroup,"clear",RUBY_METHOD_FUNC(_clear),0);
	rb_define_method(rb_cOgreResourceGroup,"destroy",RUBY_METHOD_FUNC(_destroy),0);
	rb_define_method(rb_cOgreResourceGroup,"initialise",RUBY_METHOD_FUNC(_initialise),0);
	rb_define_method(rb_cOgreResourceGroup,"initialised?",RUBY_METHOD_FUNC(_initialised),0);
	rb_define_method(rb_cOgreResourceGroup,"loaded?",RUBY_METHOD_FUNC(_loaded),0);
	rb_define_method(rb_cOgreResourceGroup,"exist?",RUBY_METHOD_FUNC(_exists),0);
	rb_define_method(rb_cOgreResourceGroup,"inGlobalPool?",RUBY_METHOD_FUNC(_inGlobalPool),0);
	rb_define_method(rb_cOgreResourceGroup,"undeclareResource",RUBY_METHOD_FUNC(_undeclareResource),1);
	rb_define_method(rb_cOgreResourceGroup,"unload",RUBY_METHOD_FUNC(_unload),-1);

	rb_define_method(rb_cOgreResourceGroup,"openResource",RUBY_METHOD_FUNC(_openResource),-1);
	rb_define_method(rb_cOgreResourceGroup,"openResources",RUBY_METHOD_FUNC(_openResources),1);
	rb_define_method(rb_cOgreResourceGroup,"createResource",RUBY_METHOD_FUNC(_createResource),-1);
	

	rb_define_singleton_method(rb_cOgreResourceGroup,"addLocation",RUBY_METHOD_FUNC(_singleton_addResourceLocation),-1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"removeLocation",RUBY_METHOD_FUNC(_singleton_removeResourceLocation),-1);

	rb_define_singleton_method(rb_cOgreResourceGroup,"locationExists?",RUBY_METHOD_FUNC(_singleton_resourceLocationExists),-1);

	rb_define_singleton_method(rb_cOgreResourceGroup,"listResourceNames",RUBY_METHOD_FUNC(_singleton_listResourceNames),-1);

	rb_define_singleton_method(rb_cOgreResourceGroup,"listLocations",RUBY_METHOD_FUNC(_singleton_listResourceLocations),-1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"listFileInfo",RUBY_METHOD_FUNC(_singleton_listResourceFileInfo),-1);

	rb_define_singleton_method(rb_cOgreResourceGroup,"findLocation",RUBY_METHOD_FUNC(_singleton_findResourceLocation),-1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"findFileInfo",RUBY_METHOD_FUNC(_singleton_findResourceFileInfo),-1);

	rb_define_singleton_method(rb_cOgreResourceGroup,"initialiseGroup",RUBY_METHOD_FUNC(_singleton_initialiseGroup),-1);

	rb_define_singleton_method(rb_cOgreResourceGroup,"getGroups",RUBY_METHOD_FUNC(_singleton_getResourceGroups),0);
	
	rb_define_singleton_method(rb_cOgreResourceGroup,"groupInitialised?",RUBY_METHOD_FUNC(_singleton_isResourceGroupInitialised),1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"groupLoaded?",RUBY_METHOD_FUNC(_singleton_isResourceGroupLoaded),1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"groupExists?",RUBY_METHOD_FUNC(_singleton_ResourceGroupExists),1);

	rb_define_singleton_method(rb_cOgreResourceGroup,"clearGroup",RUBY_METHOD_FUNC(_singleton_clearResourceGroup),1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"destroyGroup",RUBY_METHOD_FUNC(_singleton_destroyResourceGroup),1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"inGlobalPool?",RUBY_METHOD_FUNC(_singleton_isResourceGroupInGlobalPool),1);


	rb_define_singleton_method(rb_cOgreResourceGroup,"openResource",RUBY_METHOD_FUNC(_singleton_openResource),-1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"openResources",RUBY_METHOD_FUNC(_singleton_openResources),-1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"createResource",RUBY_METHOD_FUNC(_singleton_createResource),-1);


	rb_define_singleton_method(rb_cOgreResourceGroup,"unloadGroup",RUBY_METHOD_FUNC(_singleton_unloadResourceGroup),-1);
	rb_define_singleton_method(rb_cOgreResourceGroup,"undeclareResource",RUBY_METHOD_FUNC(_singleton_undeclareResource),-1);
	
	rb_define_singleton_method(rb_cOgreResourceGroup,"each_ResourceManager",RUBY_METHOD_FUNC(_singleton_each_ResourceManager),0);
}
