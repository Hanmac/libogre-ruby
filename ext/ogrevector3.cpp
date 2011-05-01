#include "ogrevector3.hpp"
#include "ogreradian.hpp"
#define _self wrap<Ogre::Vector3*>(self)
VALUE rb_cOgreVector3;

VALUE OgreVector3_alloc(VALUE self)
{
	Ogre::Vector3 *temp = new Ogre::Vector3;
	return wrap(temp);
}
/*:nodoc:


*/
VALUE OgreVector3_get_x(VALUE self)
{
	return DBL2NUM(_self->x);
}
/*:nodoc:


*/
VALUE OgreVector3_get_y(VALUE self)
{
	return DBL2NUM(_self->y);
}
/*:nodoc:


*/
VALUE OgreVector3_get_z(VALUE self)
{
	return DBL2NUM(_self->z);
}
/*:nodoc:


*/
VALUE OgreVector3_set_x(VALUE self,VALUE c)
{
	_self->x = NUM2DBL(c);
	return c;
}
/*:nodoc:


*/
VALUE OgreVector3_set_y(VALUE self,VALUE c)
{
	_self->y = NUM2DBL(c);
	return c;
}
/*:nodoc:


*/
VALUE OgreVector3_set_z(VALUE self,VALUE c)
{
	_self->z = NUM2DBL(c);
	return c;
}
/*


*/
VALUE OgreVector3_initialize(VALUE self,VALUE x,VALUE y,VALUE z)
{
	OgreVector3_set_x(self,x);
	OgreVector3_set_y(self,y);
	OgreVector3_set_z(self,z);
	return self;
}
/*


*/
VALUE OgreVector3_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	OgreVector3_set_x(self,OgreVector3_get_x(other));
	OgreVector3_set_y(self,OgreVector3_get_y(other));
	OgreVector3_set_z(self,OgreVector3_get_z(other));
	return result;
}
/*


*/
VALUE OgreVector3_inspect(VALUE self)
{
	VALUE array[5];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=OgreVector3_get_x(self);
	array[3]=OgreVector3_get_y(self);
	array[4]=OgreVector3_get_z(self);
	return rb_f_sprintf(5,array);
}
/*


*/
VALUE OgreVector3_minusself(VALUE self)
{
	return wrap(- *_self);
}
/*


*/
VALUE OgreVector3_compare(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3)){
		Ogre::Vector3 temp = *wrap<Ogre::Vector3*>(other);
		return INT2NUM(*_self > temp ? 1 : *_self < temp ? -1 : 0);
	}else
		return Qnil;
}
/*


*/
VALUE OgreVector3_swap(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3)){
		_self->swap(*wrap<Ogre::Vector3*>(other));
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(other));
	return self;
}
/*


*/
VALUE OgreVector3_plus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(*_self + *wrap<Ogre::Vector3*>(other));
	else
		return wrap(*_self + NUM2DBL(other));
}
/*


*/
VALUE OgreVector3_minus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(*_self - *wrap<Ogre::Vector3*>(other));
	else
		return wrap(*_self - NUM2DBL(other));
}
/*


*/
VALUE OgreVector3_mal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(*_self * *wrap<Ogre::Vector3*>(other));
	else
		return wrap(*_self * NUM2DBL(other));
}
/*


*/
VALUE OgreVector3_durch(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(*_self / *wrap<Ogre::Vector3*>(other));
	else
		return wrap(*_self / NUM2DBL(other));
}
/*


*/
VALUE OgreVector3_angleBetween(VALUE self, VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3)){
		return wrap(_self->angleBetween(*wrap<Ogre::Vector3*>(other)));
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(other));
}
/*


*/
VALUE OgreVector3_length(VALUE self)
{
	return DBL2NUM(_self->length());
}
/*


*/
VALUE OgreVector3_squaredlength(VALUE self)
{
	return DBL2NUM(_self->squaredLength());
}
/*


*/
VALUE OgreVector3_distance(VALUE self, VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3)){
		return wrap(_self->distance(*wrap<Ogre::Vector3*>(other)));
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(other));
}
/*


*/
VALUE OgreVector3_squaredDistance(VALUE self, VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3)){
		return wrap(_self->squaredDistance(*wrap<Ogre::Vector3*>(other)));
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(other));
}
/*


*/
VALUE OgreVector3_dotProduct(VALUE self, VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3)){
		return DBL2NUM(_self->dotProduct(*wrap<Ogre::Vector3*>(other)));
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(other));
}
/*


*/
VALUE OgreVector3_absdotProduct(VALUE self, VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3)){
		return DBL2NUM(_self->absDotProduct(*wrap<Ogre::Vector3*>(other)));
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(other));
}
/*


*/
VALUE OgreVector3_floor(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		_self->makeFloor(*wrap<Ogre::Vector3*>(other));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(other));
	return self;
}
/*


*/
VALUE OgreVector3_ceil(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		_self->makeCeil(*wrap<Ogre::Vector3*>(other));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(other));
	return self;
}
/*


*/
VALUE OgreVector3_isZeroLength(VALUE self)
{
	return _self->isZeroLength() ? Qtrue : Qfalse;
}
/*


*/
VALUE OgreVector3_midPoint(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(_self->midPoint(*wrap<Ogre::Vector3*>(other)));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(other));
}
/*


*/
VALUE OgreVector3_crossProduct(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(_self->crossProduct(*wrap<Ogre::Vector3*>(other)));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(other));
}
/*


*/
VALUE OgreVector3_isNaN(VALUE self)
{
	#if(OGRE_VERSION_MAJOR > 1 || (OGRE_VERSION_MAJOR == 1 && OGRE_VERSION_MINOR >= 7))
		return _self->isNaN() ? Qtrue : Qfalse;
	#else
		rb_raise(rb_eNotImpError,"need Ogre::Version >= 1.7");
	#endif
}
/*

*/
VALUE OgreVector3_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreVector3_get_x(self));
	rb_ary_push(result,OgreVector3_get_y(self));
	rb_ary_push(result,OgreVector3_get_z(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
	
*/
VALUE OgreVector3_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreVector3_get_x(self));
	rb_ary_push(result,OgreVector3_get_y(self));
	rb_ary_push(result,OgreVector3_get_z(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("ddd"));
}
/*

*/
VALUE OgreVector3_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("ddd"));
	OgreVector3_set_z(self,rb_ary_pop(result));
	OgreVector3_set_y(self,rb_ary_pop(result));
	OgreVector3_set_x(self,rb_ary_pop(result));
	return self;
}
/*


*/
VALUE Numeric_plus_OgreVector3(VALUE self, VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(NUM2DBL(self) + *wrap<Ogre::Vector3*>(other));
	else
		return rb_funcall(self,rb_intern("plusOgreVector3"),1,other);
}
/*


*/
VALUE Numeric_minus_OgreVector3(VALUE self, VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(NUM2DBL(self) + *wrap<Ogre::Vector3*>(other));
	else
		return rb_funcall(self,rb_intern("minusOgreVector3"),1,other);
}
/*


*/
VALUE Numeric_mal_OgreVector3(VALUE self, VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(NUM2DBL(self) + *wrap<Ogre::Vector3*>(other));
	else
		return rb_funcall(self,rb_intern("malOgreVector3"),1,other);
}
/*


*/
VALUE Numeric_durch_OgreVector3(VALUE self, VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		return wrap(NUM2DBL(self) + *wrap<Ogre::Vector3*>(other));
	else
		return rb_funcall(self,rb_intern("durchOgreVector3"),1,other);
}

