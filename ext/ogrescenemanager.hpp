#ifndef __RubyOgreSceneManager_H__
#define __RubyOgreSceneManager_H__

#include "main.hpp"
void Init_OgreSceneManager(VALUE rb_mOgre);
extern VALUE rb_cOgreSceneManager,rb_cOgreSceneManagerMetaData;

#include "ogreexception.hpp"
struct RubyOgreSceneManager{
	Ogre::String name;
};

template <>
inline VALUE wrap< Ogre::SceneManager >(Ogre::SceneManager *manager )
{
	RubyOgreSceneManager *temp = new RubyOgreSceneManager;
	temp->name = manager->getName();
	return Data_Wrap_Struct(rb_cOgreSceneManager, NULL, free, temp);
}

template <>
inline Ogre::SceneManager* wrap< Ogre::SceneManager* >(const VALUE &vmanager)
{
	if ( ! rb_obj_is_kind_of(vmanager, rb_cOgreSceneManager) )
		return NULL;
	RubyOgreSceneManager *manager;
  Data_Get_Struct( vmanager, RubyOgreSceneManager, manager);
  try{
		return Ogre::Root::getSingletonPtr()->getSceneManager(manager->name);
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
		return NULL;
	}
}

template <>
inline VALUE wrap< Ogre::SceneManagerMetaData >(Ogre::SceneManagerMetaData *manager )
{
	return Data_Wrap_Struct(rb_cOgreSceneManagerMetaData, NULL, free, manager);
}

template <>
inline VALUE wrap<const Ogre::SceneManagerMetaData >(const Ogre::SceneManagerMetaData *manager )
{
	return Data_Wrap_Struct(rb_cOgreSceneManagerMetaData, NULL, NULL, const_cast<Ogre::SceneManagerMetaData*>(manager));
}


template <>
inline Ogre::SceneManagerMetaData* wrap< Ogre::SceneManagerMetaData* >(const VALUE &vmanager)
{
	if ( ! rb_obj_is_kind_of(vmanager, rb_cOgreSceneManagerMetaData) )
		return NULL;
	Ogre::SceneManagerMetaData *manager;
  Data_Get_Struct( vmanager, Ogre::SceneManagerMetaData, manager);
	return manager;
}
#endif /* __RubyOgreSceneManager_H__ */
