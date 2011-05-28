#include "ogreentity.hpp"
#include "ogrecolor.hpp"
#include "ogremovableobject.hpp"
#define _self wrap<Ogre::Entity*>(self)
VALUE rb_cOgreEntity;

/*
 * Document-class: Ogre::Entity
 * 
 * This class represents an Entity. 
*/ 

void Init_OgreEntity(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_mOgreMovableObject = rb_define_module_under(rb_mOgre,"MovableObject");
#endif
	rb_cOgreEntity = rb_define_class_under(rb_mOgre,"Entity",rb_cObject);
	rb_undef_alloc_func(rb_cOgreEntity);
	rb_include_module(rb_cOgreEntity,rb_mOgreMovableObject);
}
