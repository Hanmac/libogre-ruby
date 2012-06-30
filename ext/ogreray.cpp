#include "ogreray.hpp"
#include "ogrevector3.hpp"
#include "ogreexception.hpp"

#define _self wrap<Ogre::Ray*>(self)
VALUE rb_cOgreRay;

template <>
VALUE wrap< Ogre::Ray >(Ogre::Ray *ray )
{
	return Data_Wrap_Struct(rb_cOgreRay, NULL, free, ray);
}


namespace RubyOgre {
namespace Ray {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::Ray);
}
macro_attr(Origin,Ogre::Vector3)
macro_attr(Direction,Ogre::Vector3)
/*
 * call-seq:
 *   sphere.inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:%s, %s>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(_getOrigin(self),rb_intern("inspect"),0);
	array[3]=rb_funcall(_getDirection(self),rb_intern("inspect"),0);
	return rb_f_sprintf(4,array);
}
/*
*/
VALUE _initialize(VALUE self,VALUE vec,VALUE direction)
{
	_setOrigin(self,vec);
	_setDirection(self,direction);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_setOrigin(self,_getOrigin(other));
	_setDirection(self,_getDirection(other));
	return result;
}
/*
*/
VALUE _equal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreRay)){
		Ogre::Ray *cother = wrap<Ogre::Ray*>(other);
		return _self->getOrigin() == cother->getOrigin() && _self->getDirection() == cother->getDirection() ? Qtrue : Qfalse;
	}else
		return Qfalse;
}
/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	Ogre::Ray *cother = wrap<Ogre::Ray*>(other);
	Ogre::Vector3 temp_direction = _self->getDirection();
	Ogre::Vector3 temp_origin = _self->getOrigin();
	_self->setDirection(cother->getDirection());
	_self->setOrigin(cother->getOrigin());
	cother->setDirection(temp_direction);
	cother->setOrigin(temp_origin);
	return self;
}
/*
*/
VALUE _intersects(VALUE self,VALUE other)
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
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_getOrigin(self));
	rb_ary_push(result,_getDirection(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
	
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,DBL2NUM(_self->getOrigin().x));
	rb_ary_push(result,DBL2NUM(_self->getOrigin().y));
	rb_ary_push(result,DBL2NUM(_self->getOrigin().z));
	rb_ary_push(result,DBL2NUM(_self->getDirection().x));
	rb_ary_push(result,DBL2NUM(_self->getDirection().y));
	rb_ary_push(result,DBL2NUM(_self->getDirection().z));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("d*"));
}
/*

*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("d*"));
	Ogre::Real x = NUM2DBL(rb_ary_pop(result));
	Ogre::Real y = NUM2DBL(rb_ary_pop(result));
	Ogre::Real z = NUM2DBL(rb_ary_pop(result));
	_self->setDirection(Ogre::Vector3(x,y,z));
	x = NUM2DBL(rb_ary_pop(result));
	y = NUM2DBL(rb_ary_pop(result));
	z = NUM2DBL(rb_ary_pop(result));
	_self->setOrigin(Ogre::Vector3(x,y,z));
	return self;
}

}}

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
	using namespace RubyOgre::Ray;

	rb_cOgreRay = rb_define_class_under(rb_mOgre,"Ray",rb_cObject);
	rb_define_alloc_func(rb_cOgreRay,_alloc);
	rb_define_method(rb_cOgreRay,"initialize",RUBY_METHOD_FUNC(_initialize),2);
	rb_define_private_method(rb_cOgreRay,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);

	rb_define_attr_method(rb_cOgreRay,"origin",_getOrigin,_setOrigin);
	
	rb_define_attr_method(rb_cOgreRay,"direction",_getDirection,_setDirection);

	rb_define_method(rb_cOgreRay,"inspect",RUBY_METHOD_FUNC(_inspect),0);
//	rb_define_method(rb_cOgreRay,"intersects?",RUBY_METHOD_FUNC(_intersects),1);
	rb_define_method(rb_cOgreRay,"==",RUBY_METHOD_FUNC(_equal),1);
	rb_define_method(rb_cOgreRay,"swap",RUBY_METHOD_FUNC(_swap),1);
	
	
	rb_define_method(rb_cOgreRay,"hash",RUBY_METHOD_FUNC(_hash),0);
	
	rb_define_method(rb_cOgreRay,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cOgreRay,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

	registerklass<Ogre::Ray>(rb_cOgreRay);
}

