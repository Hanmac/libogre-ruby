#include "ogreplane.hpp"
#include "ogrevector3.hpp"
#define _self wrap<Ogre::Plane*>(self)
VALUE rb_cOgrePlane;


template <>
VALUE wrap< Ogre::Plane >(Ogre::Plane *plane )
{
	return Data_Wrap_Struct(rb_cOgrePlane, NULL, free, plane);
}

template <>
VALUE wrap< Ogre::Plane::Side >(const Ogre::Plane::Side &side )
{
	ID result;
	switch(side){
	case Ogre::Plane::POSITIVE_SIDE:
		result = rb_intern("positive_side");
		break;
	case Ogre::Plane::NEGATIVE_SIDE:
		result = rb_intern("negative_side");
		break;
	case Ogre::Plane::BOTH_SIDE:
		result = rb_intern("both_side");
		break;
	default:
		result = rb_intern("no_side");
		break;
	}
	return ID2SYM(result);
}



template <>
Ogre::Plane::Side wrap< Ogre::Plane::Side >(const VALUE &arg)
{
	ID id = rb_to_id(arg);
	if(id==rb_intern("no_side"))
		return Ogre::Plane::NO_SIDE;
	else if(id==rb_intern("positive_side"))
		return Ogre::Plane::POSITIVE_SIDE;
	else if(id==rb_intern("negative_side"))
		return Ogre::Plane::NEGATIVE_SIDE;
	else if(id==rb_intern("both_side"))
		return Ogre::Plane::BOTH_SIDE;
	else
		return Ogre::Plane::NO_SIDE;
}


template <>
Ogre::Plane* wrap< Ogre::Plane* >(const VALUE &vplane)
{
	if (rb_obj_is_kind_of(vplane, rb_cOgreMovablePlane) )
		return wrap<Ogre::MovablePlane*>(vplane);
	return unwrapPtr<Ogre::Plane>(vplane, rb_cOgrePlane);
}
template <>
Ogre::Plane wrap< Ogre::Plane >(const VALUE &vplane)
{
	return *wrap<Ogre::Plane*>(vplane);
}

namespace RubyOgre {
namespace Plane {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::Plane);
}

macro_attr_prop(normal,Ogre::Vector3)
macro_attr_prop(d,double)


/*
*/
VALUE _initialize(int argc,VALUE* argv,VALUE self)
{
	VALUE vec,other,vec3;
	rb_scan_args(argc, argv, "21",&vec,&other,&vec3);
	if(!NIL_P(vec3))
		_self->redefine(wrap<Ogre::Vector3>(vec),wrap<Ogre::Vector3>(other),wrap<Ogre::Vector3>(vec3));
	else if(wrapable<Ogre::Vector3>(other)){
		_self->redefine(wrap<Ogre::Vector3>(vec),wrap<Ogre::Vector3>(other));
	}else{
		_set_normal(self,vec);
		_set_d(self,other);
	}
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_normal(self,_get_normal(other));
	_set_d(self,_get_d(other));
	return result;
}
/*
 * call-seq:
 *   vector3.inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:%s, %f>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(_get_normal(self),rb_intern("inspect"),0);
	array[3]=_get_d(self);
	return rb_f_sprintf(4,array);
}
/*
 * call-seq:
 *   vector.hash -> Integer
 * 
 * hash from the combined vector3 values.
 * ===Return value
 * Integer
*/
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_normal(self));
	rb_ary_push(result,_get_d(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
	
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,DBL2NUM(_self->normal.x));
	rb_ary_push(result,DBL2NUM(_self->normal.y));
	rb_ary_push(result,DBL2NUM(_self->normal.z));
	rb_ary_push(result,_get_d(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("d*"));
}
/*

*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("d*"));
	_set_d(self,rb_ary_pop(result));
	_self->normal.z = NUM2DBL(rb_ary_pop(result));
	_self->normal.y = NUM2DBL(rb_ary_pop(result));
	_self->normal.x = NUM2DBL(rb_ary_pop(result));
	return self;
}
/*
*/
VALUE _equal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgrePlane)){
		return wrap(*_self == wrap<Ogre::Plane>(other));
	}else
		return Qfalse;
}
/*
*/
VALUE _getDistance(VALUE self,VALUE vec)
{
	return DBL2NUM(_self->getDistance(wrap<Ogre::Vector3>(vec)));
}
/*
*/
VALUE _projectVector(VALUE self,VALUE vec)
{
	return wrap(_self->projectVector(wrap<Ogre::Vector3>(vec)));
}

}}

void Init_OgrePlane(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_define_attr(rb_cOgrePlane,"normal",1,1);
	rb_define_attr(rb_cOgrePlane,"d",1,1);
#endif
	using namespace RubyOgre::Plane;

	rb_cOgrePlane = rb_define_class_under(rb_mOgre,"Plane",rb_cObject);
	rb_define_alloc_func(rb_cOgrePlane,_alloc);
	rb_define_method(rb_cOgrePlane,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_private_method(rb_cOgrePlane,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);

	rb_define_attr_method(rb_cOgrePlane,"normal",_get_normal,_set_normal);
	rb_define_attr_method(rb_cOgrePlane,"d",_get_d,_set_d);
	
	rb_define_method(rb_cOgrePlane,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	rb_define_method(rb_cOgrePlane,"==",RUBY_METHOD_FUNC(_equal),1);
	rb_define_method(rb_cOgrePlane,"distance",RUBY_METHOD_FUNC(_getDistance),1);
	rb_define_method(rb_cOgrePlane,"projectVector",RUBY_METHOD_FUNC(_projectVector),1);
	
	rb_define_method(rb_cOgrePlane,"hash",RUBY_METHOD_FUNC(_hash),0);
	rb_define_method(rb_cOgrePlane,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cOgrePlane,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);
}
