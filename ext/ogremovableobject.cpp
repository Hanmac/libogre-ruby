#include "ogrenode.hpp"
#include "ogremovableobject.hpp"
#include "ogremovableobjectlistener.hpp"

#include "ogreaxisalignedbox.hpp"
#define _self wrap<Ogre::MovableObject*>(self)

VALUE rb_mOgreMovableObject;

macro_attr_with_func(MovableObject,Visible,RBOOL,RTEST)
macro_attr_with_func(MovableObject,RenderingDistance,DBL2NUM,NUM2DBL)

macro_attr_with_func(MovableObject,RenderQueueGroup,ULONG2NUM,NUM2ULONG)
macro_attr_with_func(MovableObject,VisibilityFlags,ULONG2NUM,NUM2ULONG)
macro_attr_with_func(MovableObject,QueryFlags,ULONG2NUM,NUM2ULONG)

macro_attr_with_func(MovableObject,LightMask,ULONG2NUM,NUM2ULONG)

macro_attr(MovableObject,Listener,Ogre::MovableObject::Listener*)

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
*/
VALUE OgreMovableObject_getParentNode(VALUE self)
{
	return wrap(_self->getParentNode());
}

/*
*/
VALUE OgreMovableObject_isAttached(VALUE self)
{
	return _self->isAttached() ? Qtrue : Qfalse;
}
/*
*/
VALUE OgreMovableObject_detach(VALUE self)
{
	_self->detachFromParent();
	return self;
}

/*
*/
VALUE OgreMovableObject_isVisible(VALUE self)
{
	return _self->isVisible() ? Qtrue : Qfalse;
}


/*
*/
VALUE OgreMovableObject_getBoundingBox(VALUE self)
{
	return wrap(_self->getBoundingBox());
}
/*
*/
VALUE OgreMovableObject_getBoundingRadius(VALUE self)
{
	return DBL2NUM(_self->getBoundingRadius());
}

/*
*/
VALUE OgreMovableObject_addQueryFlags(VALUE self,VALUE flags)
{
	_self->addQueryFlags(NUM2ULONG(flags));
	return self;
}
/*
*/
VALUE OgreMovableObject_removeQueryFlags(VALUE self,VALUE flags)
{
	_self->removeQueryFlags(NUM2ULONG(flags));
	return self;
}
/*
*/
VALUE OgreMovableObject_addVisibilityFlags(VALUE self,VALUE flags)
{
	_self->addVisibilityFlags(NUM2ULONG(flags));
	return self;
}
/*
*/
VALUE OgreMovableObject_removeVisibilityFlags(VALUE self,VALUE flags)
{
	_self->removeVisibilityFlags(NUM2ULONG(flags));
	return self;
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
 * Document-module: Ogre::MovableObject
 * 
 * This module represents an Movable Object.
*/
void Init_OgreMovableObject(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_define_attr(rb_mOgreMovableObject,"listener",1,1);
	rb_define_attr(rb_mOgreMovableObject,"visible",1,1);
	rb_define_attr(rb_mOgreMovableObject,"renderingDistance",1,1);
	
	
	rb_define_attr(rb_mOgreMovableObject,"renderQueueGroup",1,1);
	rb_define_attr(rb_mOgreMovableObject,"visibilityFlags",1,1);
	rb_define_attr(rb_mOgreMovableObject,"queryFlags",1,1);

	rb_define_attr(rb_mOgreMovableObject,"lightMask",1,1);


#endif
	rb_mOgreMovableObject = rb_define_module_under(rb_mOgre,"MovableObject");

	
	rb_define_method(rb_mOgreMovableObject,"name",RUBY_METHOD_FUNC(OgreMovableObject_getName),0);
	rb_define_method(rb_mOgreMovableObject,"movableType",RUBY_METHOD_FUNC(OgreMovableObject_getMovableType),0);
	rb_define_method(rb_mOgreMovableObject,"parentNode",RUBY_METHOD_FUNC(OgreMovableObject_getParentNode),0);

	rb_define_method(rb_mOgreMovableObject,"attached?",RUBY_METHOD_FUNC(OgreMovableObject_isAttached),0);

	rb_define_method(rb_mOgreMovableObject,"detach",RUBY_METHOD_FUNC(OgreMovableObject_detach),0);
	
	rb_define_method(rb_mOgreMovableObject,"inspect",RUBY_METHOD_FUNC(OgreMovableObject_inspect),0);
	
	rb_define_attr_method(rb_mOgreMovableObject,"visible",OgreMovableObject_getVisible,OgreMovableObject_setVisible);
	rb_define_method(rb_mOgreMovableObject,"visible?",RUBY_METHOD_FUNC(OgreMovableObject_isVisible),0);
	
	rb_define_method(rb_mOgreMovableObject,"boundingBox",RUBY_METHOD_FUNC(OgreMovableObject_getBoundingBox),0);
	rb_define_method(rb_mOgreMovableObject,"boundingRadius",RUBY_METHOD_FUNC(OgreMovableObject_getBoundingRadius),0);
	
	
	rb_define_method(rb_mOgreMovableObject,"addQueryFlags",RUBY_METHOD_FUNC(OgreMovableObject_addQueryFlags),1);
	rb_define_method(rb_mOgreMovableObject,"addVisibilityFlags",RUBY_METHOD_FUNC(OgreMovableObject_addVisibilityFlags),1);
	rb_define_method(rb_mOgreMovableObject,"removeQueryFlags",RUBY_METHOD_FUNC(OgreMovableObject_removeQueryFlags),1);
	rb_define_method(rb_mOgreMovableObject,"removeVisibilityFlags",RUBY_METHOD_FUNC(OgreMovableObject_removeVisibilityFlags),1);
	
	
	
	rb_define_attr_method(rb_mOgreMovableObject,"renderingDistance",OgreMovableObject_getRenderingDistance,OgreMovableObject_setRenderingDistance);
	
	rb_define_attr_method(rb_mOgreMovableObject,"listener",OgreMovableObject_getListener,OgreMovableObject_setListener);
	
	
	rb_define_attr_method(rb_mOgreMovableObject,"renderQueueGroup",OgreMovableObject_getRenderQueueGroup,OgreMovableObject_setRenderQueueGroup);
	rb_define_attr_method(rb_mOgreMovableObject,"visibilityFlags",OgreMovableObject_getVisibilityFlags,OgreMovableObject_setVisibilityFlags);
	rb_define_attr_method(rb_mOgreMovableObject,"queryFlags",OgreMovableObject_getQueryFlags,OgreMovableObject_setQueryFlags);
	
	rb_define_attr_method(rb_mOgreMovableObject,"lightMask",OgreMovableObject_getLightMask,OgreMovableObject_setLightMask);
	
}
