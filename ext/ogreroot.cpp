#include "ogreroot.hpp"
#include "ogredatastream.hpp"
#include "ogreexception.hpp"
#include "ogrerenderwindow.hpp"
#include "ogrerendersystem.hpp"
#include "ogrescenemanager.hpp"
#define _self wrap<Ogre::Root*>(self)
VALUE rb_mOgreRoot;

std::vector<std::string> pluginFolder;
Ogre::Root *root;
/*
*/
VALUE OgreRoot_addResourceLocation(int argc,VALUE *argv,VALUE self)
{
	VALUE path,type,resGroup,recursive;
	rb_scan_args(argc, argv, "22",&path,&type,&resGroup,&recursive);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(!NIL_P(resGroup))
		result = rb_string_value_cstr(&resGroup);
	try{
		_self->addResourceLocation(rb_string_value_cstr(&path),rb_string_value_cstr(&type),result,RTEST(recursive));
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
	return self;
}
/*
*/
VALUE OgreRoot_removeResourceLocation(int argc,VALUE *argv,VALUE self)
{
	VALUE name,resGroup;
	rb_scan_args(argc, argv, "11",&name,&resGroup);
	Ogre::String result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	if(!NIL_P(resGroup))
		result = rb_string_value_cstr(&resGroup);
	_self->removeResourceLocation(rb_string_value_cstr(&name),result);
	return self;
}
/*
*/
VALUE OgreRoot_hasMovableObjectFactory(VALUE self,VALUE typeName)
{
	return _self->hasMovableObjectFactory(rb_string_value_cstr(&typeName)) ? Qtrue : Qfalse;
}
/*
*/
VALUE OgreRoot_isInitialised(VALUE self)
{
	return _self->isInitialised() ? Qtrue : Qfalse;
}
/*
*/
VALUE OgreRoot_createFileStream(int argc,VALUE *argv,VALUE self)
{
	VALUE name,hash,temp;
	rb_scan_args(argc, argv, "11",&name,&hash);
	Ogre::String groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	Ogre::String pattern = Ogre::StringUtil::BLANK;
	bool overwrite=false;

	if(rb_obj_is_kind_of(hash,rb_cHash) && !NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("group_name")))))
		groupName = rb_string_value_cstr(&temp);
	if(rb_obj_is_kind_of(hash,rb_cHash) && !NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("overwrite")))))
		overwrite = RTEST(temp);
	if(rb_obj_is_kind_of(hash,rb_cHash) && !NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("pattern")))))
		pattern = rb_string_value_cstr(&temp);
	
	return wrap(_self->createFileStream(rb_string_value_cstr(&name),groupName,overwrite,pattern));
}
/*
*/
VALUE OgreRoot_openFileStream(int argc,VALUE *argv,VALUE self)
{
	VALUE name,hash,temp;
	rb_scan_args(argc, argv, "11",&name,&hash);
	Ogre::String groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	Ogre::String pattern = Ogre::StringUtil::BLANK;

	if(rb_obj_is_kind_of(hash,rb_cHash) && !NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("group_name")))))
		groupName = rb_string_value_cstr(&temp);
	if(rb_obj_is_kind_of(hash,rb_cHash) && !NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("pattern")))))
		pattern = rb_string_value_cstr(&temp);
	
	return wrap(_self->openFileStream(rb_string_value_cstr(&name),groupName,pattern));
}
/*
*/
VALUE OgreRoot_createRenderWindow(int argc,VALUE *argv,VALUE self)
{
	VALUE autoCreate,name;
	rb_scan_args(argc, argv, "20",&autoCreate,&name);
	try{
		return wrap(_self->initialise(RTEST(autoCreate),rb_string_value_cstr(&name),Ogre::StringUtil::BLANK));
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
	return Qnil;
}
/*
*/
VALUE OgreRoot_getAvailableRenderers(VALUE self)
{
	return wrap<Ogre::RenderSystem>(_self->getAvailableRenderers());
}
/*
*/
VALUE OgreRoot_getRenderSystem(VALUE self)
{
	Ogre::RenderSystem *system = _self->getRenderSystem();
	return system ? wrap(system) : Qnil;
}

/*
*/
VALUE OgreRoot_setRenderSystem(VALUE self,VALUE system)
{
	if(rb_obj_is_kind_of(system,rb_cString))
		_self->setRenderSystem(_self->getRenderSystemByName(rb_string_value_cstr(&system)));
	else if(rb_obj_is_kind_of(system,rb_cOgreRenderSystem))
		_self->setRenderSystem(wrap<Ogre::RenderSystem*>(system));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreRenderSystem),rb_obj_classname(system));
	return system;
}

