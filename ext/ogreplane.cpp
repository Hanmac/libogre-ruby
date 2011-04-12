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
VALUE OgrePlane_initialize(int argc,VALUE* argv,VALUE self)
{

	return self;
}
/*


*/
VALUE OgrePlane_inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:%s, %f>");
	array[1]=rb_class_of(self);
//	array[2]=rb_funcall(OgreSphere_get_center(self),rb_intern("inspect"),0);
//	array[3]=OgreSphere_get_radius(self);
	return rb_f_sprintf(4,array);
}
void Init_OgrePlane(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgrePlane = rb_define_class_under(rb_mOgre,"Plane",rb_cObject);
	rb_define_alloc_func(rb_cOgrePlane,OgrePlane_alloc);
	rb_define_method(rb_cOgrePlane,"initialize",RUBY_METHOD_FUNC(OgrePlane_initialize),-1);

	rb_define_method(rb_cOgrePlane,"inspect",RUBY_METHOD_FUNC(OgrePlane_inspect),0);
}

