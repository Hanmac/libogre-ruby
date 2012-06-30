#include "ogrevector4.hpp"
#include "ogrevector3.hpp"
#include "ogreradian.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::Vector4*>(self)
VALUE rb_cOgreVector4;


template <>
inline bool wrapable< Ogre::Vector4 >(const VALUE &obj)
{
	return rb_obj_is_kind_of(obj, rb_cOgreVector4) || (
	rb_respond_to(obj,rb_intern("x")) &&
	rb_respond_to(obj,rb_intern("y")) &&
	rb_respond_to(obj,rb_intern("z")));
}

template <>
VALUE wrap< Ogre::Vector4 >(Ogre::Vector4 *vector )
{
	return Data_Wrap_Struct(rb_cOgreVector4, NULL, free, vector);
}

template <>
Ogre::Vector4* wrap< Ogre::Vector4* >(const VALUE &vvector)
{
	return unwrapPtr<Ogre::Vector4>(vvector,rb_cOgreVector4);
}

template <>
Ogre::Vector4 wrap< Ogre::Vector4 >(const VALUE &vvector)
{
	Ogre::Vector4 vector;
	if(rb_obj_is_kind_of(vvector, rb_cNumeric))
		vector = NUM2DBL(vvector);
	else if(rb_respond_to(vvector,rb_intern("to_f")))
		vector = NUM2DBL(rb_funcall(vvector,rb_intern("to_f"),0));
	else if(rb_respond_to(vvector,rb_intern("to_i")))
		vector = NUM2DBL(rb_funcall(vvector,rb_intern("to_i"),0));
	else if(!rb_obj_is_kind_of(vvector, rb_cOgreVector4) &&
		rb_respond_to(vvector,rb_intern("x")) &&
		rb_respond_to(vvector,rb_intern("y")) &&
		rb_respond_to(vvector,rb_intern("z"))){
		if(rb_respond_to(vvector,rb_intern("w"))){
			vector.x = NUM2DBL(rb_funcall(vvector,rb_intern("x"),0));
			vector.y = NUM2DBL(rb_funcall(vvector,rb_intern("y"),0));
			vector.z = NUM2DBL(rb_funcall(vvector,rb_intern("z"),0));
			vector.w = NUM2DBL(rb_funcall(vvector,rb_intern("w"),0));
		}else
			vector = wrap<Ogre::Vector3>(vvector);
	}else
		return *unwrapPtr<Ogre::Vector4>(vvector,rb_cOgreVector4);
	return vector;
}


namespace RubyOgre {
namespace Vector4 {


VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::Vector4);
}

macro_attr_prop(x,double)
macro_attr_prop(y,double)
macro_attr_prop(z,double)
macro_attr_prop(w,double)
/*
*/
VALUE _initialize(VALUE self,VALUE x,VALUE y,VALUE z,VALUE w)
{
	_set_x(self,x);
	_set_y(self,y);
	_set_z(self,z);
	_set_w(self,w);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_x(self,_get_x(other));
	_set_y(self,_get_y(other));
	_set_z(self,_get_z(other));
	_set_w(self,_get_w(other));
	return result;
}
/*
 * call-seq:
 *   inspect -> String
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
	array[2]=_get_x(self);
	array[3]=_get_y(self);
	array[4]=_get_z(self);
	array[5]=_get_w(self);
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
VALUE _plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<Ogre::Vector4>(other));
}
/*
*/
VALUE _minus(VALUE self,VALUE other)
{
	return wrap(*_self - wrap<Ogre::Vector4>(other));
}
/*
*/
VALUE _mal(VALUE self,VALUE other)
{
	return wrap(*_self * wrap<Ogre::Vector4>(other));
}
/*
*/
VALUE _durch(VALUE self,VALUE other)
{
	return wrap(*_self / wrap<Ogre::Vector4>(other));
}
/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	_self->swap(*wrap<Ogre::Vector4*>(other));
	return self;
}
/*
*/
VALUE _dotProduct(VALUE self, VALUE other)
{
	return DBL2NUM(_self->dotProduct(wrap<Ogre::Vector4>(other)));
}
/*
*/
VALUE _isNaN(VALUE self)
{
	#if(OGRE_VERSION_MAJOR > 1 || (OGRE_VERSION_MAJOR == 1 && OGRE_VERSION_MINOR >= 7))
		return _self->isNaN() ? Qtrue : Qfalse;
	#else
		rb_raise(rb_eNotImpError,"need Ogre::Version >= 1.7");
	#endif
}

