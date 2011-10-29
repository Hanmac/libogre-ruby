#include "ogrematrix4.hpp"
#include "ogrevector3.hpp"
#include "ogreradian.hpp"
#define _self wrap<Ogre::Matrix4*>(self)
VALUE rb_cOgreMatrix4;


macro_attr(Matrix4,Trans,Ogre::Vector3)

VALUE OgreMatrix4_alloc(VALUE self)
{
	return wrap(new Ogre::Matrix4);
}

/*
*/
VALUE OgreMatrix4_initialize(VALUE self,VALUE x,VALUE y,VALUE z)
{
	return self;
}
/*
*/
VALUE OgreMatrix4_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
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
VALUE OgreMatrix4_inspect(VALUE self)
{
	VALUE array[5];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f)>");
	array[1]=rb_class_of(self);
	return rb_f_sprintf(5,array);
}
/*
*/
VALUE OgreMatrix4_swap(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreMatrix4)){
		_self->swap(*wrap<Ogre::Matrix4*>(other));
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreMatrix4),rb_obj_classname(other));
	return self;
}
/*
*/
VALUE OgreMatrix4_plus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreMatrix4))
		return wrap(*_self + *wrap<Ogre::Matrix4*>(other));
	else
		return Qnil;
}
/*
*/
VALUE OgreMatrix4_minus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreMatrix4))
		return wrap(*_self - *wrap<Ogre::Matrix4*>(other));
	else
		return Qnil;
}
/*
*/
VALUE OgreMatrix4_mal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreMatrix4))
		return wrap(*_self * *wrap<Ogre::Matrix4*>(other));
	else
		return Qnil;
}
/*
 * call-seq:
 *   vector.hash -> Integer
 * 
 * hash from the combined vector3 values.
 * ===Return value
 * Integer
*/
VALUE OgreMatrix4_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
	
*/
VALUE OgreMatrix4_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("ddd"));
}
/*

*/
VALUE OgreMatrix4_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("ddd"));
	return self;
}

/*
 * Document-class: Ogre::Matrix4
 * 
 * This class represents an 3dimensional Matrix.
*/
 /* Document-const: Zero
 * a zero Matrix4 */
void Init_OgreMatrix4(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreMatrix4 = rb_define_class_under(rb_mOgre,"Matrix4",rb_cObject);
	rb_define_alloc_func(rb_cOgreMatrix4,OgreMatrix4_alloc);
	rb_define_method(rb_cOgreMatrix4,"initialize",RUBY_METHOD_FUNC(OgreMatrix4_initialize),3);
	rb_define_private_method(rb_cOgreMatrix4,"initialize_copy",RUBY_METHOD_FUNC(OgreMatrix4_initialize_copy),1);
	
	rb_define_method(rb_cOgreMatrix4,"inspect",RUBY_METHOD_FUNC(OgreMatrix4_inspect),0);
	rb_define_alias(rb_cOgreMatrix4,"eql?","==");

	rb_define_method(rb_cOgreMatrix4,"+",RUBY_METHOD_FUNC(OgreMatrix4_plus),1);
	rb_define_method(rb_cOgreMatrix4,"-",RUBY_METHOD_FUNC(OgreMatrix4_minus),1);
	rb_define_method(rb_cOgreMatrix4,"*",RUBY_METHOD_FUNC(OgreMatrix4_mal),1);

	rb_define_method(rb_cOgreMatrix4,"hash",RUBY_METHOD_FUNC(OgreMatrix4_hash),0);
	rb_define_method(rb_cOgreMatrix4,"swap",RUBY_METHOD_FUNC(OgreMatrix4_swap),1);

	rb_define_method(rb_cOgreMatrix4,"marshal_dump",RUBY_METHOD_FUNC(OgreMatrix4_marshal_dump),0);
	rb_define_method(rb_cOgreMatrix4,"marshal_load",RUBY_METHOD_FUNC(OgreMatrix4_marshal_load),1);

	rb_define_const(rb_cOgreMatrix4,"Zero",wrap(Ogre::Matrix4::ZERO));
}
