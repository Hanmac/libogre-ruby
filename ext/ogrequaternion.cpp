#include "ogrequaternion.hpp"
#include "ogrevector3.hpp"
#include "ogreradian.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::Quaternion*>(self)
VALUE rb_cOgreQuaternion;

template <>
VALUE wrap< Ogre::Quaternion >(Ogre::Quaternion *quaternion )
{
	return Data_Wrap_Struct(rb_cOgreQuaternion, NULL, free, quaternion);
}

template <>
Ogre::Quaternion* wrap< Ogre::Quaternion* >(const VALUE &vquaternion)
{
	return unwrapPtr<Ogre::Quaternion>(vquaternion, rb_cOgreQuaternion);
}
template <>
Ogre::Quaternion wrap< Ogre::Quaternion >(const VALUE &vquaternion)
{
	return *wrap< Ogre::Quaternion* >(vquaternion);
}


namespace RubyOgre {
namespace Quaternion {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::Quaternion);
}

macro_attr_prop(x,double)
macro_attr_prop(y,double)
macro_attr_prop(z,double)
macro_attr_prop(w,double)

/*
*/
VALUE _initialize(int argc,VALUE* argv,VALUE self)
{
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_w(self,_get_w(other));
	_set_x(self,_get_x(other));
	_set_y(self,_get_y(other));
	_set_z(self,_get_z(other));
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
	VALUE array[6];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=_get_w(self);
	array[3]=_get_x(self);
	array[4]=_get_y(self);
	array[5]=_get_z(self);
	return rb_f_sprintf(6,array);
}
/*
*/
VALUE _minusself(VALUE self)
{
	return wrap(- *_self);
}
/*
*/
VALUE _xAxis(VALUE self)
{
	return wrap(_self->xAxis());
}
/*
*/
VALUE _yAxis(VALUE self)
{
	return wrap(_self->yAxis());
}
/*
*/
VALUE _zAxis(VALUE self)
{
	return wrap(_self->zAxis());
}
/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	_self->swap(*wrap<Ogre::Quaternion*>(other));
	return self;
}
/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<Ogre::Quaternion>(other));
}
/*
*/
VALUE _minus(VALUE self,VALUE other)
{
	return wrap(*_self - wrap<Ogre::Quaternion>(other));
}
/*
*/
VALUE _mal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreQuaternion))
		return wrap(*_self * wrap<Ogre::Quaternion>(other));
	else if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(*_self * wrap<Ogre::Vector3>(other));
	else
		return wrap(*_self * NUM2DBL(other));
}
/*
 * call-seq:
 *   hash -> Integer
 * 
 * hash from the combined vector3 values.
 * ===Return value
 * Integer
*/
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_w(self));
	rb_ary_push(result,_get_x(self));
	rb_ary_push(result,_get_y(self));
	rb_ary_push(result,_get_z(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Quaternion into an string.
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_w(self));
	rb_ary_push(result,_get_x(self));
	rb_ary_push(result,_get_y(self));
	rb_ary_push(result,_get_z(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("d*"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Quaternion.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("d*"));
	_set_z(self,rb_ary_pop(result));
	_set_y(self,rb_ary_pop(result));
	_set_x(self,rb_ary_pop(result));
	_set_w(self,rb_ary_pop(result));
	return self;
}

}}

/*
 * Document-class: Ogre::Quaternion
 * 
 * This class represents an Quaternion.
*/ 
 /* Document-const: Zero
 * a zero Quaternion */
void Init_OgreQuaternion(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");

	rb_define_attr(rb_cOgreQuaternion,"w",1,1);
	rb_define_attr(rb_cOgreQuaternion,"x",1,1);
	rb_define_attr(rb_cOgreQuaternion,"y",1,1);
	rb_define_attr(rb_cOgreQuaternion,"z",1,1);
#endif
	using namespace RubyOgre::Quaternion;

	rb_cOgreQuaternion = rb_define_class_under(rb_mOgre,"Quaternion",rb_cObject);
	rb_define_alloc_func(rb_cOgreQuaternion,_alloc);
	rb_define_method(rb_cOgreQuaternion,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_private_method(rb_cOgreQuaternion,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);

	rb_define_attr_method(rb_cOgreQuaternion,"w",_get_w,_set_w);
	rb_define_attr_method(rb_cOgreQuaternion,"x",_get_x,_set_x);
	rb_define_attr_method(rb_cOgreQuaternion,"y",_get_y,_set_y);
	rb_define_attr_method(rb_cOgreQuaternion,"z",_get_z,_set_z);

	
	rb_define_method(rb_cOgreQuaternion,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	rb_define_method(rb_cOgreQuaternion,"-@",RUBY_METHOD_FUNC(_minusself),0);
	rb_define_alias(rb_cOgreQuaternion,"eql?","==");

	rb_define_method(rb_cOgreQuaternion,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cOgreQuaternion,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cOgreQuaternion,"*",RUBY_METHOD_FUNC(_mal),1);

	rb_define_method(rb_cOgreQuaternion,"xAxis",RUBY_METHOD_FUNC(_xAxis),0);
	rb_define_method(rb_cOgreQuaternion,"yAxis",RUBY_METHOD_FUNC(_yAxis),0);
	rb_define_method(rb_cOgreQuaternion,"zAxis",RUBY_METHOD_FUNC(_zAxis),0);

	rb_define_method(rb_cOgreQuaternion,"hash",RUBY_METHOD_FUNC(_hash),0);
	rb_define_method(rb_cOgreQuaternion,"swap",RUBY_METHOD_FUNC(_swap),1);

	rb_define_method(rb_cOgreQuaternion,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cOgreQuaternion,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

	rb_define_const(rb_cOgreQuaternion,"Zero",wrap(Ogre::Quaternion::ZERO));
}
