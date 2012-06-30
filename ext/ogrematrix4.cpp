#include "ogrematrix4.hpp"
#include "ogrevector3.hpp"
#include "ogreradian.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::Matrix4*>(self)
VALUE rb_cOgreMatrix4;

template <>
VALUE wrap< Ogre::Matrix4 >(Ogre::Matrix4 *matrix )
{
	return Data_Wrap_Struct(rb_cOgreMatrix4, NULL, free, matrix);
}

template <>
Ogre::Matrix4* wrap< Ogre::Matrix4* >(const VALUE &vmatrix)
{
	return unwrapPtr<Ogre::Matrix4>(vmatrix, rb_cOgreMatrix4);
}

template <>
Ogre::Matrix4 wrap< Ogre::Matrix4 >(const VALUE &vmatrix)
{
	return *unwrapPtr<Ogre::Matrix4>(vmatrix, rb_cOgreMatrix4);
}

namespace RubyOgre {
namespace Matrix4 {

macro_attr(Trans,Ogre::Vector3)


VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::Matrix4);
}

/*
*/
VALUE _initialize(VALUE self,VALUE x,VALUE y,VALUE z)
{
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
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
VALUE _inspect(VALUE self)
{
	VALUE array[5];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f)>");
	array[1]=rb_class_of(self);
	return rb_f_sprintf(5,array);
}
/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	_self->swap(*wrap<Ogre::Matrix4*>(other));
	return self;
}
/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreMatrix4))
		return wrap(*_self + *wrap<Ogre::Matrix4*>(other));
	else
		return Qnil;
}
/*
*/
VALUE _minus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreMatrix4))
		return wrap(*_self - *wrap<Ogre::Matrix4*>(other));
	else
		return Qnil;
}
/*
*/
VALUE _mal(VALUE self,VALUE other)
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
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
	
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("ddd"));
}
/*

*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("ddd"));
	return self;
}

}}

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
	using namespace RubyOgre::Matrix4;

	rb_cOgreMatrix4 = rb_define_class_under(rb_mOgre,"Matrix4",rb_cObject);
	rb_define_alloc_func(rb_cOgreMatrix4,_alloc);
	rb_define_method(rb_cOgreMatrix4,"initialize",RUBY_METHOD_FUNC(_initialize),3);
	rb_define_private_method(rb_cOgreMatrix4,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);
	
	rb_define_method(rb_cOgreMatrix4,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	rb_define_alias(rb_cOgreMatrix4,"eql?","==");

	rb_define_method(rb_cOgreMatrix4,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cOgreMatrix4,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cOgreMatrix4,"*",RUBY_METHOD_FUNC(_mal),1);

	rb_define_method(rb_cOgreMatrix4,"hash",RUBY_METHOD_FUNC(_hash),0);
	rb_define_method(rb_cOgreMatrix4,"swap",RUBY_METHOD_FUNC(_swap),1);

	rb_define_method(rb_cOgreMatrix4,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cOgreMatrix4,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

	rb_define_const(rb_cOgreMatrix4,"Zero",wrap(Ogre::Matrix4::ZERO));
	rb_define_const(rb_cOgreMatrix4,"Identity",wrap(Ogre::Matrix4::IDENTITY));

}
