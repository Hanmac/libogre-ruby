#ifndef __RubyOgreResourceGroupManager_H__
#define __RubyOgreResourceGroupManager_H__

#include "main.hpp"
void Init_OgreResourceGroupManager(VALUE rb_mOgre);
extern VALUE rb_cOgreResourceGroupManager;


template <>
inline VALUE wrap< Ogre::ResourceGroupManager >(Ogre::ResourceGroupManager *manager )
{
	return Data_Wrap_Struct(rb_cOgreResourceGroupManager, NULL, NULL, manager);
}

template <>
inline Ogre::ResourceGroupManager* wrap< Ogre::ResourceGroupManager* >(const VALUE &vmanager)
{
	if ( ! rb_obj_is_kind_of(vmanager, rb_cOgreResourceGroupManager) )
		return NULL;
	Ogre::ResourceGroupManager *manager;
  Data_Get_Struct( vmanager, Ogre::ResourceGroupManager, manager);
	return manager;
}
#endif /* __RubyOgreResourceGroupManager_H__ */
