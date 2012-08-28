#include "ogreradian.hpp"
#include "ogredegree.hpp"

#define _self wrap<Ogre::Degree*>(self)
VALUE rb_cOgreDegree;

template <>
VALUE wrap< Ogre::Degree >(Ogre::Degree *degree )
{
	return Data_Wrap_Struct(rb_cOgreDegree, NULL, free, degree);
}

template <>
Ogre::Degree wrap< Ogre::Degree >(const VALUE &vdegree)
{
	if(!rb_obj_is_kind_of(vdegree, rb_cOgreDegree))
	{
		if(rb_obj_is_kind_of(vdegree,rb_cOgreRadian)){
			return Ogre::Degree(wrap<Ogre::Radian>(vdegree));
		}else if(rb_obj_is_kind_of(vdegree,rb_cNumeric)){
			return Ogre::Degree(NUM2DBL(vdegree));
		}
	}
	return *unwrapPtr<Ogre::Degree>(vdegree, rb_cOgreDegree);
}

namespace RubyOgre {
namespace Degree {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::Degree);
}

/*
*/
VALUE _initialize(VALUE self,VALUE val)
{
	*_self= NUM2DBL(val);
	return self;
}
/*
 * call-seq:
 *   to_i -> int
 * 
 * returns a Integer
*/
VALUE _to_i(VALUE self)
{
	return INT2NUM((int)(_self->valueDegrees()));
}
/*
 * call-seq:
 *   to_f -> float
 * 
 * returns a Float
*/
VALUE _to_f(VALUE self)
{
	return DBL2NUM(_self->valueDegrees());
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	*_self =*wrap<Ogre::Degree*>(other);
	return result;
}
/*
 * call-seq:
 *   to_degree -> Degree
 * 
 * retruns self
*/
VALUE _to_degree(VALUE self)
{
	return self;
}
/*
 * call-seq:
 *   to_degree -> Radian
 * 
 * retruns a Radian
*/
VALUE _to_radian(VALUE self)
{
	return wrap(Ogre::Radian(*_self));
}
/*
 * call-seq:
 *   -@ -> Degree
 * 
 * retruns -self
*/
VALUE _minusself(VALUE self)
{
	return wrap(- *_self);
}
/*
 * call-seq:
 *   degree.inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%f°>");
	array[1]=rb_class_of(self);
	array[2]=_to_f(self);
	return rb_f_sprintf(3,array);
}
/*
*/
VALUE _compare(VALUE self,VALUE other)
{
	Ogre::Degree temp = wrap<Ogre::Degree>(other);
	return INT2NUM(*_self > temp ? 1 : *_self < temp ? -1 : 0);
}

/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<Ogre::Degree>(other));
}

/*
*/
VALUE _minus(VALUE self,VALUE other)
{
	return wrap(*_self - wrap<Ogre::Degree>(other));
}

/*
*/
VALUE _mal(VALUE self,VALUE other)
{
	return wrap(*_self * wrap<Ogre::Degree>(other));
}

/*
*/
VALUE _durch(VALUE self,VALUE other)
{
	return wrap(*_self / NUM2DBL(other));
}

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
 * packs a Degree into an string.
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
 * loads a string into an Degree.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("d"));
	*_self= NUM2DBL(rb_ary_pop(result));
	return self;
}

}}

//TODO: added "friend" methods for Float
void Init_OgreDegree(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	using namespace RubyOgre::Degree;

	rb_cOgreDegree = rb_define_class_under(rb_mOgre,"Degree",rb_cNumeric);
	rb_define_alloc_func(rb_cOgreDegree,_alloc);
	rb_define_method(rb_cOgreDegree,"initialize",RUBY_METHOD_FUNC(_initialize),1);
	rb_define_private_method(rb_cOgreDegree,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);
	
	rb_define_method(rb_cOgreDegree,"to_i",RUBY_METHOD_FUNC(_to_i),0);
	rb_define_method(rb_cOgreDegree,"to_f",RUBY_METHOD_FUNC(_to_f),0);
	
	rb_define_method(rb_cOgreDegree,"to_degree",RUBY_METHOD_FUNC(_to_degree),0);
	rb_define_method(rb_cOgreDegree,"to_radian",RUBY_METHOD_FUNC(_to_radian),0);
	
	rb_define_method(rb_cOgreDegree,"-@",RUBY_METHOD_FUNC(_minusself),0);
	rb_define_method(rb_cOgreDegree,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	
	rb_define_method(rb_cOgreDegree,"<=>",RUBY_METHOD_FUNC(_compare),1);
	
	rb_define_method(rb_cOgreDegree,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cOgreDegree,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cOgreDegree,"*",RUBY_METHOD_FUNC(_mal),1);
	rb_define_method(rb_cOgreDegree,"/",RUBY_METHOD_FUNC(_durch),1);
	
	rb_define_method(rb_cOgreDegree,"hash",RUBY_METHOD_FUNC(_hash),0);
	
	rb_define_method(rb_cOgreDegree,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cOgreDegree,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

	registerklass<Ogre::Degree>(rb_cOgreDegree);
}
