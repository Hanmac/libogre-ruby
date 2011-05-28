#include "ogrematrix3.hpp"
#include "ogrevector3.hpp"
#include "ogreradian.hpp"
#define _self wrap<Ogre::Matrix3*>(self)
VALUE rb_cOgreMatrix3;

VALUE OgreMatrix3_alloc(VALUE self)
{
	return wrap(new Ogre::Matrix3);
}/*
*/
VALUE OgreMatrix3_initialize(VALUE self,VALUE x,VALUE y,VALUE z)
{
	return self;
}
/*
*/
VALUE OgreMatrix3_initialize_copy(VALUE self, VALUE other)
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
VALUE OgreMatrix3_inspect(VALUE self)
{
	VALUE array[5];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f)>");
	array[1]=rb_class_of(self);
	return rb_f_sprintf(5,array);
}
/*
*/
VALUE OgreMatrix3_minusself(VALUE self)
{
	return wrap(- *_self);
}
/*
*/
VALUE OgreMatrix3_swap(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreMatrix3)){
		_self->swap(*wrap<Ogre::Matrix3*>(other));
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreMatrix3),rb_obj_classname(other));
	return self;
}
/*
*/
VALUE OgreMatrix3_plus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreMatrix3))
		return wrap(*_self + *wrap<Ogre::Matrix3*>(other));
	else
		return Qnil;
}
/*
*/
VALUE OgreMatrix3_minus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreMatrix3))
		return wrap(*_self - *wrap<Ogre::Matrix3*>(other));
	else
		return Qnil;
}
/*
*/
VALUE OgreMatrix3_mal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreMatrix3))
		return wrap(*_self * *wrap<Ogre::Matrix3*>(other));
	else
		return wrap(*_self * NUM2DBL(other));
}
/*
 * call-seq:
 *   vector.hash -> Integer
 * 
 * hash from the combined vector3 values.
 * ===Return value
 * Integer
*/
VALUE OgreMatrix3_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
	
*/
VALUE OgreMatrix3_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("ddd"));
}
/*

*/
VALUE OgreMatrix3_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("ddd"));
	return self;
}

/*
 * Document-class: Ogre::Matrix3
 * 
 * This class represents an 3dimensional Matrix.
*/
 /* Document-const: Zero
 * a zero Matrix3 */
void Init_OgreMatrix3(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreMatrix3 = rb_define_class_under(rb_mOgre,"Matrix3",rb_cObject);
	rb_define_alloc_func(rb_cOgreMatrix3,OgreMatrix3_alloc);
	rb_define_method(rb_cOgreMatrix3,"initialize",RUBY_METHOD_FUNC(OgreMatrix3_initialize),3);
	rb_define_private_method(rb_cOgreMatrix3,"initialize_copy",RUBY_METHOD_FUNC(OgreMatrix3_initialize_copy),1);
	
	rb_define_method(rb_cOgreMatrix3,"inspect",RUBY_METHOD_FUNC(OgreMatrix3_inspect),0);
	rb_define_method(rb_cOgreMatrix3,"-@",RUBY_METHOD_FUNC(OgreMatrix3_minusself),0);
	rb_define_alias(rb_cOgreMatrix3,"eql?","==");

	rb_define_method(rb_cOgreMatrix3,"+",RUBY_METHOD_FUNC(OgreMatrix3_plus),1);
	rb_define_method(rb_cOgreMatrix3,"-",RUBY_METHOD_FUNC(OgreMatrix3_minus),1);
	rb_define_method(rb_cOgreMatrix3,"*",RUBY_METHOD_FUNC(OgreMatrix3_mal),1);

	rb_define_method(rb_cOgreMatrix3,"hash",RUBY_METHOD_FUNC(OgreMatrix3_hash),0);
	rb_define_method(rb_cOgreMatrix3,"swap",RUBY_METHOD_FUNC(OgreMatrix3_swap),1);

	rb_define_method(rb_cOgreMatrix3,"marshal_dump",RUBY_METHOD_FUNC(OgreMatrix3_marshal_dump),0);
	rb_define_method(rb_cOgreMatrix3,"marshal_load",RUBY_METHOD_FUNC(OgreMatrix3_marshal_load),1);

	rb_define_const(rb_cOgreMatrix3,"Zero",wrap(Ogre::Matrix3::ZERO));
}
