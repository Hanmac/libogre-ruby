#include "ogrevector2.hpp"
#define _self wrap<Ogre::Vector2*>(self)
VALUE rb_cOgreVector2;

VALUE OgreVector2_alloc(VALUE self)
{
	return wrap(new Ogre::Vector2);
}
/*:nodoc:
*/
VALUE OgreVector2_get_x(VALUE self)
{
	return DBL2NUM(_self->x);
}
/*:nodoc:
*/
VALUE OgreVector2_get_y(VALUE self)
{
	return DBL2NUM(_self->y);
}
/*:nodoc:
*/
VALUE OgreVector2_set_x(VALUE self,VALUE c)
{
	_self->x = NUM2DBL(c);
	return c;
}
/*:nodoc:
*/
VALUE OgreVector2_set_y(VALUE self,VALUE c)
{
	_self->y = NUM2DBL(c);
	return c;
}
/*
*/
VALUE OgreVector2_initialize(VALUE self,VALUE x,VALUE y)
{
	OgreVector2_set_x(self,x);
	OgreVector2_set_y(self,y);
	return self;
}
/*
*/
VALUE OgreVector2_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	OgreVector2_set_x(self,OgreVector2_get_x(other));
	OgreVector2_set_y(self,OgreVector2_get_y(other));
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
VALUE OgreVector2_inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:(%f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=OgreVector2_get_x(self);
	array[3]=OgreVector2_get_y(self);
	return rb_f_sprintf(4,array);
}
/*
*/
VALUE OgreVector2_minusself(VALUE self)
{
	return wrap(- *_self);
}
/*
*/
VALUE OgreVector2_compare(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector2)){
		Ogre::Vector2 temp = *wrap<Ogre::Vector2*>(other);
		return INT2NUM(*_self > temp ? 1 : *_self < temp ? -1 : 0);
	}else
		return Qnil;
}
/*
*/
VALUE OgreVector2_swap(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector2)){
		_self->swap(*wrap<Ogre::Vector2*>(other));
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector2),rb_obj_classname(other));
	return self;
}
/*
*/
VALUE OgreVector2_plus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector2))
		return wrap(*_self + *wrap<Ogre::Vector2*>(other));
	else
		return wrap(*_self + NUM2DBL(other));
}
/*
*/
VALUE OgreVector2_minus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector2))
		return wrap(*_self - *wrap<Ogre::Vector2*>(other));
	else
		return wrap(*_self - NUM2DBL(other));
}
/*
*/
VALUE OgreVector2_mal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector2))
		return wrap(*_self * *wrap<Ogre::Vector2*>(other));
	else
		return wrap(*_self * NUM2DBL(other));
}
/*
*/
VALUE OgreVector2_durch(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector2))
		return wrap(*_self / *wrap<Ogre::Vector2*>(other));
	else
		return wrap(*_self / NUM2DBL(other));
}
/*
*/
VALUE OgreVector2_length(VALUE self)
{
	return DBL2NUM(_self->length());
}
/*
*/
VALUE OgreVector2_squaredlength(VALUE self)
{
	return DBL2NUM(_self->squaredLength());
}
/*
*/
VALUE OgreVector2_distance(VALUE self, VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector2)){
		return wrap(_self->distance(*wrap<Ogre::Vector2*>(other)));
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector2),rb_obj_classname(other));
}
/*
*/
VALUE OgreVector2_squaredDistance(VALUE self, VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector2)){
		return wrap(_self->squaredDistance(*wrap<Ogre::Vector2*>(other)));
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector2),rb_obj_classname(other));
}
/*
*/
VALUE OgreVector2_dotProduct(VALUE self, VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector2)){
		return DBL2NUM(_self->dotProduct(*wrap<Ogre::Vector2*>(other)));
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector2),rb_obj_classname(other));
}
/*
*/
VALUE OgreVector2_isZeroLength(VALUE self)
{
	return _self->isZeroLength() ? Qtrue : Qfalse;
}
/*
*/
VALUE OgreVector2_crossProduct(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector2))
		return wrap(_self->crossProduct(*wrap<Ogre::Vector2*>(other)));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector2),rb_obj_classname(other));
}
/*
*/
VALUE OgreVector2_isNaN(VALUE self)
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
VALUE OgreVector2_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreVector2_get_x(self));
	rb_ary_push(result,OgreVector2_get_y(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Vector2 into an string.
*/
VALUE OgreVector2_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreVector2_get_x(self));
	rb_ary_push(result,OgreVector2_get_y(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Vector2.
*/
VALUE OgreVector2_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dd"));
	OgreVector2_set_y(self,rb_ary_pop(result));
	OgreVector2_set_x(self,rb_ary_pop(result));
	return self;
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
	rb_cOgreVector2 = rb_define_class_under(rb_mOgre,"Vector2",rb_cObject);
	rb_define_alloc_func(rb_cOgreVector2,OgreVector2_alloc);
	rb_define_method(rb_cOgreVector2,"initialize",RUBY_METHOD_FUNC(OgreVector2_initialize),2);
	rb_define_private_method(rb_cOgreVector2,"initialize_copy",RUBY_METHOD_FUNC(OgreVector2_initialize_copy),1);
	
	rb_define_method(rb_cOgreVector2,"x",RUBY_METHOD_FUNC(OgreVector2_get_x),0);
	rb_define_method(rb_cOgreVector2,"y",RUBY_METHOD_FUNC(OgreVector2_get_y),0);

	rb_define_method(rb_cOgreVector2,"x=",RUBY_METHOD_FUNC(OgreVector2_set_x),1);
	rb_define_method(rb_cOgreVector2,"y=",RUBY_METHOD_FUNC(OgreVector2_set_y),1);

	rb_define_method(rb_cOgreVector2,"inspect",RUBY_METHOD_FUNC(OgreVector2_inspect),0);
	rb_define_method(rb_cOgreVector2,"-@",RUBY_METHOD_FUNC(OgreVector2_minusself),0);
	rb_define_method(rb_cOgreVector2,"<=>",RUBY_METHOD_FUNC(OgreVector2_compare),1);
	rb_include_module(rb_cOgreVector2,rb_mComparable);
	rb_define_alias(rb_cOgreVector2,"eql?","==");

	rb_define_method(rb_cOgreVector2,"+",RUBY_METHOD_FUNC(OgreVector2_plus),1);
	rb_define_method(rb_cOgreVector2,"-",RUBY_METHOD_FUNC(OgreVector2_minus),1);
	rb_define_method(rb_cOgreVector2,"*",RUBY_METHOD_FUNC(OgreVector2_mal),1);
	rb_define_method(rb_cOgreVector2,"/",RUBY_METHOD_FUNC(OgreVector2_durch),1);

	rb_define_method(rb_cOgreVector2,"length",RUBY_METHOD_FUNC(OgreVector2_length),0);
	rb_define_method(rb_cOgreVector2,"squared_length",RUBY_METHOD_FUNC(OgreVector2_squaredlength),0);
	
	rb_define_method(rb_cOgreVector2,"hash",RUBY_METHOD_FUNC(OgreVector2_hash),0);

	rb_define_method(rb_cOgreVector2,"zerolength?",RUBY_METHOD_FUNC(OgreVector2_isZeroLength),0);	
	rb_define_method(rb_cOgreVector2,"NaN?",RUBY_METHOD_FUNC(OgreVector2_isNaN),0);
	rb_define_method(rb_cOgreVector2,"swap",RUBY_METHOD_FUNC(OgreVector2_swap),1);

	rb_define_method(rb_cOgreVector2,"marshal_dump",RUBY_METHOD_FUNC(OgreVector2_marshal_dump),0);
	rb_define_method(rb_cOgreVector2,"marshal_load",RUBY_METHOD_FUNC(OgreVector2_marshal_load),1);

	rb_define_const(rb_cOgreVector2,"Zero",wrap(Ogre::Vector2::ZERO));
	rb_define_const(rb_cOgreVector2,"Unit_X",wrap(Ogre::Vector2::UNIT_X));
	rb_define_const(rb_cOgreVector2,"Unit_Y",wrap(Ogre::Vector2::UNIT_Y));
	rb_define_const(rb_cOgreVector2,"Negative_Unit_X",wrap(Ogre::Vector2::NEGATIVE_UNIT_X));
  rb_define_const(rb_cOgreVector2,"Negative_Unit_Y",wrap(Ogre::Vector2::NEGATIVE_UNIT_Y));
  rb_define_const(rb_cOgreVector2,"Unit_Scale",wrap(Ogre::Vector2::UNIT_SCALE));
}
