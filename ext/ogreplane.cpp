#include "ogreplane.hpp"
#include "ogrevector3.hpp"
#define _self wrap<Ogre::Plane*>(self)
VALUE rb_cOgrePlane;


VALUE OgrePlane_alloc(VALUE self)
{
	Ogre::Plane *temp = new Ogre::Plane;
	return wrap(temp);
}
/*


*/
VALUE OgrePlane_get_normal(VALUE self)
{
	return wrap(_self->normal);
}
/*


*/
VALUE OgrePlane_get_d(VALUE self)
{
	return DBL2NUM(_self->d);
}
/*


*/
VALUE OgrePlane_set_normal(VALUE self,VALUE vec)
{
	if(rb_obj_is_kind_of(vec,rb_cOgreVector3))
		_self->normal = *wrap<Ogre::Vector3*>(vec);
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(vec));
	return vec;
}
/*


*/
VALUE OgrePlane_set_d(VALUE self,VALUE d)
{
	_self->d = NUM2DBL(d);
	return d;
}
/*


*/
VALUE OgrePlane_initialize(int argc,VALUE* argv,VALUE self)
{
	VALUE vec,other,vec3;
	rb_scan_args(argc, argv, "21",&vec,&other,&vec3);
	if(!rb_obj_is_kind_of(vec,rb_cOgreVector3))
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(vec));
	if(NIL_P(vec3))
		_self->redefine(*wrap<Ogre::Vector3*>(vec),*wrap<Ogre::Vector3*>(other),*wrap<Ogre::Vector3*>(vec3));
	else if(rb_obj_is_kind_of(other,rb_cOgreVector3)){
		_self->redefine(*wrap<Ogre::Vector3*>(vec),*wrap<Ogre::Vector3*>(other));
	}else{
		OgrePlane_set_normal(self,vec);
		OgrePlane_set_d(self,other);
	}
	return self;
}
/*


*/
VALUE OgrePlane_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	OgrePlane_set_normal(self,OgrePlane_get_normal(other));
	OgrePlane_set_d(self,OgrePlane_get_d(other));
	return result;
}
/*


*/
VALUE OgrePlane_inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:%s, %f>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(OgrePlane_get_normal(self),rb_intern("inspect"),0);
	array[3]=OgrePlane_get_d(self);
	return rb_f_sprintf(4,array);
}
/*


*/
VALUE OgrePlane_equal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgrePlane)){
		return *_self == *wrap<Ogre::Plane*>(other) ? Qtrue : Qfalse;
	}else
		return Qfalse;
}
/*


*/
VALUE OgrePlane_getDistance(VALUE self,VALUE vec)
{
	if(rb_obj_is_kind_of(vec,rb_cOgreVector3))
		return DBL2NUM(_self->getDistance(*wrap<Ogre::Vector3*>(vec)));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(vec));
}
/*


*/
VALUE OgrePlane_projectVector(VALUE self,VALUE vec)
{
	if(rb_obj_is_kind_of(vec,rb_cOgreVector3))
		return wrap(_self->projectVector(*wrap<Ogre::Vector3*>(vec)));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(vec));
}

void Init_OgrePlane(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgrePlane = rb_define_class_under(rb_mOgre,"Plane",rb_cObject);
	rb_define_alloc_func(rb_cOgrePlane,OgrePlane_alloc);
	rb_define_method(rb_cOgrePlane,"initialize",RUBY_METHOD_FUNC(OgrePlane_initialize),-1);
	rb_define_private_method(rb_cOgrePlane,"initialize_copy",RUBY_METHOD_FUNC(OgrePlane_initialize_copy),1);
	rb_define_method(rb_cOgrePlane,"normal",RUBY_METHOD_FUNC(OgrePlane_get_normal),0);
	rb_define_method(rb_cOgrePlane,"d",RUBY_METHOD_FUNC(OgrePlane_get_d),0);
	rb_define_method(rb_cOgrePlane,"normal=",RUBY_METHOD_FUNC(OgrePlane_set_normal),1);
	rb_define_method(rb_cOgrePlane,"d=",RUBY_METHOD_FUNC(OgrePlane_set_d),1);
	
	rb_define_method(rb_cOgrePlane,"inspect",RUBY_METHOD_FUNC(OgrePlane_inspect),0);
	rb_define_method(rb_cOgrePlane,"==",RUBY_METHOD_FUNC(OgrePlane_equal),1);
	rb_define_method(rb_cOgrePlane,"distance",RUBY_METHOD_FUNC(OgrePlane_getDistance),1);
	rb_define_method(rb_cOgrePlane,"projectVector",RUBY_METHOD_FUNC(OgrePlane_projectVector),1);
}

