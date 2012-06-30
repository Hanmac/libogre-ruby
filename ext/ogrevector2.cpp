#include "ogrevector2.hpp"
#include "ogreexception.hpp"

#define _self wrap<Ogre::Vector2*>(self)
VALUE rb_cOgreVector2;

namespace RubyOgre
{
namespace Vector2
{

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::Vector2);
}
macro_attr_prop(x,double)
macro_attr_prop(y,double)
/*
*/
VALUE _initialize(VALUE self,VALUE x,VALUE y)
{
	_set_x(self,x);
	_set_y(self,y);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_x(self,_get_x(other));
	_set_y(self,_get_y(other));
	return result;
}
/*
 * call-seq:
 *   vector2.inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:(%f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=_get_x(self);
	array[3]=_get_y(self);
	return rb_f_sprintf(4,array);
}
/*
*/
VALUE _minusself(VALUE self)
{
	return wrap(- *_self);
}
/*
*/
VALUE _compare(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector2)){
		Ogre::Vector2 temp = *wrap<Ogre::Vector2*>(other);
		return INT2NUM(*_self > temp ? 1 : *_self < temp ? -1 : 0);
	}else
		return Qnil;
}
/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	_self->swap(*wrap<Ogre::Vector2*>(other));
	return self;
}
/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector2))
		return wrap(*_self + *wrap<Ogre::Vector2*>(other));
	else
		return wrap(*_self + NUM2DBL(other));
}
/*
*/
VALUE _minus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector2))
		return wrap(*_self - *wrap<Ogre::Vector2*>(other));
	else
		return wrap(*_self - NUM2DBL(other));
}
/*
*/
VALUE _mal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector2))
		return wrap(*_self * *wrap<Ogre::Vector2*>(other));
	else
		return wrap(*_self * NUM2DBL(other));
}
/*
*/
VALUE _durch(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector2))
		return wrap(*_self / *wrap<Ogre::Vector2*>(other));
	else
		return wrap(*_self / NUM2DBL(other));
}
/*
*/
VALUE _length(VALUE self)
{
	return DBL2NUM(_self->length());
}
/*
*/
VALUE _squaredlength(VALUE self)
{
	return DBL2NUM(_self->squaredLength());
}
/*
*/
VALUE _distance(VALUE self, VALUE other)
{
	return wrap(_self->distance(*wrap<Ogre::Vector2*>(other)));
}
/*
*/
VALUE _squaredDistance(VALUE self, VALUE other)
{
	return wrap(_self->squaredDistance(*wrap<Ogre::Vector2*>(other)));
}
/*
*/
VALUE _dotProduct(VALUE self, VALUE other)
{
	return DBL2NUM(_self->dotProduct(*wrap<Ogre::Vector2*>(other)));
}
/*
*/
VALUE _isZeroLength(VALUE self)
{
	return _self->isZeroLength() ? Qtrue : Qfalse;
}
/*
*/
VALUE _crossProduct(VALUE self,VALUE other)
{
	return wrap(_self->crossProduct(*wrap<Ogre::Vector2*>(other)));
}
/*
*/
VALUE _isNaN(VALUE self)
{
	return _self->isNaN() ? Qtrue : Qfalse;
}
/*
 * call-seq:
 *   vector.hash -> Integer
 * 
 * hash from the combined vector2 values.
 * ===Return value
 * Integer
*/
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_x(self));
	rb_ary_push(result,_get_y(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Vector2 into an string.
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_x(self));
	rb_ary_push(result,_get_y(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Vector2.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dd"));
	_set_y(self,rb_ary_pop(result));
	_set_x(self,rb_ary_pop(result));
	return self;
}

}
}

/*
 * Document-class: Ogre::Vector2
 * 
 * This class represents an 2dimensional Vector.
*/ 
/* Document-attr: x
 * the x Cordinate */
/* Document-attr: y
 * the y Cordinate */
 /* Document-const: Zero
 * a Vector2(0.0,0.0) */
 /* Document-const: Unit_X
 * a Vector2(1.0,0.0) */
 /* Document-const: Unit_Y
 * a Vector2(0.0,1.0) */
 /* Document-const: Negative_Unit_X
 * a Vector2(-1.0,0.0) */
 /* Document-const: Negative_Unit_Y
 * a Vector2(0.0,-1.0) */
 /* Document-const: Unit_Scale
 * a Vector2(1.0,1.0) */
void Init_OgreVector2(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_define_attr(rb_cOgreVector2,"x",1,1);
	rb_define_attr(rb_cOgreVector2,"y",1,1);
#endif
	using namespace RubyOgre::Vector2;

	rb_cOgreVector2 = rb_define_class_under(rb_mOgre,"Vector2",rb_cObject);
	rb_define_alloc_func(rb_cOgreVector2,_alloc);
	rb_define_method(rb_cOgreVector2,"initialize",RUBY_METHOD_FUNC(_initialize),2);
	rb_define_private_method(rb_cOgreVector2,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);
	
	rb_define_attr_method(rb_cOgreVector2,"x",_get_x,_set_x);
	rb_define_attr_method(rb_cOgreVector2,"y",_get_y,_set_y);

	rb_define_method(rb_cOgreVector2,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	rb_define_method(rb_cOgreVector2,"-@",RUBY_METHOD_FUNC(_minusself),0);
	rb_define_method(rb_cOgreVector2,"<=>",RUBY_METHOD_FUNC(_compare),1);
	rb_include_module(rb_cOgreVector2,rb_mComparable);
	rb_define_alias(rb_cOgreVector2,"eql?","==");

	rb_define_method(rb_cOgreVector2,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cOgreVector2,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cOgreVector2,"*",RUBY_METHOD_FUNC(_mal),1);
	rb_define_method(rb_cOgreVector2,"/",RUBY_METHOD_FUNC(_durch),1);

	rb_define_method(rb_cOgreVector2,"length",RUBY_METHOD_FUNC(_length),0);
	rb_define_method(rb_cOgreVector2,"squared_length",RUBY_METHOD_FUNC(_squaredlength),0);
	
	rb_define_method(rb_cOgreVector2,"hash",RUBY_METHOD_FUNC(_hash),0);

	rb_define_method(rb_cOgreVector2,"zerolength?",RUBY_METHOD_FUNC(_isZeroLength),0);
	rb_define_method(rb_cOgreVector2,"NaN?",RUBY_METHOD_FUNC(_isNaN),0);
	rb_define_method(rb_cOgreVector2,"swap",RUBY_METHOD_FUNC(_swap),1);

	rb_define_method(rb_cOgreVector2,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cOgreVector2,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

	rb_define_const(rb_cOgreVector2,"Zero",wrap(Ogre::Vector2::ZERO));
	rb_define_const(rb_cOgreVector2,"Unit_X",wrap(Ogre::Vector2::UNIT_X));
	rb_define_const(rb_cOgreVector2,"Unit_Y",wrap(Ogre::Vector2::UNIT_Y));
	rb_define_const(rb_cOgreVector2,"Negative_Unit_X",wrap(Ogre::Vector2::NEGATIVE_UNIT_X));
	rb_define_const(rb_cOgreVector2,"Negative_Unit_Y",wrap(Ogre::Vector2::NEGATIVE_UNIT_Y));
	rb_define_const(rb_cOgreVector2,"Unit_Scale",wrap(Ogre::Vector2::UNIT_SCALE));
}
