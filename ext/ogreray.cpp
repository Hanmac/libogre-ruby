#include "ogreray.hpp"
#include "ogrevector3.hpp"
#define _self wrap<Ogre::Ray*>(self)
VALUE rb_cOgreRay;


VALUE OgreRay_alloc(VALUE self)
{
	return wrap(new Ogre::Ray);
}
/*:nodoc:
*/
VALUE OgreRay_set_origin(VALUE self,VALUE vec)
{
	_self->setOrigin(*wrap<Ogre::Vector3*>(vec));
	return vec;
}
/*:nodoc:
*/
VALUE OgreRay_set_direction(VALUE self,VALUE vec)
{
	_self->setDirection(*wrap<Ogre::Vector3*>(vec));
	return vec;
}
/*:nodoc:
*/
VALUE OgreRay_get_origin(VALUE self)
{
	return wrap(_self->getOrigin());
}
/*:nodoc:
*/
VALUE OgreRay_get_direction(VALUE self)
{
	return wrap(_self->getDirection());
}
/*
 * call-seq:
 *   sphere.inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE OgreRay_inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:%s, %s>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(OgreRay_get_origin(self),rb_intern("inspect"),0);
	array[3]=rb_funcall(OgreRay_get_direction(self),rb_intern("inspect"),0);
	return rb_f_sprintf(4,array);
}
/*
*/
VALUE OgreRay_initialize(VALUE self,VALUE vec,VALUE direction)
{
	OgreRay_set_origin(self,vec);
	OgreRay_set_direction(self,direction);
	return self;
}
/*
*/
VALUE OgreRay_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	OgreRay_set_origin(self,OgreRay_get_origin(other));
	OgreRay_set_direction(self,OgreRay_get_direction(other));
	return result;
}
/*
*/
VALUE OgreRay_equal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreRay)){
		Ogre::Ray *cother = wrap<Ogre::Ray*>(other);
		return _self->getOrigin() == cother->getOrigin() && _self->getDirection() == cother->getDirection() ? Qtrue : Qfalse;
	}else
		return Qfalse;
}
/*
*/
VALUE OgreRay_swap(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreRay)){
		Ogre::Ray *cother = wrap<Ogre::Ray*>(other);
		Ogre::Vector3 temp_direction = _self->getDirection();
		Ogre::Vector3 temp_origin = _self->getOrigin();
		_self->setDirection(cother->getDirection());
		_self->setOrigin(cother->getOrigin());
		cother->setDirection(temp_direction);
		cother->setOrigin(temp_origin);		
		return self;
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreRay),rb_obj_classname(other));
}
/*
*/
VALUE OgreRay_intersects(VALUE self,VALUE other)
{
	bool result=true;
	return result ? Qtrue : Qfalse;
}
/*
 * call-seq:
 *   rect.hash -> Integer
 * 
 * hash from the combined rect values.
 * ===Return value
 * Integer
*/
VALUE OgreRay_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreRay_get_origin(self));
	rb_ary_push(result,OgreRay_get_direction(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
	
*/
VALUE OgreRay_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,DBL2NUM(_self->getOrigin().x));
	rb_ary_push(result,DBL2NUM(_self->getOrigin().y));
	rb_ary_push(result,DBL2NUM(_self->getOrigin().z));
	rb_ary_push(result,DBL2NUM(_self->getDirection().x));
	rb_ary_push(result,DBL2NUM(_self->getDirection().y));
	rb_ary_push(result,DBL2NUM(_self->getDirection().z));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddddd"));
}
/*

*/
VALUE OgreRay_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddddd"));
	Ogre::Real x = NUM2DBL(rb_ary_pop(result));
	Ogre::Real y = NUM2DBL(rb_ary_pop(result));
	Ogre::Real z = NUM2DBL(rb_ary_pop(result));
	_self->setOrigin(Ogre::Vector3(x,y,z));
	x = NUM2DBL(rb_ary_pop(result));
	y = NUM2DBL(rb_ary_pop(result));
	z = NUM2DBL(rb_ary_pop(result));
	_self->setDirection(Ogre::Vector3(x,y,z));
	return self;
}

/*
 * Document-class: Ogre::Ray
 * 
 * This class represents an Ray.
*/ 

/* Document-attr: origin
 * The origin Vector3 of the Ray. */
/* Document-attr: direction
 * The direction of the Ray. */


void Init_OgreRay(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	rb_define_attr(rb_cOgreRay,"origin",1,1);
	rb_define_attr(rb_cOgreRay,"direction",1,1);
#endif
	rb_cOgreRay = rb_define_class_under(rb_mOgre,"Ray",rb_cObject);
	rb_define_alloc_func(rb_cOgreRay,OgreRay_alloc);
	rb_define_method(rb_cOgreRay,"initialize",RUBY_METHOD_FUNC(OgreRay_initialize),2);
	rb_define_private_method(rb_cOgreRay,"initialize_copy",RUBY_METHOD_FUNC(OgreRay_initialize_copy),1);

	rb_define_method(rb_cOgreRay,"origin",RUBY_METHOD_FUNC(OgreRay_get_origin),0);
	rb_define_method(rb_cOgreRay,"direction",RUBY_METHOD_FUNC(OgreRay_get_direction),0);

	rb_define_method(rb_cOgreRay,"origin=",RUBY_METHOD_FUNC(OgreRay_set_origin),1);
	rb_define_method(rb_cOgreRay,"direction=",RUBY_METHOD_FUNC(OgreRay_set_direction),1);

	rb_define_method(rb_cOgreRay,"inspect",RUBY_METHOD_FUNC(OgreRay_inspect),0);
//	rb_define_method(rb_cOgreRay,"intersects?",RUBY_METHOD_FUNC(OgreRay_intersects),1);
	rb_define_method(rb_cOgreRay,"==",RUBY_METHOD_FUNC(OgreRay_equal),1);
	rb_define_method(rb_cOgreRay,"swap",RUBY_METHOD_FUNC(OgreRay_swap),1);
	
	
	rb_define_method(rb_cOgreRay,"hash",RUBY_METHOD_FUNC(OgreRay_hash),0);
	
	rb_define_method(rb_cOgreRay,"marshal_dump",RUBY_METHOD_FUNC(OgreRay_marshal_dump),0);
	rb_define_method(rb_cOgreRay,"marshal_load",RUBY_METHOD_FUNC(OgreRay_marshal_load),1);
}

