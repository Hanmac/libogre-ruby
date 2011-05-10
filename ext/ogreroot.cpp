#include "ogreroot.hpp"
#include "ogredatastream.hpp"
#include "ogreexception.hpp"
#include "ogrerenderwindow.hpp"
#include "ogrerendersystem.hpp"
#include "ogrescenemanager.hpp"
#define _self wrap<Ogre::Root*>(self)
VALUE rb_cOgreRoot;

std::vector<std::string> pluginFolder;

VALUE OgreRoot_alloc(VALUE self)
{
	return wrap(Ogre::Root::getSingletonPtr());
}

/*


*/
VALUE OgreRoot_addResourceLocation(int argc,VALUE *argv,VALUE self)
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
	Ogre::String result;
	if(NIL_P(insatanceName))
		result = Ogre::StringUtil::BLANK;
	else
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
	Ogre::SceneManagerEnumerator::MetaDataIterator map = _self->getSceneManagerMetaDataIterator();
	Ogre::SceneManagerEnumerator::MetaDataIterator::iterator it;
	for (it = map.begin(); it != map.end(); ++it) {
		rb_yield(wrap(*it));
	}
	return self;
}
/*

*/
void Init_OgreRoot(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_mSingleton = rb_define_module("Singleton");
#endif
	rb_cOgreRoot = rb_define_class_under(rb_mOgre,"Root",rb_cObject);
	rb_define_alloc_func(rb_cOgreRoot,OgreRoot_alloc);
	rb_funcall(rb_cOgreRoot,rb_intern("include"),1,rb_mSingleton);
	#if 0
	rb_include_module(rb_cOgreRoot,rb_mSingleton);
	#endif
	
	rb_define_singleton_method(rb_cOgreRoot,"method_missing",RUBY_METHOD_FUNC(OgreSingleton_method_missing),-1);// in ogre.y


	rb_define_method(rb_cOgreRoot,"addResourceLocation",RUBY_METHOD_FUNC(OgreRoot_addResourceLocation),-1);
	
	rb_define_method(rb_cOgreRoot,"removeResourceLocation",RUBY_METHOD_FUNC(OgreRoot_removeResourceLocation),-1);
	rb_define_method(rb_cOgreRoot,"hasMovableObjectFactory?",RUBY_METHOD_FUNC(OgreRoot_hasMovableObjectFactory),1);

	rb_define_method(rb_cOgreRoot,"createFileStream",RUBY_METHOD_FUNC(OgreRoot_createFileStream),-1);
	rb_define_method(rb_cOgreRoot,"openFileStream",RUBY_METHOD_FUNC(OgreRoot_openFileStream),-1);

	rb_define_method(rb_cOgreRoot,"createRenderWindow",RUBY_METHOD_FUNC(OgreRoot_createRenderWindow),-1);
	rb_define_method(rb_cOgreRoot,"getAvailableRenderers",RUBY_METHOD_FUNC(OgreRoot_getAvailableRenderers),0);
	rb_define_method(rb_cOgreRoot,"showConfigDialog",RUBY_METHOD_FUNC(OgreRoot_showConfigDialog),0);
	
	rb_define_method(rb_cOgreRoot,"rendersystem",RUBY_METHOD_FUNC(OgreRoot_getRenderSystem),0);
	rb_define_method(rb_cOgreRoot,"rendersystem=",RUBY_METHOD_FUNC(OgreRoot_setRenderSystem),1);
	rb_define_method(rb_cOgreRoot,"initialised?",RUBY_METHOD_FUNC(OgreRoot_isInitialised),0);

	rb_define_method(rb_cOgreRoot,"loadPlugin",RUBY_METHOD_FUNC(OgreRoot_loadPlugin),1);
	rb_define_method(rb_cOgreRoot,"unloadPlugin",RUBY_METHOD_FUNC(OgreRoot_unloadPlugin),1);
	
	rb_define_method(rb_cOgreRoot,"addPluginFolder",RUBY_METHOD_FUNC(OgreRoot_addPluginFolder),1);
	rb_define_method(rb_cOgreRoot,"pluginfolders",RUBY_METHOD_FUNC(OgreRoot_listPluginFolders),0);
	rb_define_method(rb_cOgreRoot,"each_metadata",RUBY_METHOD_FUNC(OgreRoot_each_metadata),0);

	rb_define_method(rb_cOgreRoot,"createSceneManager",RUBY_METHOD_FUNC(OgreRoot_createSceneManager),-1);
}
