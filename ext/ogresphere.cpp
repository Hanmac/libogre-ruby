#include "ogresphere.hpp"
#include "ogrevector3.hpp"
#define _self wrap<Ogre::Sphere*>(self)
VALUE rb_cOgreSphere;


VALUE OgreSphere_alloc(VALUE self)
{
	return wrap(new Ogre::Sphere);
}
/*:nodoc:
*/
VALUE OgreSphere_set_center(VALUE self,VALUE vec)
{
	_self->setCenter(*wrap<Ogre::Vector3*>(vec));
	return vec;
}
/*:nodoc:
*/
VALUE OgreSphere_set_radius(VALUE self,VALUE radius)
{
	_self->setRadius(NUM2DBL(radius));
	return radius;
}
/*:nodoc:
*/
VALUE OgreSphere_get_center(VALUE self)
{
	return wrap(_self->getCenter());
}
/*:nodoc:
*/
VALUE OgreSphere_get_radius(VALUE self)
{
	return DBL2NUM(_self->getRadius());
}
/*
 * call-seq:
 *   sphere.inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE OgreSphere_inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:%s, %f>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(OgreSphere_get_center(self),rb_intern("inspect"),0);
	array[3]=OgreSphere_get_radius(self);
	return rb_f_sprintf(4,array);
}
/*
*/
VALUE OgreSphere_initialize(VALUE self,VALUE vec,VALUE radius)
{
	OgreSphere_set_center(self,vec);
	OgreSphere_set_radius(self,radius);
	return self;
}
/*
*/
VALUE OgreSphere_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	OgreSphere_set_center(self,OgreSphere_get_center(other));
	OgreSphere_set_radius(self,OgreSphere_get_radius(other));
	return result;
}
/*
*/
VALUE OgreSphere_equal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreSphere)){
		Ogre::Sphere *cother = wrap<Ogre::Sphere*>(other);
		return _self->getCenter() == cother->getCenter() && _self->getRadius() == cother->getRadius() ? Qtrue : Qfalse;
	}else
		return Qfalse;
}
/*
*/
VALUE OgreSphere_swap(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreSphere)){
		Ogre::Sphere *cother = wrap<Ogre::Sphere*>(other);
		Ogre::Real temp_radius = _self->getRadius();
		Ogre::Vector3 temp_vec = _self->getCenter();
		_self->setRadius(cother->getRadius());
		_self->setCenter(cother->getCenter());
		cother->setRadius(temp_radius);
		cother->setCenter(temp_vec);		
		return self;
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreSphere),rb_obj_classname(other));
}
/*
*/
VALUE OgreSphere_intersects(VALUE self,VALUE other)
{
	bool result;
	if(rb_obj_is_kind_of(other,rb_cOgreSphere))
		result = _self->intersects(*wrap<Ogre::Sphere*>(other));
	else if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		result = _self->intersects(*wrap<Ogre::Vector3*>(other));
	else
		rb_raise(rb_eTypeError,"Exepted %s,%s got %s!",
		rb_class2name(rb_cOgreSphere),
		rb_class2name(rb_cOgreVector3),
		rb_obj_classname(other));
	return result ? Qtrue : Qfalse;
}
/*
 * call-seq:
 *   hash -> Integer
 * 
 * hash from the combined Sphere values.
 * ===Return value
 * Integer
*/
VALUE OgreSphere_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreSphere_get_center(self));
	rb_ary_push(result,OgreSphere_get_radius(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Sphere into an string.	
*/
VALUE OgreSphere_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,DBL2NUM(_self->getCenter().x));
	rb_ary_push(result,DBL2NUM(_self->getCenter().y));
	rb_ary_push(result,DBL2NUM(_self->getCenter().z));
	rb_ary_push(result,OgreSphere_get_radius(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Box.
*/
VALUE OgreSphere_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddd"));
	Ogre::Real x = NUM2DBL(rb_ary_pop(result));
	Ogre::Real y = NUM2DBL(rb_ary_pop(result));
	Ogre::Real z = NUM2DBL(rb_ary_pop(result));
	_self->setCenter(Ogre::Vector3(x,y,z));
	OgreSphere_set_radius(self,rb_ary_pop(result));
	return self;
}

/*
 * Document-class: Ogre::Sphere
 * 
 * This class represents an Sphere. 
*/ 

/* Document-attr: center
 * The center Vector3 of the Sphere. */
/* Document-attr: radius
 * The radius of the Sphere. */


void Init_OgreSphere(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	rb_define_attr(rb_cOgreSphere,"center",1,1);
	rb_define_attr(rb_cOgreSphere,"radius",1,1);
#endif
	rb_cOgreSphere = rb_define_class_under(rb_mOgre,"Sphere",rb_cObject);
	rb_define_alloc_func(rb_cOgreSphere,OgreSphere_alloc);
	rb_define_method(rb_cOgreSphere,"initialize",RUBY_METHOD_FUNC(OgreSphere_initialize),2);
	rb_define_private_method(rb_cOgreSphere,"initialize_copy",RUBY_METHOD_FUNC(OgreSphere_initialize_copy),1);

	rb_define_method(rb_cOgreSphere,"center",RUBY_METHOD_FUNC(OgreSphere_get_center),0);
	rb_define_method(rb_cOgreSphere,"radius",RUBY_METHOD_FUNC(OgreSphere_get_radius),0);

	rb_define_method(rb_cOgreSphere,"center=",RUBY_METHOD_FUNC(OgreSphere_set_center),1);
	rb_define_method(rb_cOgreSphere,"radius=",RUBY_METHOD_FUNC(OgreSphere_set_radius),1);

	rb_define_method(rb_cOgreSphere,"inspect",RUBY_METHOD_FUNC(OgreSphere_inspect),0);
	rb_define_method(rb_cOgreSphere,"intersects?",RUBY_METHOD_FUNC(OgreSphere_intersects),1);
	rb_define_method(rb_cOgreSphere,"==",RUBY_METHOD_FUNC(OgreSphere_equal),1);
	rb_define_method(rb_cOgreSphere,"swap",RUBY_METHOD_FUNC(OgreSphere_swap),1);
	
	
	rb_define_method(rb_cOgreSphere,"hash",RUBY_METHOD_FUNC(OgreSphere_hash),0);
	
	rb_define_method(rb_cOgreSphere,"marshal_dump",RUBY_METHOD_FUNC(OgreSphere_marshal_dump),0);
	rb_define_method(rb_cOgreSphere,"marshal_load",RUBY_METHOD_FUNC(OgreSphere_marshal_load),1);
}