/*
* call-seq:
 *   vector == other -> true or false 
 * 
 * 
 * ===Return value
 * boolean
*/
VALUE _equal(VALUE self,VALUE other)
{
	if(self == other)
		return Qtrue;
	else if(wrapable<Ogre::Vector4>(other))
		return wrap(*_self == wrap<Ogre::Vector4>(other));
	else
		return Qfalse;
}

/*
 * call-seq:
 *   vector.hash -> Integer
 * 
 * hash from the combined Vector4 values.
 * ===Return value
 * Integer
*/
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_x(self));
	rb_ary_push(result,_get_y(self));
	rb_ary_push(result,_get_z(self));
	rb_ary_push(result,_get_w(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Vector4 into an string.
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_x(self));
	rb_ary_push(result,_get_y(self));
	rb_ary_push(result,_get_z(self));
	rb_ary_push(result,_get_w(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("d*"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Vector4.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("d*"));
	_set_w(self,rb_ary_pop(result));
	_set_z(self,rb_ary_pop(result));
	_set_y(self,rb_ary_pop(result));
	_set_x(self,rb_ary_pop(result));
	return self;
}

}}

/*
 * Document-class: Ogre::Vector4
 * 
 * This class represents an 4dimensional Vector.
*/ 
/* Document-attr: x
 * the x Cordinate */
/* Document-attr: y
 * the y Cordinate */
/* Document-attr: z
 * the z Cordinate */
/* Document-attr: w
 * the w Cordinate */
 /* Document-const: Zero
 * a Vector2(0.0,0.0,0.0,0.0) */
void Init_OgreVector4(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_define_attr(rb_cOgreVector4,"x",1,1);
	rb_define_attr(rb_cOgreVector4,"y",1,1);
	rb_define_attr(rb_cOgreVector4,"z",1,1);
	rb_define_attr(rb_cOgreVector4,"w",1,1);
#endif
	using namespace RubyOgre::Vector4;

	rb_cOgreVector4 = rb_define_class_under(rb_mOgre,"Vector4",rb_cObject);
	rb_define_alloc_func(rb_cOgreVector4,_alloc);
	rb_define_method(rb_cOgreVector4,"initialize",RUBY_METHOD_FUNC(_initialize),4);
	rb_define_private_method(rb_cOgreVector4,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);
	
	rb_define_attr_method(rb_cOgreVector4,"x",_get_x,_set_x);
	rb_define_attr_method(rb_cOgreVector4,"y",_get_y,_set_y);
	rb_define_attr_method(rb_cOgreVector4,"z",_get_z,_set_z);
	rb_define_attr_method(rb_cOgreVector4,"w",_get_w,_set_w);
	
	rb_define_method(rb_cOgreVector4,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	rb_define_method(rb_cOgreVector4,"-@",RUBY_METHOD_FUNC(_minusself),0);

	rb_define_method(rb_cOgreVector4,"==",RUBY_METHOD_FUNC(_equal),1);
	rb_define_alias(rb_cOgreVector4,"eql?","==");

	rb_define_method(rb_cOgreVector4,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cOgreVector4,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cOgreVector4,"*",RUBY_METHOD_FUNC(_mal),1);
	rb_define_method(rb_cOgreVector4,"/",RUBY_METHOD_FUNC(_durch),1);

	rb_define_method(rb_cOgreVector4,"dotProduct",RUBY_METHOD_FUNC(_dotProduct),1);
	
	rb_define_method(rb_cOgreVector4,"hash",RUBY_METHOD_FUNC(_hash),0);
	rb_define_method(rb_cOgreVector4,"swap",RUBY_METHOD_FUNC(_swap),1);
	rb_define_method(rb_cOgreVector4,"NaN?",RUBY_METHOD_FUNC(_isNaN),0);

	rb_define_method(rb_cOgreVector4,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cOgreVector4,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

	rb_define_const(rb_cOgreVector4,"Zero",wrap(Ogre::Vector4::ZERO));
}
