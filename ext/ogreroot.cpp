#include "ogreroot.hpp"
#include "ogreresource.hpp"
#include "ogredatastream.hpp"
#include "ogreexception.hpp"
#include "ogrerenderwindow.hpp"
#include "ogrerendersystem.hpp"
#include "ogrescenemanager.hpp"
#include "ogreframelistener.hpp"

#define _self wrap<Ogre::Root*>(self)
VALUE rb_mOgreRoot;

std::vector<std::string> pluginFolder;
Ogre::Root *root;

template <>
VALUE wrap< Ogre::Plugin >(Ogre::Plugin *man )
{
	return wrap(man->getName());
}
template <>
Ogre::Root* wrap< Ogre::Root* >(const VALUE &vvector)
{
	if(root==NULL)
		root = new Ogre::Root();
	return Ogre::Root::getSingletonPtr();
}

namespace RubyOgre {
namespace Root {

singlereturn(showConfigDialog)
singlefunc(saveConfig)
singlereturn(restoreConfig)

singlereturn(getRenderSystem)
singlereturn(isInitialised)

singlefunc(startRendering)
singlefunc(shutdown)

/*
*/
VALUE _addResourceLocation(int argc,VALUE *argv,VALUE self)
{
	VALUE path,type,resGroup,recursive;
	rb_scan_args(argc, argv, "22",&path,&type,&resGroup,&recursive);

	RUBYTRY(
		_self->addResourceLocation(wrap< Ogre::String >(path),
			wrap< Ogre::String >(type),
			unwrapResourceGroup(resGroup,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME),
			RTEST(recursive)
		);
	)
	return self;
}
/*
*/
VALUE _removeResourceLocation(int argc,VALUE *argv,VALUE self)
{
	VALUE name,resGroup;
	rb_scan_args(argc, argv, "11",&name,&resGroup);
	_self->removeResourceLocation(wrap< Ogre::String >(name),
		unwrapResourceGroup(resGroup,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME)
	);
	return self;
}
/*
*/
VALUE _hasMovableObjectFactory(VALUE self,VALUE typeName)
{
	return wrap(_self->hasMovableObjectFactory(wrap< Ogre::String >(typeName)));
}

/*
*/
VALUE _createFileStream(int argc,VALUE *argv,VALUE self)
{
	VALUE name,hash,temp;
	rb_scan_args(argc, argv, "11",&name,&hash);
	Ogre::String groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	Ogre::String pattern = Ogre::StringUtil::BLANK;
	bool overwrite=false;
	RUBYTRY(
	if(rb_obj_is_kind_of(hash,rb_cHash))
	{
		temp = rb_hash_aref(hash,ID2SYM(rb_intern("group_name")));
		groupName = unwrapResourceGroup(temp,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("overwrite")))))
			overwrite = RTEST(temp);
		if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("pattern")))))
			pattern = wrap< Ogre::String >(temp);
	}

	return wrap(_self->createFileStream(wrap< Ogre::String >(name),groupName,overwrite,pattern));
	)
	return Qnil;
}
/*
*/
VALUE _openFileStream(int argc,VALUE *argv,VALUE self)
{
	VALUE name,hash,temp;
	rb_scan_args(argc, argv, "11",&name,&hash);
	Ogre::String groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	Ogre::String pattern = Ogre::StringUtil::BLANK;
	RUBYTRY(
	if(rb_obj_is_kind_of(hash,rb_cHash))
	{
		temp = rb_hash_aref(hash,ID2SYM(rb_intern("group_name")));
		groupName = unwrapResourceGroup(temp,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("pattern")))))
			pattern = wrap< Ogre::String >(temp);
	}
	return wrap(_self->openFileStream(wrap< Ogre::String >(name),groupName,pattern));
	)
	return Qnil;
}
/*
*/
VALUE _createRenderWindow(int argc,VALUE *argv,VALUE self)
{
	VALUE autoCreate,name;
	rb_scan_args(argc, argv, "20",&autoCreate,&name);
	RUBYTRY(
		return wrap(_self->initialise(RTEST(autoCreate),wrap< Ogre::String >(name)));
	)
	return Qnil;
}
/*
*/
VALUE _getAvailableRenderers(VALUE self)
{
	return wrap<Ogre::RenderSystem>(_self->getAvailableRenderers());
}

/*
*/
VALUE _setRenderSystem(VALUE self,VALUE system)
{
	if(rb_obj_is_kind_of(system,rb_cString))
		_self->setRenderSystem(_self->getRenderSystemByName(wrap< Ogre::String >(system)));
	else
		_self->setRenderSystem(wrap<Ogre::RenderSystem*>(system));
	return system;
}

