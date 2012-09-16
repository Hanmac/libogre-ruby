#include "ogrevector3.hpp"
#include "ogreradian.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::Vector3*>(self)
VALUE rb_cOgreVector3;


template <>
bool wrapable< Ogre::Vector3 >(const VALUE &obj)
{
	return rb_obj_is_kind_of(obj, rb_cOgreVector3) || (
	rb_respond_to(obj,rb_intern("x")) &&
	rb_respond_to(obj,rb_intern("y")) &&
	rb_respond_to(obj,rb_intern("z")));
}


template <>
VALUE wrap< Ogre::Vector3 >(Ogre::Vector3 *vector )
{
	return Data_Wrap_Struct(rb_cOgreVector3, NULL, free, vector);
}

template <>
Ogre::Vector3* wrap< Ogre::Vector3* >(const VALUE &vvector)
{
	return unwrapPtr<Ogre::Vector3>(vvector,rb_cOgreVector3);
}

template <>
Ogre::Vector3 wrap< Ogre::Vector3 >(const VALUE &vvector)
{
	if(SYMBOL_P(vvector)){
		ID id = SYM2ID(vvector);
		if(id == rb_intern("zero"))
			return Ogre::Vector3::ZERO;
		if(id == rb_intern("unit_x"))
			return Ogre::Vector3::UNIT_X;
		if(id == rb_intern("unit_y"))
			return Ogre::Vector3::UNIT_Y;
		if(id == rb_intern("unit_z"))
			return Ogre::Vector3::UNIT_Z;
	} else if (!rb_obj_is_kind_of(vvector, rb_cOgreVector3) &&
		rb_respond_to(vvector,rb_intern("x")) &&
		rb_respond_to(vvector,rb_intern("y")) &&
		rb_respond_to(vvector,rb_intern("z"))){
		 	Ogre::Vector3 vector;
		 	vector.x = NUM2DBL(rb_funcall(vvector,rb_intern("x"),0));
		 	vector.y = NUM2DBL(rb_funcall(vvector,rb_intern("y"),0));
		 	vector.z = NUM2DBL(rb_funcall(vvector,rb_intern("z"),0));
		 	return vector;
	}
	return *unwrapPtr<Ogre::Vector3>(vvector,rb_cOgreVector3);
}


