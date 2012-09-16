#include "ogrenode.hpp"
#include "ogremovableobject.hpp"
#include "ogremovableobjectlistener.hpp"

#include "ogreaxisalignedbox.hpp"
#define _self wrap<Ogre::MovableObject*>(self)

VALUE rb_mOgreMovableObject;

template <>
Ogre::MovableObject* wrap< Ogre::MovableObject* >(const VALUE &val )
{
	if(rb_obj_is_kind_of(val, rb_cOgreParticleSystem))
		return wrap< Ogre::ParticleSystem* >(val);

	return unwrapPtr<Ogre::MovableObject>(val,rb_mOgreMovableObject);
}


namespace RubyOgre
{
namespace MovableObject
{

macro_attr(Visible,bool)
macro_attr(RenderingDistance,double)

macro_attr(RenderQueueGroup,uint)
macro_attr(VisibilityFlags,uint)
macro_attr(QueryFlags,uint)

macro_attr(LightMask,uint)

macro_attr(Listener,Ogre::MovableObject::Listener*)

singlereturn(getName)
singlereturn(getMovableType)
singlereturn(getParentNode)

singlereturn(getBoundingBox)
singlereturn(getBoundingRadius)

singlereturn(isAttached)
singlereturn(isVisible)

/*
*/
VALUE _detach(VALUE self)
{
	_self->detachFromParent();
	return self;
}

/*
*/
VALUE _addQueryFlags(VALUE self,VALUE flags)
{
	_self->addQueryFlags(NUM2ULONG(flags));
	return self;
}
/*
*/
VALUE _removeQueryFlags(VALUE self,VALUE flags)
{
	_self->removeQueryFlags(NUM2ULONG(flags));
	return self;
}
/*
*/
VALUE _addVisibilityFlags(VALUE self,VALUE flags)
{
	_self->addVisibilityFlags(NUM2ULONG(flags));
	return self;
}
/*
*/
VALUE _removeVisibilityFlags(VALUE self,VALUE flags)
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
VALUE _inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	if(_self==NULL)
		array[2]=rb_str_new2("(destroyed)");
	else
		array[2]=_getName(self);
	return rb_f_sprintf(3,array);
}

}
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
	using namespace RubyOgre::MovableObject;
	
	rb_define_method(rb_mOgreMovableObject,"name",RUBY_METHOD_FUNC(_getName),0);
	rb_define_method(rb_mOgreMovableObject,"movable_type",RUBY_METHOD_FUNC(_getMovableType),0);
	rb_define_method(rb_mOgreMovableObject,"parent_node",RUBY_METHOD_FUNC(_getParentNode),0);

	rb_define_method(rb_mOgreMovableObject,"attached?",RUBY_METHOD_FUNC(_isAttached),0);

	rb_define_method(rb_mOgreMovableObject,"detach",RUBY_METHOD_FUNC(_detach),0);
	
	rb_define_method(rb_mOgreMovableObject,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	

	rb_define_method(rb_mOgreMovableObject,"visible?",RUBY_METHOD_FUNC(_isVisible),0);
	
	rb_define_method(rb_mOgreMovableObject,"boundingBox",RUBY_METHOD_FUNC(_getBoundingBox),0);
	rb_define_method(rb_mOgreMovableObject,"boundingRadius",RUBY_METHOD_FUNC(_getBoundingRadius),0);
	
	
	rb_define_method(rb_mOgreMovableObject,"add_query_flags",RUBY_METHOD_FUNC(_addQueryFlags),1);
	rb_define_method(rb_mOgreMovableObject,"add_visibility_flags",RUBY_METHOD_FUNC(_addVisibilityFlags),1);
	rb_define_method(rb_mOgreMovableObject,"remove_query_flags",RUBY_METHOD_FUNC(_removeQueryFlags),1);
	rb_define_method(rb_mOgreMovableObject,"remove_visibility_flags",RUBY_METHOD_FUNC(_removeVisibilityFlags),1);
	
	
	
	rb_define_attr_method(rb_mOgreMovableObject,"rendering_distance",_getRenderingDistance,_setRenderingDistance);
	
	rb_define_attr_method(rb_mOgreMovableObject,"listener",_getListener,_setListener);
	
	rb_define_attr_method(rb_mOgreMovableObject,"visible",_getVisible,_setVisible);
	
	rb_define_attr_method(rb_mOgreMovableObject,"render_queue_group",_getRenderQueueGroup,_setRenderQueueGroup);
	rb_define_attr_method(rb_mOgreMovableObject,"visibility_flags",_getVisibilityFlags,_setVisibilityFlags);
	rb_define_attr_method(rb_mOgreMovableObject,"query_flags",_getQueryFlags,_setQueryFlags);
	
	rb_define_attr_method(rb_mOgreMovableObject,"light_mask",_getLightMask,_setLightMask);
	
	registerklass<Ogre::MovableObject>(rb_mOgreMovableObject);
}
