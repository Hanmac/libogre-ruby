#ifndef __RubyOgreMovableObject_H__
#define __RubyOgreMovableObject_H__

#include "main.hpp"
void Init_OgreMovableObject(VALUE rb_mOgre);
extern VALUE rb_mOgreMovableObject;

#include "ogrelight.hpp"
#include "ogreentity.hpp"

template <>
inline VALUE wrap< Ogre::MovableObject >(Ogre::MovableObject *obj )
{
	if(typeid( *obj ) == typeid(Ogre::MovableObject))
		return rb_str_new2(obj->getName().c_str());
	Ogre::Light* light = dynamic_cast<Ogre::Light*>(obj);
	if(light != NULL)
		return wrap(light);
	Ogre::Entity* entity = dynamic_cast<Ogre::Entity*>(obj);
	if(entity != NULL)
		return wrap(entity);
	return Qnil;
}

template <>
inline Ogre::MovableObject* wrap< Ogre::MovableObject* >(const VALUE &vmovable)
{
	if ( ! rb_obj_is_kind_of(vmovable, rb_mOgreMovableObject) )
		return NULL;
	RubyMovableObject *movable;
  Data_Get_Struct( vmovable, RubyMovableObject, movable);
  try{
	  Ogre::SceneManager *man = Ogre::Root::getSingletonPtr()->getSceneManager(movable->man);
		return man->getMovableObject(movable->name,movable->type);
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
		return NULL;
	}
}
#endif /* __RubyOgreMovableObject_H__ */