namespace RubyOgre {
namespace Vector3 {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::Vector3);
}
macro_attr_prop(x,Ogre::Real)
macro_attr_prop(y,Ogre::Real)
macro_attr_prop(z,Ogre::Real)
/*
*/
VALUE _initialize(VALUE self,VALUE x,VALUE y,VALUE z)
{
	_set_x(self,x);
	_set_y(self,y);
	_set_z(self,z);
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
	VALUE array[5];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=_get_x(self);
	array[3]=_get_y(self);
	array[4]=_get_z(self);
	return rb_f_sprintf(5,array);
}
/*
 * call-seq:
 *   to_s -> String
 *
 * ===Return value
 * String
*/
VALUE _to_s(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("(%f, %f, %f)");
	array[1]=_get_x(self);
	array[2]=_get_y(self);
	array[3]=_get_z(self);
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
	if(rb_obj_is_kind_of(other,rb_cOgreVector3)){
		Ogre::Vector3 temp = wrap<Ogre::Vector3>(other);
		return INT2NUM(*_self > temp ? 1 : *_self < temp ? -1 : 0);
	}else
		return Qnil;
}
/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	_self->swap(*wrap<Ogre::Vector3*>(other));
	return self;
}
/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(*_self + *wrap<Ogre::Vector3*>(other));
	else
		return wrap(*_self + NUM2DBL(other));
}
/*
*/
VALUE _minus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(*_self - *wrap<Ogre::Vector3*>(other));
	else
		return wrap(*_self - NUM2DBL(other));
}
/*
*/
VALUE _mal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(*_self * *wrap<Ogre::Vector3*>(other));
	else
		return wrap(*_self * NUM2DBL(other));
}
/*
*/
VALUE _durch(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(*_self / *wrap<Ogre::Vector3*>(other));
	else
		return wrap(*_self / NUM2DBL(other));
}
/*
*/
VALUE _angleBetween(VALUE self, VALUE other)
{
	return wrap(_self->angleBetween(*wrap<Ogre::Vector3*>(other)));
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
	return wrap(_self->distance(*wrap<Ogre::Vector3*>(other)));
}
/*
*/
VALUE _squaredDistance(VALUE self, VALUE other)
{
	return wrap(_self->squaredDistance(*wrap<Ogre::Vector3*>(other)));
}
/*
*/
VALUE _dotProduct(VALUE self, VALUE other)
{
	return DBL2NUM(_self->dotProduct(*wrap<Ogre::Vector3*>(other)));
}
/*
*/
VALUE _absdotProduct(VALUE self, VALUE other)
{
	return DBL2NUM(_self->absDotProduct(*wrap<Ogre::Vector3*>(other)));
}
/*
*/
VALUE _floor(VALUE self,VALUE other)
{
	_self->makeFloor(*wrap<Ogre::Vector3*>(other));
	return self;
}
/*
*/
VALUE _ceil(VALUE self,VALUE other)
{
	_self->makeCeil(*wrap<Ogre::Vector3*>(other));
	return self;
}
/*
*/
VALUE _isZeroLength(VALUE self)
{
	return _self->isZeroLength() ? Qtrue : Qfalse;
}
/*
*/
VALUE _midPoint(VALUE self,VALUE other)
{
	return wrap(_self->midPoint(*wrap<Ogre::Vector3*>(other)));
}
/*
*/
VALUE _crossProduct(VALUE self,VALUE other)
{
	return wrap(_self->crossProduct(*wrap<Ogre::Vector3*>(other)));
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
 *   vector.hash -> Integer
 * 
 * hash from the combined vector3 values.
 * ===Return value
 * Integer
*/
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_x(self));
	rb_ary_push(result,_get_y(self));
	rb_ary_push(result,_get_z(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Vector3 into an string.
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_x(self));
	rb_ary_push(result,_get_y(self));
	rb_ary_push(result,_get_z(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("ddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Vector3.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("ddd"));
	_set_z(self,rb_ary_pop(result));
	_set_y(self,rb_ary_pop(result));
	_set_x(self,rb_ary_pop(result));
	return self;
}

}
}

/*
 * Document-class: Ogre::Vector3
 * 
 * This class represents an 3dimensional Vector.
*/ 
/* Document-attr: x
 * the x Cordinate */
/* Document-attr: y
 * the y Cordinate */
/* Document-attr: z
 * the z Cordinate */
 /* Document-const: Zero
 * a Vector2(0.0,0.0,0.0) */
 /* Document-const: Unit_X
 * a Vector2(1.0,0.0,0.0) */
 /* Document-const: Unit_Y
 * a Vector2(0.0,1.0,0.0) */
 /* Document-const: Unit_Z
 * a Vector2(0.0,0.0,1.0) */
 /* Document-const: Negative_Unit_X
 * a Vector2(-1.0,0.0,0.0) */
 /* Document-const: Negative_Unit_Y
 * a Vector2(0.0,-1.0,0.0) */
 /* Document-const: Negative_Unit_Z
 * a Vector2(0.0,,0.0-1.0) */
 /* Document-const: Unit_Scale
 * a Vector2(1.0,1.0,1.0) */
void Init_OgreVector3(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_define_attr(rb_cOgreVector3,"x",1,1);
	rb_define_attr(rb_cOgreVector3,"y",1,1);
	rb_define_attr(rb_cOgreVector3,"z",1,1);
#endif
	using namespace RubyOgre::Vector3;
	rb_cOgreVector3 = rb_define_class_under(rb_mOgre,"Vector3",rb_cObject);
	rb_define_alloc_func(rb_cOgreVector3,_alloc);
	rb_define_method(rb_cOgreVector3,"initialize",RUBY_METHOD_FUNC(_initialize),3);
	rb_define_private_method(rb_cOgreVector3,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);
	
	rb_define_attr_method(rb_cOgreVector3,"x",_get_x,_set_x);
	rb_define_attr_method(rb_cOgreVector3,"y",_get_y,_set_y);
	rb_define_attr_method(rb_cOgreVector3,"z",_get_z,_set_z);
	
	rb_define_method(rb_cOgreVector3,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	rb_define_method(rb_cOgreVector3,"to_s",RUBY_METHOD_FUNC(_to_s),0);

	rb_define_method(rb_cOgreVector3,"-@",RUBY_METHOD_FUNC(_minusself),0);
	rb_define_method(rb_cOgreVector3,"<=>",RUBY_METHOD_FUNC(_compare),1);
	rb_include_module(rb_cOgreVector3,rb_mComparable);
	rb_define_alias(rb_cOgreVector3,"eql?","==");
	rb_define_method(rb_cOgreVector3,"angleBetween",RUBY_METHOD_FUNC(_angleBetween),1);

	rb_define_method(rb_cOgreVector3,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cOgreVector3,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cOgreVector3,"*",RUBY_METHOD_FUNC(_mal),1);
	rb_define_method(rb_cOgreVector3,"/",RUBY_METHOD_FUNC(_durch),1);

	rb_define_method(rb_cOgreVector3,"length",RUBY_METHOD_FUNC(_length),0);
	rb_define_method(rb_cOgreVector3,"squared_length",RUBY_METHOD_FUNC(_squaredlength),0);

	rb_define_method(rb_cOgreVector3,"distance",RUBY_METHOD_FUNC(_distance),1);
	rb_define_method(rb_cOgreVector3,"squared_distance",RUBY_METHOD_FUNC(_squaredDistance),1);
	
	rb_define_method(rb_cOgreVector3,"dotProduct",RUBY_METHOD_FUNC(_dotProduct),1);
	rb_define_method(rb_cOgreVector3,"absdotProduct",RUBY_METHOD_FUNC(_absdotProduct),1);

	rb_define_method(rb_cOgreVector3,"floor",RUBY_METHOD_FUNC(_floor),1);
	rb_define_method(rb_cOgreVector3,"ceil",RUBY_METHOD_FUNC(_ceil),1);
	rb_define_method(rb_cOgreVector3,"midPoint",RUBY_METHOD_FUNC(_midPoint),1);
	rb_define_method(rb_cOgreVector3,"crossProduct",RUBY_METHOD_FUNC(_crossProduct),1);
	
	rb_define_method(rb_cOgreVector3,"hash",RUBY_METHOD_FUNC(_hash),0);

	rb_define_method(rb_cOgreVector3,"zerolength?",RUBY_METHOD_FUNC(_isZeroLength),0);
	rb_define_method(rb_cOgreVector3,"NaN?",RUBY_METHOD_FUNC(_isNaN),0);
	rb_define_method(rb_cOgreVector3,"swap",RUBY_METHOD_FUNC(_swap),1);

	rb_define_method(rb_cOgreVector3,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cOgreVector3,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

	rb_define_const(rb_cOgreVector3,"Zero",wrap(Ogre::Vector3::ZERO));
	rb_define_const(rb_cOgreVector3,"Unit_X",wrap(Ogre::Vector3::UNIT_X));
	rb_define_const(rb_cOgreVector3,"Unit_Y",wrap(Ogre::Vector3::UNIT_Y));
	rb_define_const(rb_cOgreVector3,"Unit_Z",wrap(Ogre::Vector3::UNIT_Z));
	rb_define_const(rb_cOgreVector3,"Negative_Unit_X",wrap(Ogre::Vector3::NEGATIVE_UNIT_X));
	rb_define_const(rb_cOgreVector3,"Negative_Unit_Y",wrap(Ogre::Vector3::NEGATIVE_UNIT_Y));
	rb_define_const(rb_cOgreVector3,"Negative_Unit_Z",wrap(Ogre::Vector3::NEGATIVE_UNIT_Z));
	rb_define_const(rb_cOgreVector3,"Unit_Scale",wrap(Ogre::Vector3::UNIT_SCALE));
}
