#include "ogresphere.hpp"
#include "ogrevector3.hpp"
#define _self wrap<Ogre::Sphere*>(self)
VALUE rb_cOgreSphere;


VALUE OgreSphere_alloc(VALUE self)
{
	Ogre::Sphere *temp = new Ogre::Sphere;
	return wrap(temp);
}

/*


*/
VALUE OgreSphere_set_center(VALUE self,VALUE vec)
{
	if(rb_obj_is_kind_of(vec,rb_cOgreVector3))
		_self->setCenter(*wrap<Ogre::Vector3*>(vec));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(vec));
	return vec;
}

/*


*/
VALUE OgreSphere_set_radius(VALUE self,VALUE radius)
{
	_self->setRadius(NUM2DBL(radius));
	return radius;
}

/*


*/
VALUE OgreSphere_get_center(VALUE self)
{
	return wrap(_self->getCenter());
}

/*


*/
VALUE OgreSphere_get_radius(VALUE self)
{
	return DBL2NUM(_self->getRadius());
}


/*


*/
VALUE OgreSphere_inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:%s, %f>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(OgreSphere_get_center(self),rb_intern("inspect"),0);
	array[3]=OgreSphere_get_radius(self);
	return rb_f_sprintf(4,array);
}

/*


*/
VALUE OgreSphere_initialize(VALUE self,VALUE vec,VALUE radius)
{
	OgreSphere_set_center(self,vec);
	OgreSphere_set_radius(self,radius);
	return self;
}


/*


*/
VALUE OgreSphere_equal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreSphere)){
		Ogre::Sphere *cother = wrap<Ogre::Sphere*>(other);
		return _self->getCenter() == cother->getCenter() && _self->getRadius() == cother->getRadius() ? Qtrue : Qfalse;
	}else
		return Qfalse;
}
/*


*/
VALUE OgreSphere_intersects(VALUE self,VALUE other)
{
	bool result;
	if(rb_obj_is_kind_of(other,rb_cOgreSphere))
		result = _self->intersects(*wrap<Ogre::Sphere*>(other));
	else if(rb_obj_is_kind_of(other,rb_cOgreVector3))
		result = _self->intersects(*wrap<Ogre::Vector3*>(other));
	else
		rb_raise(rb_eTypeError,"Exepted %s,%s got %s!",
		rb_class2name(rb_cOgreSphere),
		rb_class2name(rb_cOgreVector3),
		rb_obj_classname(other));
	return result ? Qtrue : Qfalse;
}
void Init_OgreSphere(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreSphere = rb_define_class_under(rb_mOgre,"Sphere",rb_cObject);
	rb_define_alloc_func(rb_cOgreSphere,OgreSphere_alloc);
	rb_define_method(rb_cOgreSphere,"initialize",RUBY_METHOD_FUNC(OgreSphere_initialize),2);
	
	rb_define_method(rb_cOgreSphere,"center",RUBY_METHOD_FUNC(OgreSphere_get_center),0);
	rb_define_method(rb_cOgreSphere,"radius",RUBY_METHOD_FUNC(OgreSphere_get_radius),0);

	rb_define_method(rb_cOgreSphere,"center=",RUBY_METHOD_FUNC(OgreSphere_set_center),1);
	rb_define_method(rb_cOgreSphere,"radius=",RUBY_METHOD_FUNC(OgreSphere_set_radius),1);

	rb_define_method(rb_cOgreSphere,"inspect",RUBY_METHOD_FUNC(OgreSphere_inspect),0);
	rb_define_method(rb_cOgreSphere,"intersects?",RUBY_METHOD_FUNC(OgreSphere_intersects),1);
	rb_define_method(rb_cOgreSphere,"==",RUBY_METHOD_FUNC(OgreSphere_equal),1);
}

