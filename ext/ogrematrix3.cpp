#include "ogrematrix3.hpp"
#include "ogrevector3.hpp"
#include "ogreradian.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::Matrix3*>(self)
VALUE rb_cOgreMatrix3;

namespace RubyOgre {
namespace Matrix3 {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::Matrix3(0,0,0,0,0,0,0,0,0));
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);

	*_self = *wrap<Ogre::Matrix3*>(other);
	return result;
}
/*
 *
 */
VALUE _each(VALUE self)
{
	Ogre::Matrix3 &cself = *_self;
	for(uint i = 0; i < 3; ++i)
		rb_yield_values(3,DBL2NUM(cself[i][0]),DBL2NUM(cself[i][1]),DBL2NUM(cself[i][2]));
	return self;
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
	VALUE array[11];
	array[0]=rb_str_new2("#<%s:[[%f, %f, %f],[%f, %f, %f],[%f, %f, %f]]>");
	array[1]=rb_class_of(self);
	for(uint i = 0; i < 3; ++i)
		for(uint j = 0; j < 3; ++j)
			array[2+i*3+j] = DBL2NUM((*_self)[i][j]);
	return rb_f_sprintf(11,array);
}
/*
*/
VALUE _minusself(VALUE self)
{
	return wrap(- *_self);
}

/*
*/
VALUE _equal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreMatrix3)){
		return wrap(*_self == wrap<Ogre::Matrix3>(other));
	}else
		return Qfalse;
}

/*
 *
 */
VALUE _get(int argc,VALUE *argv,VALUE self)
{
	VALUE x,y;
	rb_scan_args(argc, argv, "11",&x,&y);
	if(NUM2UINT(x) < 3)
	{
		if(NIL_P(y))
			return wrap(_self->GetColumn(NUM2UINT(x)));
		else if(NUM2UINT(y) < 3)
			return DBL2NUM((*_self)[NUM2UINT(x)][NUM2UINT(y)]);
	}
	return Qnil;
}
/*
 *
 */
VALUE _set(int argc,VALUE *argv,VALUE self)
{
	VALUE x,y,val;
	rb_scan_args(argc, argv, "21",&x,&y,&val);
	if(NUM2UINT(x) < 3){
		if(NIL_P(val))
			_self->SetColumn(NUM2UINT(x),wrap<Ogre::Vector3>(y));
		if(NUM2UINT(y) < 3)
			(*_self)[NUM2UINT(x)][NUM2UINT(y)] = NUM2DBL(val);
	}
	return val;
}

/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	_self->swap(*wrap<Ogre::Matrix3*>(other));
	return self;
}
/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<Ogre::Matrix3>(other));
}
/*
*/
VALUE _minus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreMatrix3))
		return wrap(*_self - wrap<Ogre::Matrix3>(other));
	else
		return Qnil;
}
/*
*/
VALUE _mal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreMatrix3))
		return wrap(*_self * wrap<Ogre::Matrix3>(other));
	else if(wrapable<Ogre::Vector3>(other))
		return wrap(*_self * wrap<Ogre::Vector3>(other));
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
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();
	for(uint i = 0; i < 3; ++i)
		for(uint j = 0; j < 3; ++j)
			rb_ary_push(result,DBL2NUM((*_self)[i][j]));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
	
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	for(uint i = 0; i < 3; ++i)
		for(uint j = 0; j < 3; ++j)
			rb_ary_push(result,DBL2NUM((*_self)[i][j]));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("d*"));
}
/*

*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("d*"));
	for(uint i = 2; i > 0; --i)
			for(uint j = 2; j > 0; --j)
				(*_self)[i][j] = NUM2DBL(rb_ary_pop(result));
	return self;
}


}}
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
	using namespace RubyOgre::Matrix3;

	rb_cOgreMatrix3 = rb_define_class_under(rb_mOgre,"Matrix3",rb_cObject);
	rb_define_alloc_func(rb_cOgreMatrix3,_alloc);
	rb_define_private_method(rb_cOgreMatrix3,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);
	
	rb_define_method(rb_cOgreMatrix3,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	rb_define_method(rb_cOgreMatrix3,"-@",RUBY_METHOD_FUNC(_minusself),0);

	rb_define_method(rb_cOgreMatrix3,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cOgreMatrix3,rb_mEnumerable);

	rb_define_method(rb_cOgreMatrix3,"==",RUBY_METHOD_FUNC(_equal),1);
	rb_define_alias(rb_cOgreMatrix3,"eql?","==");

	rb_define_method(rb_cOgreMatrix3,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cOgreMatrix3,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cOgreMatrix3,"*",RUBY_METHOD_FUNC(_mal),1);

	rb_define_method(rb_cOgreMatrix3,"[]",RUBY_METHOD_FUNC(_get),-1);
	rb_define_method(rb_cOgreMatrix3,"[]=",RUBY_METHOD_FUNC(_set),-1);

	rb_define_method(rb_cOgreMatrix3,"hash",RUBY_METHOD_FUNC(_hash),0);
	rb_define_method(rb_cOgreMatrix3,"swap",RUBY_METHOD_FUNC(_swap),1);

	rb_define_method(rb_cOgreMatrix3,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cOgreMatrix3,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

	rb_define_const(rb_cOgreMatrix3,"Zero",wrap(Ogre::Matrix3::ZERO));
}
