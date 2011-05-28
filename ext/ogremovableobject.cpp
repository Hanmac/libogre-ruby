#include "ogremovableobject.hpp"
#include "ogremovableobjectlistener.hpp"
#define _self wrap<Ogre::MovableObject*>(self)

VALUE rb_mOgreMovableObject;

/*
*/
VALUE OgreMovableObject_getName(VALUE self)
{
	return wrap(_self->getName());
}

/*
*/
VALUE OgreMovableObject_getMovableType(VALUE self)
{
	return wrap(_self->getMovableType());
}

/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE OgreMovableObject_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	if(_self==NULL)
		array[2]=rb_str_new2("(destroyed)");
	else
		array[2]=OgreMovableObject_getName(self);
	return rb_f_sprintf(3,array);
}

/*
 * call-seq:
 *   listener -> MovableObject::Listener
 * 
 * returns the listener.
*/
VALUE OgreMovableObject_getListener(VALUE self)
{
	Ogre::MovableObject::Listener *temp = _self->getListener();
	return temp ? wrap(temp) : Qnil;
}
/*
 * call-seq:
 *   listener = MovableObject::Listener
 * 
 * sets the listener.
*/
VALUE OgreMovableObject_setListener(VALUE self,VALUE val)
{
	_self->setListener(wrap<Ogre::MovableObject::Listener*>(val));
	return val;
}

/*
 * Document-module: Ogre::MovableObject
 * 
 * This module represents an Movable Object.
*/ 

void Init_OgreMovableObject(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_mOgreMovableObject = rb_define_module_under(rb_mOgre,"MovableObject");

	
	rb_define_method(rb_mOgreMovableObject,"name",RUBY_METHOD_FUNC(OgreMovableObject_getName),0);
	rb_define_method(rb_mOgreMovableObject,"movableType",RUBY_METHOD_FUNC(OgreMovableObject_getMovableType),0);
	
	rb_define_method(rb_mOgreMovableObject,"inspect",RUBY_METHOD_FUNC(OgreMovableObject_inspect),0);
	
	rb_define_method(rb_mOgreMovableObject,"listener",RUBY_METHOD_FUNC(OgreMovableObject_getListener),0);
	rb_define_method(rb_mOgreMovableObject,"listener=",RUBY_METHOD_FUNC(OgreMovableObject_setListener),1);
}