/*
*/
VALUE OgreRoot_showConfigDialog(VALUE self)
{
	return _self->showConfigDialog() ? Qtrue : Qfalse;
}
/*
*/
VALUE OgreRoot_loadPlugin(VALUE self,VALUE val)
{
	try{
		_self->loadPlugin(rb_string_value_cstr(&val));
	}catch(Ogre::Exception& e){
		bool found = false;
		for (std::vector<std::string>::iterator it = pluginFolder.begin(); it != pluginFolder.end(); ++it){
			try{
				_self->loadPlugin(*it + rb_string_value_cstr(&val));
				found = true;
			}catch(Ogre::Exception& f){
			}
		}
		if(!found)
			rb_raise(wrap(e));
	}
	return self;
}
/*
*/
VALUE OgreRoot_addPluginFolder(VALUE self,VALUE path)
{
	std::string str = rb_string_value_cstr(&path);
	if(str[str.length()-1] != '/')
		str.push_back('/');
	pluginFolder.push_back(str);
	return self;
}
/*
*/
VALUE OgreRoot_listPluginFolders(VALUE self)
{
	return wrap<std::string>(pluginFolder);
}
/*
*/
VALUE OgreRoot_listPlugins(VALUE self)
{
	return wrap<Ogre::Plugin>(_self->getInstalledPlugins());
}


/*
*/
VALUE OgreRoot_unloadPlugin(VALUE self,VALUE val)
{
	try{
		_self->unloadPlugin(rb_string_value_cstr(&val));
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
	return self;
}

/*
*/
VALUE OgreRoot_createSceneManager(int argc,VALUE *argv,VALUE self)
{
	VALUE typeName,insatanceName;
	rb_scan_args(argc, argv, "11",&typeName,&insatanceName);
	Ogre::String result = Ogre::StringUtil::BLANK;
	if(!NIL_P(insatanceName))
		result = rb_string_value_cstr(&insatanceName);
	try{
		return wrap(_self->createSceneManager(rb_string_value_cstr(&typeName),result));
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
	return Qnil;
}
/*
*/
VALUE OgreRoot_each_metadata(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<const Ogre::SceneManagerMetaData*>(_self->getSceneManagerMetaDataIterator());
	return self;
}
/*
*/
VALUE OgreRoot_each_sceneManager(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::String,Ogre::SceneManager*>(_self->getSceneManagerIterator());
	return self;
}

/*
 * Document-module: Ogre
 * 
 * This module hould the Ogre classes and modules. it has the methods of Root as singleton
*/
void Init_OgreRoot(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_define_singleton_method(rb_mOgre,"addResourceLocation",RUBY_METHOD_FUNC(OgreRoot_addResourceLocation),-1);
	
	rb_define_singleton_method(rb_mOgre,"removeResourceLocation",RUBY_METHOD_FUNC(OgreRoot_removeResourceLocation),-1);
	rb_define_singleton_method(rb_mOgre,"hasMovableObjectFactory?",RUBY_METHOD_FUNC(OgreRoot_hasMovableObjectFactory),1);

	rb_define_singleton_method(rb_mOgre,"createFileStream",RUBY_METHOD_FUNC(OgreRoot_createFileStream),-1);
	rb_define_singleton_method(rb_mOgre,"openFileStream",RUBY_METHOD_FUNC(OgreRoot_openFileStream),-1);

	rb_define_singleton_method(rb_mOgre,"createRenderWindow",RUBY_METHOD_FUNC(OgreRoot_createRenderWindow),-1);
	rb_define_singleton_method(rb_mOgre,"getAvailableRenderers",RUBY_METHOD_FUNC(OgreRoot_getAvailableRenderers),0);
	rb_define_singleton_method(rb_mOgre,"showConfigDialog",RUBY_METHOD_FUNC(OgreRoot_showConfigDialog),0);
	
	rb_define_singleton_method(rb_mOgre,"rendersystem",RUBY_METHOD_FUNC(OgreRoot_getRenderSystem),0);
	rb_define_singleton_method(rb_mOgre,"rendersystem=",RUBY_METHOD_FUNC(OgreRoot_setRenderSystem),1);
	rb_define_singleton_method(rb_mOgre,"initialised?",RUBY_METHOD_FUNC(OgreRoot_isInitialised),0);

	rb_define_singleton_method(rb_mOgre,"loadPlugin",RUBY_METHOD_FUNC(OgreRoot_loadPlugin),1);
	rb_define_singleton_method(rb_mOgre,"unloadPlugin",RUBY_METHOD_FUNC(OgreRoot_unloadPlugin),1);
	
	rb_define_singleton_method(rb_mOgre,"addPluginFolder",RUBY_METHOD_FUNC(OgreRoot_addPluginFolder),1);
	rb_define_singleton_method(rb_mOgre,"pluginfolders",RUBY_METHOD_FUNC(OgreRoot_listPluginFolders),0);
	rb_define_singleton_method(rb_mOgre,"plugins",RUBY_METHOD_FUNC(OgreRoot_listPlugins),0);
	
	rb_define_singleton_method(rb_mOgre,"each_metadata",RUBY_METHOD_FUNC(OgreRoot_each_metadata),0);
	rb_define_singleton_method(rb_mOgre,"each_sceneManager",RUBY_METHOD_FUNC(OgreRoot_each_sceneManager),0);

	rb_define_singleton_method(rb_mOgre,"createSceneManager",RUBY_METHOD_FUNC(OgreRoot_createSceneManager),-1);
}