/* Document-attr: x
 * the x Cordinate */
/* Document-attr: y
 * the y Cordinate */
/* Document-attr: z
 * the z Cordinate */
void Init_OgreVector3(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_define_attr(rb_cOgreVector3,"x",1,1);
	rb_define_attr(rb_cOgreVector3,"y",1,1);
	rb_define_attr(rb_cOgreVector3,"z",1,1);
#endif
	rb_cOgreVector3 = rb_define_class_under(rb_mOgre,"Vector3",rb_cObject);
	rb_define_alloc_func(rb_cOgreVector3,OgreVector3_alloc);
	rb_define_method(rb_cOgreVector3,"initialize",RUBY_METHOD_FUNC(OgreVector3_initialize),3);
	rb_define_private_method(rb_cOgreVector3,"initialize_copy",RUBY_METHOD_FUNC(OgreVector3_initialize_copy),1);
	
	rb_define_method(rb_cOgreVector3,"x",RUBY_METHOD_FUNC(OgreVector3_get_x),0);
	rb_define_method(rb_cOgreVector3,"y",RUBY_METHOD_FUNC(OgreVector3_get_y),0);
	rb_define_method(rb_cOgreVector3,"z",RUBY_METHOD_FUNC(OgreVector3_get_z),0);
	
	rb_define_method(rb_cOgreVector3,"x=",RUBY_METHOD_FUNC(OgreVector3_set_x),1);
	rb_define_method(rb_cOgreVector3,"y=",RUBY_METHOD_FUNC(OgreVector3_set_y),1);
	rb_define_method(rb_cOgreVector3,"z=",RUBY_METHOD_FUNC(OgreVector3_set_z),1);
	
	rb_define_method(rb_cOgreVector3,"inspect",RUBY_METHOD_FUNC(OgreVector3_inspect),0);
	rb_define_method(rb_cOgreVector3,"-@",RUBY_METHOD_FUNC(OgreVector3_minusself),0);
	rb_define_method(rb_cOgreVector3,"<=>",RUBY_METHOD_FUNC(OgreVector3_compare),1);
	rb_include_module(rb_cOgreVector3,rb_mComparable);
	rb_define_alias(rb_cOgreVector3,"eql?","==");
	rb_define_method(rb_cOgreVector3,"angleBetween",RUBY_METHOD_FUNC(OgreVector3_angleBetween),1);	

	rb_define_method(rb_cOgreVector3,"+",RUBY_METHOD_FUNC(OgreVector3_plus),1);
	rb_define_method(rb_cOgreVector3,"-",RUBY_METHOD_FUNC(OgreVector3_minus),1);
	rb_define_method(rb_cOgreVector3,"*",RUBY_METHOD_FUNC(OgreVector3_mal),1);
	rb_define_method(rb_cOgreVector3,"/",RUBY_METHOD_FUNC(OgreVector3_durch),1);

	rb_define_method(rb_cOgreVector3,"length",RUBY_METHOD_FUNC(OgreVector3_length),0);
	rb_define_method(rb_cOgreVector3,"squared_length",RUBY_METHOD_FUNC(OgreVector3_squaredlength),0);

	rb_define_method(rb_cOgreVector3,"distance",RUBY_METHOD_FUNC(OgreVector3_distance),1);
	rb_define_method(rb_cOgreVector3,"squared_distance",RUBY_METHOD_FUNC(OgreVector3_squaredDistance),1);
	
	rb_define_method(rb_cOgreVector3,"floor",RUBY_METHOD_FUNC(OgreVector3_floor),1);
	rb_define_method(rb_cOgreVector3,"ceil",RUBY_METHOD_FUNC(OgreVector3_ceil),1);
	rb_define_method(rb_cOgreVector3,"midPoint",RUBY_METHOD_FUNC(OgreVector3_midPoint),1);
	rb_define_method(rb_cOgreVector3,"crossProduct",RUBY_METHOD_FUNC(OgreVector3_crossProduct),1);
	
	rb_define_method(rb_cOgreVector3,"hash",RUBY_METHOD_FUNC(OgreVector3_hash),0);

	rb_define_method(rb_cOgreVector3,"zerolength?",RUBY_METHOD_FUNC(OgreVector3_isZeroLength),0);	
	rb_define_method(rb_cOgreVector3,"NaN?",RUBY_METHOD_FUNC(OgreVector3_isNaN),0);
	rb_define_method(rb_cOgreVector3,"swap",RUBY_METHOD_FUNC(OgreVector3_swap),1);

	rb_define_method(rb_cOgreVector3,"marshal_dump",RUBY_METHOD_FUNC(OgreVector3_marshal_dump),0);
	rb_define_method(rb_cOgreVector3,"marshal_load",RUBY_METHOD_FUNC(OgreVector3_marshal_load),1);
/*
	rb_define_alias(rb_cInteger,"plusOgreVector3","+");
	rb_define_alias(rb_cInteger,"minusOgreVector3","-");
	rb_define_alias(rb_cInteger,"malOgreVector3","*");
	rb_define_alias(rb_cInteger,"durchOgreVector3","/");
*/	
	rb_define_alias(rb_cFloat,"plusOgreVector3","+");
	rb_define_alias(rb_cFloat,"minusOgreVector3","-");
	rb_define_alias(rb_cFloat,"malOgreVector3","*");
	rb_define_alias(rb_cFloat,"durchOgreVector3","/");
/*
	rb_define_method(rb_cInteger,"+",RUBY_METHOD_FUNC(Numeric_plus_OgreVector3),1);
	rb_define_method(rb_cInteger,"-",RUBY_METHOD_FUNC(Numeric_minus_OgreVector3),1);
	rb_define_method(rb_cInteger,"*",RUBY_METHOD_FUNC(Numeric_mal_OgreVector3),1);
	rb_define_method(rb_cInteger,"/",RUBY_METHOD_FUNC(Numeric_durch_OgreVector3),1);
*/	
	rb_define_method(rb_cFloat,"+",RUBY_METHOD_FUNC(Numeric_plus_OgreVector3),1);
	rb_define_method(rb_cFloat,"-",RUBY_METHOD_FUNC(Numeric_minus_OgreVector3),1);
	rb_define_method(rb_cFloat,"*",RUBY_METHOD_FUNC(Numeric_mal_OgreVector3),1);
	rb_define_method(rb_cFloat,"/",RUBY_METHOD_FUNC(Numeric_durch_OgreVector3),1);

	rb_define_const(rb_cOgreVector3,"Zero",wrap(Ogre::Vector3::ZERO));
	rb_define_const(rb_cOgreVector3,"Unit_X",wrap(Ogre::Vector3::UNIT_X));
	rb_define_const(rb_cOgreVector3,"Unit_Y",wrap(Ogre::Vector3::UNIT_Y));
	rb_define_const(rb_cOgreVector3,"Unit_Z",wrap(Ogre::Vector3::UNIT_Z));
	rb_define_const(rb_cOgreVector3,"Negative_Unit_X",wrap(Ogre::Vector3::NEGATIVE_UNIT_X));
  rb_define_const(rb_cOgreVector3,"Negative_Unit_Y",wrap(Ogre::Vector3::NEGATIVE_UNIT_Y));
  rb_define_const(rb_cOgreVector3,"Negative_Unit_Z",wrap(Ogre::Vector3::NEGATIVE_UNIT_Z));
  rb_define_const(rb_cOgreVector3,"Unit_Scale",wrap(Ogre::Vector3::UNIT_SCALE));
}
