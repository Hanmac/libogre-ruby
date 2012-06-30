#ifndef __RubyOgreSceneManager_H__
#define __RubyOgreSceneManager_H__

#include "main.hpp"
void Init_OgreSceneManager(VALUE rb_mOgre);
extern VALUE rb_cOgreSceneManager,rb_cOgreSceneManagerMetaData;

#include "ogreexception.hpp"

template <>
VALUE wrap< Ogre::SceneManagerMetaData >(Ogre::SceneManagerMetaData *manager );

template <>
VALUE wrap<const Ogre::SceneManagerMetaData >(const Ogre::SceneManagerMetaData *manager );


template <>
Ogre::SceneManagerMetaData* wrap< Ogre::SceneManagerMetaData* >(const VALUE &vmanager);

#endif /* __RubyOgreSceneManager_H__ */
