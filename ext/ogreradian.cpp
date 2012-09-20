#include "ogreradian.hpp"
#include "ogredegree.hpp"
#define _self wrap<Ogre::Radian*>(self)
VALUE rb_cOgreRadian;

template <>
VALUE wrap< Ogre::Radian >(Ogre::Radian *radian )
{
	return Data_Wrap_Struct(rb_cOgreRadian, NULL, free, radian);
}

template <>
Ogre::Radian wrap< Ogre::Radian >(const VALUE &vradian)
{
	if (!rb_obj_is_kind_of(vradian, rb_cOgreRadian))
	{
		if(rb_obj_is_kind_of(vradian,rb_cOgreDegree))
			return Ogre::Radian(wrap<Ogre::Degree>(vradian));
		else if(rb_obj_is_kind_of(vradian,rb_cNumeric))
			return Ogre::Radian(NUM2DBL(vradian));
	}
	return *unwrapPtr<Ogre::Radian>(vradian, rb_cOgreRadian);
}

namespace RubyOgre {
namespace Radian {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::Radian);
}

/*
*/
VALUE _initialize(VALUE self,VALUE val)
{
	*_self= NUM2DBL(val);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	*_self =*wrap<Ogre::Radian*>(other);
	return result;
}
/*
 * call-seq:
 *   to_i -> int
 * 
 * returns a Integer
*/
VALUE _to_i(VALUE self)
{
	return INT2NUM((int)(_self->valueRadians()));
}
/*
 * call-seq:
 *   to_f -> float
 * 
 * returns a Float
*/
VALUE _to_f(VALUE self)
{
	return DBL2NUM(_self->valueRadians());
}
/*
 * call-seq:
 *   to_degree -> Degree
 * 
 * returns a Dregree
*/
VALUE _to_degree(VALUE self)
{
	return wrap(Ogre::Degree(*_self));
}

/*
 * call-seq:
 *   to_radian -> Radian
 * 
 * return self.
*/
VALUE _to_radian(VALUE self)
{
	return self;
}
/*
 * call-seq:
 *   -@ -> Radian
 * 
 * returns -self
*/
VALUE _minusself(VALUE self)
{
	return wrap(- *_self);
}

/*
 * call-seq:
 *   radian.inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%fπ>");
	array[1]=rb_class_of(self);
	array[2]=DBL2NUM(_self->valueRadians() / Ogre::Math::PI);
	return rb_f_sprintf(3,array);
}

/*
*/
VALUE _compare(VALUE self,VALUE other)
{
	Ogre::Radian temp = wrap<Ogre::Radian>(other);
	return INT2NUM(*_self > temp ? 1 : *_self < temp ? -1 : 0);
}

/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<Ogre::Radian>(other));
}

/*
*/
VALUE _minus(VALUE self,VALUE other)
{
	return wrap(*_self - wrap<Ogre::Radian>(other));
}

/*
*/
VALUE _mal(VALUE self,VALUE other)
{
	return wrap(*_self * wrap<Ogre::Radian>(other));
}

/*
*/
VALUE _durch(VALUE self,VALUE other)
{
	return wrap(*_self / NUM2DBL(other));
}
//TODO: added "friend" methods for Float

/*
 * call-seq:
 *   degree.hash -> Integer
 * 
 * hash from the combined Degree values.
 * ===Return value
 * Integer
*/
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_to_f(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Radian into an string.
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_to_f(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("d"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Radian.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("d"));
	*_self= NUM2DBL(rb_ary_pop(result));
	return self;
}

}}

void Init_OgreRadian(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	using namespace RubyOgre::Radian;

	rb_cOgreRadian = rb_define_class_under(rb_mOgre,"Radian",rb_cNumeric);
	rb_define_alloc_func(rb_cOgreRadian,_alloc);
	rb_define_method(rb_cOgreRadian,"initialize",RUBY_METHOD_FUNC(_initialize),1);
	rb_define_private_method(rb_cOgreRadian,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);

	rb_define_method(rb_cOgreRadian,"to_i",RUBY_METHOD_FUNC(_to_i),0);
	rb_define_method(rb_cOgreRadian,"to_f",RUBY_METHOD_FUNC(_to_f),0);
	
	rb_define_method(rb_cOgreRadian,"to_degree",RUBY_METHOD_FUNC(_to_degree),0);
	rb_define_method(rb_cOgreRadian,"to_radian",RUBY_METHOD_FUNC(_to_radian),0);
	
	rb_define_method(rb_cOgreRadian,"-@",RUBY_METHOD_FUNC(_minusself),0);
	rb_define_method(rb_cOgreRadian,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	
	rb_define_method(rb_cOgreRadian,"<=>",RUBY_METHOD_FUNC(_compare),1);
	
	rb_define_method(rb_cOgreRadian,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cOgreRadian,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cOgreRadian,"*",RUBY_METHOD_FUNC(_mal),1);
	rb_define_method(rb_cOgreRadian,"/",RUBY_METHOD_FUNC(_durch),1);
	
	
	rb_define_method(rb_cOgreRadian,"hash",RUBY_METHOD_FUNC(_hash),0);
	
	rb_define_method(rb_cOgreRadian,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cOgreRadian,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);
}
