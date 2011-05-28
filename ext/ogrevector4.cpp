#include "ogrevector4.hpp"
#include "ogreradian.hpp"
#define _self wrap<Ogre::Vector4*>(self)
VALUE rb_cOgreVector4;

VALUE OgreVector4_alloc(VALUE self)
{
	return wrap(new Ogre::Vector4);
}
/*:nodoc:
*/
VALUE OgreVector4_get_x(VALUE self)
{
	return DBL2NUM(_self->x);
}
/*:nodoc:
*/
VALUE OgreVector4_get_y(VALUE self)
{
	return DBL2NUM(_self->y);
}
/*:nodoc:
*/
VALUE OgreVector4_get_z(VALUE self)
{
	return DBL2NUM(_self->z);
}
/*:nodoc:
*/
VALUE OgreVector4_get_w(VALUE self)
{
	return DBL2NUM(_self->w);
}
/*:nodoc:
*/
VALUE OgreVector4_set_x(VALUE self,VALUE c)
{
	_self->x = NUM2DBL(c);
	return c;
}
/*:nodoc:
*/
VALUE OgreVector4_set_y(VALUE self,VALUE c)
{
	_self->y = NUM2DBL(c);
	return c;
}
/*:nodoc:
*/
VALUE OgreVector4_set_z(VALUE self,VALUE c)
{
	_self->z = NUM2DBL(c);
	return c;
}
/*:nodoc:
*/
VALUE OgreVector4_set_w(VALUE self,VALUE c)
{
	_self->w = NUM2DBL(c);
	return c;
}
/*
*/
VALUE OgreVector4_initialize(VALUE self,VALUE x,VALUE y,VALUE z,VALUE w)
{
	OgreVector4_set_x(self,x);
	OgreVector4_set_y(self,y);
	OgreVector4_set_z(self,z);
	OgreVector4_set_w(self,w);
	return self;
}
/*
*/
VALUE OgreVector4_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	OgreVector4_set_x(self,OgreVector4_get_x(other));
	OgreVector4_set_y(self,OgreVector4_get_y(other));
	OgreVector4_set_z(self,OgreVector4_get_z(other));
	OgreVector4_set_w(self,OgreVector4_get_w(other));
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
VALUE OgreVector4_inspect(VALUE self)
{
	VALUE array[6];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=OgreVector4_get_x(self);
	array[3]=OgreVector4_get_y(self);
	array[4]=OgreVector4_get_z(self);
	array[5]=OgreVector4_get_w(self);
	return rb_f_sprintf(6,array);
}
/*
*/
VALUE OgreVector4_minusself(VALUE self)
{
	return wrap(- *_self);
}
/*
*/
VALUE OgreVector4_plus(VALUE self,VALUE other)
{
	return wrap(*_self + *wrap<Ogre::Vector4*>(other));
}
/*
*/
VALUE OgreVector4_minus(VALUE self,VALUE other)
{
	return wrap(*_self - *wrap<Ogre::Vector4*>(other));
}
/*
*/
VALUE OgreVector4_mal(VALUE self,VALUE other)
{
	return wrap(*_self * *wrap<Ogre::Vector4*>(other));
}
/*
*/
VALUE OgreVector4_durch(VALUE self,VALUE other)
{
	return wrap(*_self / *wrap<Ogre::Vector4*>(other));
}
/*
*/
VALUE OgreVector4_swap(VALUE self,VALUE other)
{
	_self->swap(*wrap<Ogre::Vector4*>(other));
	return self;
}
/*
*/
VALUE OgreVector4_dotProduct(VALUE self, VALUE other)
{
	return DBL2NUM(_self->dotProduct(*wrap<Ogre::Vector4*>(other)));
}
/*
*/
VALUE OgreVector4_isNaN(VALUE self)
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
VALUE OgreVector4_equal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector4))
		return *_self == *wrap<Ogre::Vector4*>(other) ? Qtrue : Qfalse;
	else
		return Qfalse;
}
/*
* call-seq:
 *   vector != other -> true or false 
 * 
 * 
 * ===Return value
 * boolean
*/
VALUE OgreVector4_nequal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector4))
		return *_self != *wrap<Ogre::Vector4*>(other) ? Qtrue : Qfalse;
	else
		return Qtrue;
}
/*
 * call-seq:
 *   vector.hash -> Integer
 * 
 * hash from the combined Vector4 values.
 * ===Return value
 * Integer
*/
VALUE OgreVector4_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreVector4_get_x(self));
	rb_ary_push(result,OgreVector4_get_y(self));
	rb_ary_push(result,OgreVector4_get_z(self));
	rb_ary_push(result,OgreVector4_get_w(self));	
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Vector4 into an string.
*/
VALUE OgreVector4_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreVector4_get_x(self));
	rb_ary_push(result,OgreVector4_get_y(self));
	rb_ary_push(result,OgreVector4_get_z(self));
	rb_ary_push(result,OgreVector4_get_w(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Vector4.
*/
VALUE OgreVector4_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddd"));
	OgreVector4_set_w(self,rb_ary_pop(result));
	OgreVector4_set_z(self,rb_ary_pop(result));
	OgreVector4_set_y(self,rb_ary_pop(result));
	OgreVector4_set_x(self,rb_ary_pop(result));
	return self;
}
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
	rb_cOgreVector4 = rb_define_class_under(rb_mOgre,"Vector4",rb_cObject);
	rb_define_alloc_func(rb_cOgreVector4,OgreVector4_alloc);
	rb_define_method(rb_cOgreVector4,"initialize",RUBY_METHOD_FUNC(OgreVector4_initialize),4);
	rb_define_private_method(rb_cOgreVector4,"initialize_copy",RUBY_METHOD_FUNC(OgreVector4_initialize_copy),1);
	
	rb_define_method(rb_cOgreVector4,"x",RUBY_METHOD_FUNC(OgreVector4_get_x),0);
	rb_define_method(rb_cOgreVector4,"y",RUBY_METHOD_FUNC(OgreVector4_get_y),0);
	rb_define_method(rb_cOgreVector4,"z",RUBY_METHOD_FUNC(OgreVector4_get_z),0);
	rb_define_method(rb_cOgreVector4,"w",RUBY_METHOD_FUNC(OgreVector4_get_w),0);
	
	rb_define_method(rb_cOgreVector4,"x=",RUBY_METHOD_FUNC(OgreVector4_set_x),1);
	rb_define_method(rb_cOgreVector4,"y=",RUBY_METHOD_FUNC(OgreVector4_set_y),1);
	rb_define_method(rb_cOgreVector4,"z=",RUBY_METHOD_FUNC(OgreVector4_set_z),1);
	rb_define_method(rb_cOgreVector4,"w=",RUBY_METHOD_FUNC(OgreVector4_set_w),1);
	
	rb_define_method(rb_cOgreVector4,"inspect",RUBY_METHOD_FUNC(OgreVector4_inspect),0);
	rb_define_method(rb_cOgreVector4,"-@",RUBY_METHOD_FUNC(OgreVector4_minusself),0);

	rb_define_method(rb_cOgreVector4,"==",RUBY_METHOD_FUNC(OgreVector4_equal),1);
	rb_define_method(rb_cOgreVector4,"!=",RUBY_METHOD_FUNC(OgreVector4_nequal),1);
	
	rb_define_alias(rb_cOgreVector4,"eql?","==");

	rb_define_method(rb_cOgreVector4,"+",RUBY_METHOD_FUNC(OgreVector4_plus),1);
	rb_define_method(rb_cOgreVector4,"-",RUBY_METHOD_FUNC(OgreVector4_minus),1);
	rb_define_method(rb_cOgreVector4,"*",RUBY_METHOD_FUNC(OgreVector4_mal),1);
	rb_define_method(rb_cOgreVector4,"/",RUBY_METHOD_FUNC(OgreVector4_durch),1);

	rb_define_method(rb_cOgreVector4,"dotProduct",RUBY_METHOD_FUNC(OgreVector4_dotProduct),1);
	
	rb_define_method(rb_cOgreVector4,"hash",RUBY_METHOD_FUNC(OgreVector4_hash),0);
	rb_define_method(rb_cOgreVector4,"swap",RUBY_METHOD_FUNC(OgreVector4_swap),1);
	rb_define_method(rb_cOgreVector4,"NaN?",RUBY_METHOD_FUNC(OgreVector4_isNaN),0);

	rb_define_method(rb_cOgreVector4,"marshal_dump",RUBY_METHOD_FUNC(OgreVector4_marshal_dump),0);
	rb_define_method(rb_cOgreVector4,"marshal_load",RUBY_METHOD_FUNC(OgreVector4_marshal_load),1);

	rb_define_const(rb_cOgreVector4,"Zero",wrap(Ogre::Vector4::ZERO));
}
