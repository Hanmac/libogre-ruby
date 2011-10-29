#include "ogreradian.hpp"
#include "ogredegree.hpp"

#define _self wrap<Ogre::Degree*>(self)
VALUE rb_cOgreDegree;

VALUE OgreDegree_alloc(VALUE self)
{
	return wrap(new Ogre::Degree);
}

Ogre::Degree* rb_to_degree(const VALUE &vdegree)
{
	return wrap<Ogre::Degree*>(vdegree);
}
/*
*/
VALUE OgreDegree_initialize(VALUE self,VALUE val)
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
VALUE OgreDegree_to_i(VALUE self)
{
	return INT2NUM((int)(_self->valueDegrees()));
}
/*
 * call-seq:
 *   to_f -> float
 * 
 * returns a Float
*/
VALUE OgreDegree_to_f(VALUE self)
{
	return DBL2NUM(_self->valueDegrees());
}
/*
*/
VALUE OgreDegree_initialize_copy(VALUE self, VALUE other)
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
VALUE OgreDegree_to_degree(VALUE self)
{
	return self;
}
/*
 * call-seq:
 *   to_degree -> Radian
 * 
 * retruns a Radian
*/
VALUE OgreDegree_to_radian(VALUE self)
{
	return wrap(Ogre::Radian(*_self));
}
/*
 * call-seq:
 *   -@ -> Degree
 * 
 * retruns -self
*/
VALUE OgreDegree_minusself(VALUE self)
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
VALUE OgreDegree_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%f°>");
	array[1]=rb_class_of(self);
	array[2]=OgreDegree_to_f(self);
	return rb_f_sprintf(3,array);
}
/*
*/
VALUE OgreDegree_compare(VALUE self,VALUE other)
{
	Ogre::Degree temp = *wrap<Ogre::Degree*>(other);
	return INT2NUM(*_self > temp ? 1 : *_self < temp ? -1 : 0);
}

/*
*/
VALUE OgreDegree_plus(VALUE self,VALUE other)
{
	return wrap(*_self + *wrap<Ogre::Degree*>(other));
}

/*
*/
VALUE OgreDegree_minus(VALUE self,VALUE other)
{
	return wrap(*_self - *wrap<Ogre::Degree*>(other));
}

/*
*/
VALUE OgreDegree_mal(VALUE self,VALUE other)
{
	return wrap(*_self * *wrap<Ogre::Degree*>(other));
}

/*
*/
VALUE OgreDegree_durch(VALUE self,VALUE other)
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
VALUE OgreDegree_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreDegree_to_f(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Degree into an string.
*/
VALUE OgreDegree_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreDegree_to_f(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("d"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 *
 * loads a string into an Degree.
*/
VALUE OgreDegree_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("d"));
	*_self= NUM2DBL(rb_ary_pop(result));
	return self;
}

//TODO: added "friend" methods for Float
void Init_OgreDegree(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreDegree = rb_define_class_under(rb_mOgre,"Degree",rb_cNumeric);
	rb_define_alloc_func(rb_cOgreDegree,OgreDegree_alloc);
	rb_define_method(rb_cOgreDegree,"initialize",RUBY_METHOD_FUNC(OgreDegree_initialize),1);
	rb_define_private_method(rb_cOgreDegree,"initialize_copy",RUBY_METHOD_FUNC(OgreDegree_initialize_copy),1);
	
	rb_define_method(rb_cOgreDegree,"to_i",RUBY_METHOD_FUNC(OgreDegree_to_i),0);
	rb_define_method(rb_cOgreDegree,"to_f",RUBY_METHOD_FUNC(OgreDegree_to_f),0);
	
	rb_define_method(rb_cOgreDegree,"to_degree",RUBY_METHOD_FUNC(OgreDegree_to_degree),0);
	rb_define_method(rb_cOgreDegree,"to_radian",RUBY_METHOD_FUNC(OgreDegree_to_radian),0);
	
	rb_define_method(rb_cOgreDegree,"-@",RUBY_METHOD_FUNC(OgreDegree_minusself),0);
	rb_define_method(rb_cOgreDegree,"inspect",RUBY_METHOD_FUNC(OgreDegree_inspect),0);
	
	rb_define_method(rb_cOgreDegree,"<=>",RUBY_METHOD_FUNC(OgreDegree_compare),1);
	
	rb_define_method(rb_cOgreDegree,"+",RUBY_METHOD_FUNC(OgreDegree_plus),1);
	rb_define_method(rb_cOgreDegree,"-",RUBY_METHOD_FUNC(OgreDegree_minus),1);
	rb_define_method(rb_cOgreDegree,"*",RUBY_METHOD_FUNC(OgreDegree_mal),1);
	rb_define_method(rb_cOgreDegree,"/",RUBY_METHOD_FUNC(OgreDegree_durch),1);
	
	rb_define_method(rb_cOgreDegree,"hash",RUBY_METHOD_FUNC(OgreDegree_hash),0);
	
	rb_define_method(rb_cOgreDegree,"marshal_dump",RUBY_METHOD_FUNC(OgreDegree_marshal_dump),0);
	rb_define_method(rb_cOgreDegree,"marshal_load",RUBY_METHOD_FUNC(OgreDegree_marshal_load),1);

}
