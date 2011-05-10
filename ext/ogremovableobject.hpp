#ifndef __RubyOgreMovableObject_H__
#define __RubyOgreMovableObject_H__

#include "main.hpp"
void Init_OgreMovableObject(VALUE rb_mOgre);
extern VALUE rb_mOgreMovableObject;

#include "ogrelight.hpp"

template <>
inline VALUE wrap< Ogre::MovableObject >(Ogre::MovableObject *obj )
{
	//rb_warn("%s",typeid( *obj ).name());
	rb_warn("%s",obj->getMovableType().c_str());
	Ogre::Light* light = dynamic_cast<Ogre::Light*>(obj);
	if(light != NULL)
		return wrap(light);
	return Qnil;
}

template <>
inline Ogre::MovableObject* wrap< Ogre::MovableObject* >(const VALUE &vmovable)
{
	if ( ! rb_obj_is_kind_of(vmovable, rb_mOgreMovableObject) )
		return NULL;
	Ogre::MovableObject *movable;
  Data_Get_Struct( vmovable, Ogre::MovableObject, movable);
	return movable;
}
#endif /* __RubyOgreMovableObject_H__ */
