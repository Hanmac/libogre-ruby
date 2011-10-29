#include "ogrequaternion.hpp"
#include "ogrevector3.hpp"
#include "ogreradian.hpp"
#define _self wrap<Ogre::Quaternion*>(self)
VALUE rb_cOgreQuaternion;

VALUE OgreQuaternion_alloc(VALUE self)
{
	return wrap(new Ogre::Quaternion);
}


macro_attr_prop_with_func(Quaternion,x,DBL2NUM,NUM2DBL)
macro_attr_prop_with_func(Quaternion,y,DBL2NUM,NUM2DBL)
macro_attr_prop_with_func(Quaternion,z,DBL2NUM,NUM2DBL)
macro_attr_prop_with_func(Quaternion,w,DBL2NUM,NUM2DBL)

/*
*/
VALUE OgreQuaternion_initialize(int argc,VALUE* argv,VALUE self)
{
	return self;
}
/*
*/
VALUE OgreQuaternion_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	OgreQuaternion_set_w(self,OgreQuaternion_get_w(other));
	OgreQuaternion_set_x(self,OgreQuaternion_get_x(other));
	OgreQuaternion_set_y(self,OgreQuaternion_get_y(other));
	OgreQuaternion_set_z(self,OgreQuaternion_get_z(other));
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
VALUE OgreQuaternion_inspect(VALUE self)
{
	VALUE array[6];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=OgreQuaternion_get_w(self);
	array[3]=OgreQuaternion_get_x(self);
	array[4]=OgreQuaternion_get_y(self);
	array[5]=OgreQuaternion_get_z(self);
	return rb_f_sprintf(6,array);
}
/*
*/
VALUE OgreQuaternion_minusself(VALUE self)
{
	return wrap(- *_self);
}
/*
*/
VALUE OgreQuaternion_xAxis(VALUE self)
{
	return wrap(_self->xAxis());
}
/*
*/
VALUE OgreQuaternion_yAxis(VALUE self)
{
	return wrap(_self->yAxis());
}
/*
*/
VALUE OgreQuaternion_zAxis(VALUE self)
{
	return wrap(_self->zAxis());
}
/*
*/
VALUE OgreQuaternion_swap(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreQuaternion)){
		_self->swap(*wrap<Ogre::Quaternion*>(other));
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreQuaternion),rb_obj_classname(other));
	return self;
}
/*
*/
VALUE OgreQuaternion_plus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreQuaternion))
		return wrap(*_self + *wrap<Ogre::Quaternion*>(other));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreQuaternion),rb_obj_classname(other));
}
/*
*/
VALUE OgreQuaternion_minus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreQuaternion))
		return wrap(*_self - *wrap<Ogre::Quaternion*>(other));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreQuaternion),rb_obj_classname(other));
}
/*
*/
VALUE OgreQuaternion_mal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreQuaternion))
		return wrap(*_self * *wrap<Ogre::Quaternion*>(other));
	else if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(*_self * *wrap<Ogre::Vector3*>(other));
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
VALUE OgreQuaternion_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreQuaternion_get_w(self));
	rb_ary_push(result,OgreQuaternion_get_x(self));
	rb_ary_push(result,OgreQuaternion_get_y(self));
	rb_ary_push(result,OgreQuaternion_get_z(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Quaternion into an string.
*/
VALUE OgreQuaternion_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreQuaternion_get_w(self));
	rb_ary_push(result,OgreQuaternion_get_x(self));
	rb_ary_push(result,OgreQuaternion_get_y(self));
	rb_ary_push(result,OgreQuaternion_get_z(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Quaternion.
*/
VALUE OgreQuaternion_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddd"));
	OgreQuaternion_set_z(self,rb_ary_pop(result));
	OgreQuaternion_set_y(self,rb_ary_pop(result));
	OgreQuaternion_set_x(self,rb_ary_pop(result));
	OgreQuaternion_set_w(self,rb_ary_pop(result));
	return self;
}

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
	rb_cOgreQuaternion = rb_define_class_under(rb_mOgre,"Quaternion",rb_cObject);
	rb_define_alloc_func(rb_cOgreQuaternion,OgreQuaternion_alloc);
	rb_define_method(rb_cOgreQuaternion,"initialize",RUBY_METHOD_FUNC(OgreQuaternion_initialize),-1);
	rb_define_private_method(rb_cOgreQuaternion,"initialize_copy",RUBY_METHOD_FUNC(OgreQuaternion_initialize_copy),1);

	rb_define_attr_method(rb_cOgreQuaternion,"w",OgreQuaternion_get_w,OgreQuaternion_set_w);
	rb_define_attr_method(rb_cOgreQuaternion,"x",OgreQuaternion_get_x,OgreQuaternion_set_x);
	rb_define_attr_method(rb_cOgreQuaternion,"y",OgreQuaternion_get_y,OgreQuaternion_set_y);
	rb_define_attr_method(rb_cOgreQuaternion,"z",OgreQuaternion_get_z,OgreQuaternion_set_z);

	
	rb_define_method(rb_cOgreQuaternion,"inspect",RUBY_METHOD_FUNC(OgreQuaternion_inspect),0);
	rb_define_method(rb_cOgreQuaternion,"-@",RUBY_METHOD_FUNC(OgreQuaternion_minusself),0);
	rb_define_alias(rb_cOgreQuaternion,"eql?","==");

	rb_define_method(rb_cOgreQuaternion,"+",RUBY_METHOD_FUNC(OgreQuaternion_plus),1);
	rb_define_method(rb_cOgreQuaternion,"-",RUBY_METHOD_FUNC(OgreQuaternion_minus),1);
	rb_define_method(rb_cOgreQuaternion,"*",RUBY_METHOD_FUNC(OgreQuaternion_mal),1);

	rb_define_method(rb_cOgreQuaternion,"xAxis",RUBY_METHOD_FUNC(OgreQuaternion_xAxis),0);
	rb_define_method(rb_cOgreQuaternion,"yAxis",RUBY_METHOD_FUNC(OgreQuaternion_yAxis),0);
	rb_define_method(rb_cOgreQuaternion,"zAxis",RUBY_METHOD_FUNC(OgreQuaternion_zAxis),0);

	rb_define_method(rb_cOgreQuaternion,"hash",RUBY_METHOD_FUNC(OgreQuaternion_hash),0);
	rb_define_method(rb_cOgreQuaternion,"swap",RUBY_METHOD_FUNC(OgreQuaternion_swap),1);

	rb_define_method(rb_cOgreQuaternion,"marshal_dump",RUBY_METHOD_FUNC(OgreQuaternion_marshal_dump),0);
	rb_define_method(rb_cOgreQuaternion,"marshal_load",RUBY_METHOD_FUNC(OgreQuaternion_marshal_load),1);

	rb_define_const(rb_cOgreQuaternion,"Zero",wrap(Ogre::Quaternion::ZERO));
}
