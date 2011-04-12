#include "ogredegree.hpp"
#include "ogreradian.hpp"
#define _self wrap<Ogre::Degree*>(self)
VALUE rb_cOgreDegree;

VALUE OgreDegree_alloc(VALUE self)
{
	Ogre::Degree *temp = new Ogre::Degree;
	return wrap(temp);
}

/*


*/
VALUE OgreDegree_initialize(VALUE self,VALUE val)
{
	*_self= NUM2DBL(val);
	return self;
}
/*


*/
VALUE OgreDegree_to_i(VALUE self)
{
	return INT2NUM((int)(_self->valueDegrees()));
}
/*


*/
VALUE OgreDegree_to_f(VALUE self)
{
	return DBL2NUM(_self->valueDegrees());
}

/*


*/
VALUE OgreDegree_to_degree(VALUE self)
{
	return self;
}

/*


*/
VALUE OgreDegree_to_radian(VALUE self)
{
	return wrap(Ogre::Radian(*_self));
}

/*


*/
VALUE OgreDegree_minusself(VALUE self)
{
	return wrap(- *_self);
}

/*


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
	if(rb_obj_is_kind_of(other,rb_cOgreDegree)){
		Ogre::Degree temp = *wrap<Ogre::Degree*>(other);
		return INT2NUM(*_self > temp ? 1 : *_self < temp ? -1 : 0);
	}else if(rb_obj_is_kind_of(other,rb_cOgreRadian)){
		Ogre::Degree temp = Ogre::Degree(*wrap<Ogre::Radian*>(other));
		return INT2NUM(*_self > temp ? 1 : *_self < temp ? -1 : 0);
	}else{
		Ogre::Degree temp = Ogre::Degree(NUM2DBL(other));
		return INT2NUM(*_self > temp ? 1 : *_self < temp ? -1 : 0);
	}
}

/*


*/
VALUE OgreDegree_plus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreDegree)){
		return wrap(*_self + *wrap<Ogre::Degree*>(other));
	}else if(rb_obj_is_kind_of(other,rb_cOgreRadian)){
		return wrap(*_self + *wrap<Ogre::Radian*>(other));
	}else
		return wrap(*_self + Ogre::Degree(NUM2DBL(other)));
}

/*


*/
VALUE OgreDegree_minus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreDegree)){
		return wrap(*_self - *wrap<Ogre::Degree*>(other));
	}else if(rb_obj_is_kind_of(other,rb_cOgreRadian)){
		return wrap(*_self - *wrap<Ogre::Radian*>(other));
	}else
		return wrap(*_self - Ogre::Degree(NUM2DBL(other)));
}

/*


*/
VALUE OgreDegree_mal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreDegree)){
		return wrap(*_self * *wrap<Ogre::Degree*>(other));
	}else if(rb_obj_is_kind_of(other,rb_cOgreRadian)){
		return wrap(*_self * Ogre::Degree(*wrap<Ogre::Radian*>(other)));
	}else
		return wrap(*_self * Ogre::Degree(NUM2DBL(other)));
}

/*


*/
VALUE OgreDegree_durch(VALUE self,VALUE other)
{
	return wrap(*_self / NUM2DBL(other));
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
}
