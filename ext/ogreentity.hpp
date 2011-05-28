#ifndef __RubyOgreEntity_H__
#define __RubyOgreEntity_H__

#include "main.hpp"
void Init_OgreEntity(VALUE rb_mOgre);
extern VALUE rb_cOgreEntity;
#include "ogreexception.hpp"
#include "ogremovableobject_impl.hpp"
template <>
inline VALUE wrap< Ogre::Entity >(Ogre::Entity *entity )
{
	RubyMovableObject *temp = new RubyMovableObject;
	temp->man = entity->_getManager()->getName();
	temp->type = entity->getMovableType();
	temp->name = entity->getName();
	return Data_Wrap_Struct(rb_cOgreEntity, NULL, free, temp);
}

template <>
inline Ogre::Entity* wrap< Ogre::Entity* >(const VALUE &ventity)
{
	if ( ! rb_obj_is_kind_of(ventity, rb_cOgreEntity) )
		return NULL;
	RubyMovableObject *entity;
  Data_Get_Struct( ventity, RubyMovableObject, entity);
  try{
    return Ogre::Root::getSingletonPtr()->getSceneManager(entity->man)->getEntity(entity->name);
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
		return NULL;
	}
}
#endif /* __RubyOgreEntity_H__ */