/*
*/
VALUE _loadPlugin(VALUE self,VALUE val)
{
	try{
		_self->loadPlugin(wrap< Ogre::String >(val));
	}catch(Ogre::Exception& e){
		bool found = false;
		for (std::vector<std::string>::iterator it = pluginFolder.begin(); it != pluginFolder.end(); ++it){
			try{
				_self->loadPlugin(*it + wrap< Ogre::String >(val));
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
 *
 */

VALUE _addFrameListener(VALUE self,VALUE obj)
{
	_self->addFrameListener(wrap<Ogre::FrameListener*>(obj));
	return self;
}

/*
*/
VALUE _addPluginFolder(VALUE self,VALUE path)
{
	std::string str = wrap< Ogre::String >(path);
	if(str[str.length()-1] != '/')
		str.push_back('/');
	pluginFolder.push_back(str);
	return self;
}
/*
*/
VALUE _listPluginFolders(VALUE self)
{
	return wrap<std::string>(pluginFolder);
}
/*
*/
VALUE _listPlugins(VALUE self)
{
	return wrap<Ogre::Plugin>(_self->getInstalledPlugins());
}


/*
*/
VALUE _unloadPlugin(VALUE self,VALUE val)
{
	RUBYTRY(_self->unloadPlugin(wrap< Ogre::String >(val));)
	return self;
}

/*
*/
VALUE _createSceneManager(int argc,VALUE *argv,VALUE self)
{
	VALUE typeName,instanceName;
	rb_scan_args(argc, argv, "11",&typeName,&instanceName);
	Ogre::String result;
	if(!NIL_P(instanceName))
		result = wrap< Ogre::String >(instanceName);
	RUBYTRY(
		return wrap(_self->createSceneManager(wrap< Ogre::String >(typeName),result));
	)
	return Qnil;
}
/*
*/
VALUE _each_metadata(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<const Ogre::SceneManagerMetaData*>(_self->getSceneManagerMetaDataIterator());
	return self;
}
/*
*/
VALUE _each_sceneManager(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::String,Ogre::SceneManager*>(_self->getSceneManagerIterator());
	return self;
}

}
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
	using namespace RubyOgre::Root;

	rb_define_singleton_method(rb_mOgre,"addResourceLocation",RUBY_METHOD_FUNC(_addResourceLocation),-1);
	
	rb_define_singleton_method(rb_mOgre,"removeResourceLocation",RUBY_METHOD_FUNC(_removeResourceLocation),-1);
	rb_define_singleton_method(rb_mOgre,"hasMovableObjectFactory?",RUBY_METHOD_FUNC(_hasMovableObjectFactory),1);

	rb_define_singleton_method(rb_mOgre,"createFileStream",RUBY_METHOD_FUNC(_createFileStream),-1);
	rb_define_singleton_method(rb_mOgre,"openFileStream",RUBY_METHOD_FUNC(_openFileStream),-1);

	rb_define_singleton_method(rb_mOgre,"createRenderWindow",RUBY_METHOD_FUNC(_createRenderWindow),-1);
	rb_define_singleton_method(rb_mOgre,"getAvailableRenderers",RUBY_METHOD_FUNC(_getAvailableRenderers),0);

	rb_define_singleton_method(rb_mOgre,"showConfigDialog",RUBY_METHOD_FUNC(_showConfigDialog),0);
	rb_define_singleton_method(rb_mOgre,"saveConfig",RUBY_METHOD_FUNC(_saveConfig),0);
	rb_define_singleton_method(rb_mOgre,"loadConfig",RUBY_METHOD_FUNC(_restoreConfig),0);

	rb_define_singleton_method(rb_mOgre,"startRendering",RUBY_METHOD_FUNC(_startRendering),0);

	rb_define_singleton_method(rb_mOgre,"shutdown",RUBY_METHOD_FUNC(_shutdown),0);

	rb_define_singleton_method(rb_mOgre,"addFrameListener",RUBY_METHOD_FUNC(_addFrameListener),1);
	
	rb_define_singleton_method(rb_mOgre,"rendersystem",RUBY_METHOD_FUNC(_getRenderSystem),0);
	rb_define_singleton_method(rb_mOgre,"rendersystem=",RUBY_METHOD_FUNC(_setRenderSystem),1);
	rb_define_singleton_method(rb_mOgre,"initialised?",RUBY_METHOD_FUNC(_isInitialised),0);

	rb_define_singleton_method(rb_mOgre,"loadPlugin",RUBY_METHOD_FUNC(_loadPlugin),1);
	rb_define_singleton_method(rb_mOgre,"unloadPlugin",RUBY_METHOD_FUNC(_unloadPlugin),1);
	
	rb_define_singleton_method(rb_mOgre,"addPluginFolder",RUBY_METHOD_FUNC(_addPluginFolder),1);
	rb_define_singleton_method(rb_mOgre,"pluginfolders",RUBY_METHOD_FUNC(_listPluginFolders),0);
	rb_define_singleton_method(rb_mOgre,"plugins",RUBY_METHOD_FUNC(_listPlugins),0);
	
	rb_define_singleton_method(rb_mOgre,"each_metadata",RUBY_METHOD_FUNC(_each_metadata),0);
	rb_define_singleton_method(rb_mOgre,"each_sceneManager",RUBY_METHOD_FUNC(_each_sceneManager),0);

	rb_define_singleton_method(rb_mOgre,"createSceneManager",RUBY_METHOD_FUNC(_createSceneManager),-1);
	

#ifdef OGRE_PLUGINDIR
	pluginFolder.push_back(OGRE_PLUGINDIR);
#endif
}
