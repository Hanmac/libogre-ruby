#include "ogreradian.hpp"
#include "ogredegree.hpp"
#define _self wrap<Ogre::Radian*>(self)
VALUE rb_cOgreRadian;

VALUE OgreRadian_alloc(VALUE self)
{
	Ogre::Radian *temp = new Ogre::Radian;
	return wrap(temp);
}

/*


*/
VALUE OgreRadian_initialize(VALUE self,VALUE val)
{
	*_self= NUM2DBL(val);
	return self;
}
/*


*/
VALUE OgreRadian_to_i(VALUE self)
{
	return INT2NUM((int)(_self->valueRadians()));
}

/*


*/
VALUE OgreRadian_to_f(VALUE self)
{
	return DBL2NUM(_self->valueRadians());
}

/*


*/
VALUE OgreRadian_to_degree(VALUE self)
{
	return wrap(Ogre::Degree(*_self));
}

/*


*/
VALUE OgreRadian_to_radian(VALUE self)
{
	return self;
}

/*


*/
VALUE OgreRadian_minusself(VALUE self)
{
	return wrap(- *_self);
}

/*


*/
VALUE OgreRadian_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%fπ>");
	array[1]=rb_class_of(self);
	array[2]=DBL2NUM(_self->valueRadians() / Ogre::Math::PI);
	return rb_f_sprintf(3,array);
}

/*


*/
VALUE OgreRadian_compare(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreRadian)){
		Ogre::Radian temp = *wrap<Ogre::Radian*>(other);
		return INT2NUM(*_self > temp ? 1 : *_self < temp ? -1 : 0);
	}else if(rb_obj_is_kind_of(other,rb_cOgreDegree)){
		Ogre::Radian temp = Ogre::Radian(*wrap<Ogre::Degree*>(other));
		return INT2NUM(*_self > temp ? 1 : *_self < temp ? -1 : 0);
	}else{
		Ogre::Radian temp = Ogre::Radian(NUM2DBL(other));
		return INT2NUM(*_self > temp ? 1 : *_self < temp ? -1 : 0);
	}
}

/*


*/
VALUE OgreRadian_plus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreDegree)){
		return wrap(*_self + *wrap<Ogre::Degree*>(other));
	}else if(rb_obj_is_kind_of(other,rb_cOgreRadian)){
		return wrap(*_self + *wrap<Ogre::Radian*>(other));
	}else
		return wrap(*_self + Ogre::Radian(NUM2DBL(other)));
}

/*


*/
VALUE OgreRadian_minus(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreRadian)){
		return wrap(*_self - *wrap<Ogre::Radian*>(other));
	}else if(rb_obj_is_kind_of(other,rb_cOgreDegree)){
		return wrap(*_self - *wrap<Ogre::Degree*>(other));
	}else
		return wrap(*_self - Ogre::Radian(NUM2DBL(other)));
}

/*


*/
VALUE OgreRadian_mal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreRadian)){
		return wrap(*_self * *wrap<Ogre::Radian*>(other));
	}else if(rb_obj_is_kind_of(other,rb_cOgreDegree)){
		return wrap(*_self * Ogre::Radian(*wrap<Ogre::Degree*>(other)));
	}else
		return wrap(*_self * Ogre::Radian(NUM2DBL(other)));
}

/*


*/
VALUE OgreRadian_durch(VALUE self,VALUE other)
{
	return wrap(*_self / NUM2DBL(other));
}
//TODO: added "friend" methods for Float
void Init_OgreRadian(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreRadian = rb_define_class_under(rb_mOgre,"Radian",rb_cNumeric);
	rb_define_alloc_func(rb_cOgreRadian,OgreRadian_alloc);
	rb_define_method(rb_cOgreRadian,"initialize",RUBY_METHOD_FUNC(OgreRadian_initialize),1);

	rb_define_method(rb_cOgreRadian,"to_i",RUBY_METHOD_FUNC(OgreRadian_to_i),0);
	rb_define_method(rb_cOgreRadian,"to_f",RUBY_METHOD_FUNC(OgreRadian_to_f),0);
	
	rb_define_method(rb_cOgreRadian,"to_degree",RUBY_METHOD_FUNC(OgreRadian_to_degree),0);
	rb_define_method(rb_cOgreRadian,"to_radian",RUBY_METHOD_FUNC(OgreRadian_to_radian),0);
	
	rb_define_method(rb_cOgreRadian,"-@",RUBY_METHOD_FUNC(OgreRadian_minusself),0);
	rb_define_method(rb_cOgreRadian,"inspect",RUBY_METHOD_FUNC(OgreRadian_inspect),0);
	
	rb_define_method(rb_cOgreRadian,"<=>",RUBY_METHOD_FUNC(OgreRadian_compare),1);
	
	rb_define_method(rb_cOgreRadian,"+",RUBY_METHOD_FUNC(OgreRadian_plus),1);
	rb_define_method(rb_cOgreRadian,"-",RUBY_METHOD_FUNC(OgreRadian_minus),1);
	rb_define_method(rb_cOgreRadian,"*",RUBY_METHOD_FUNC(OgreRadian_mal),1);
	rb_define_method(rb_cOgreRadian,"/",RUBY_METHOD_FUNC(OgreRadian_durch),1);
}
