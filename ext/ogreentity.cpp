#include "ogreentity.hpp"
#include "ogremesh.hpp"

#include "ogresubentity.hpp"
#include "ogrecolor.hpp"
#include "ogremovableobject.hpp"
#define _self wrap<Ogre::Entity*>(self)
VALUE rb_cOgreEntity;

macro_attr_with_func(Entity,DisplaySkeleton,RBOOL,RTEST)

/*
*/
VALUE OgreEntity_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for (unsigned int i = 0; i < _self->getNumSubEntities(); ++i)
		rb_yield(wrap(_self->getSubEntity(i)));
	return self;
}

/*
*/
VALUE OgreEntity_mesh(VALUE self)
{
	return wrap(_self->getMesh().get());
}
/*
*/
VALUE OgreEntity_each_attached(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::String,Ogre::MovableObject*>(_self->getAttachedObjectIterator());
	return self;
}

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
	rb_define_method(rb_cOgreEntity,"each",RUBY_METHOD_FUNC(OgreEntity_each),0);
	rb_include_module(rb_cOgreEntity,rb_mEnumerable);
	
	rb_define_method(rb_cOgreEntity,"each_attached",RUBY_METHOD_FUNC(OgreEntity_each_attached),0);
}
