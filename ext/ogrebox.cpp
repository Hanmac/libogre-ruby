#include "ogrebox.hpp"

#define _self wrap<Ogre::Box*>(self)
VALUE rb_cOgreBox;

VALUE OgreBox_alloc(VALUE self)
{
	Ogre::Box *temp = new Ogre::Box;
	return wrap(temp);
}
/*


*/
VALUE OgreBox_get_left(VALUE self)
{
	return INT2NUM(_self->left);
}
/*


*/
VALUE OgreBox_get_top(VALUE self)
{
	return INT2NUM(_self->top);
}
/*


*/
VALUE OgreBox_get_right(VALUE self)
{
	return INT2NUM(_self->right);
}
/*


*/
VALUE OgreBox_get_bottom(VALUE self)
{
	return INT2NUM(_self->bottom);
}
/*


*/
VALUE OgreBox_get_front(VALUE self)
{
	return INT2NUM(_self->front);
}
/*


*/
VALUE OgreBox_get_back(VALUE self)
{
	return INT2NUM(_self->back);
}
/*


*/
VALUE OgreBox_set_left(VALUE self,VALUE val)
{
	_self->left = NUM2INT(val);
	return val;
}
/*


*/
VALUE OgreBox_set_top(VALUE self,VALUE val)
{
	_self->top = NUM2INT(val);
	return val;
}
/*


*/
VALUE OgreBox_set_right(VALUE self,VALUE val)
{
	_self->right = NUM2INT(val);
	return val;
}
/*


*/
VALUE OgreBox_set_bottom(VALUE self,VALUE val)
{
	_self->bottom = NUM2INT(val);
	return val;
}
/*


*/
VALUE OgreBox_set_front(VALUE self,VALUE val)
{
	_self->front = NUM2INT(val);
	return val;
}
/*


*/
VALUE OgreBox_set_back(VALUE self,VALUE val)
{
	_self->back = NUM2INT(val);
	return val;
}
/*


*/
VALUE OgreBox_width(VALUE self)
{
	return INT2NUM(_self->getWidth());
}
/*


*/
VALUE OgreBox_height(VALUE self)
{
	return INT2NUM(_self->getHeight());
}
/*


*/
VALUE OgreBox_depth(VALUE self)
{
	return INT2NUM(_self->getDepth());
}


void Init_OgreBox(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreBox = rb_define_class_under(rb_mOgre,"Box",rb_cObject);
	rb_define_alloc_func(rb_cOgreBox,OgreBox_alloc);


	rb_define_method(rb_cOgreBox,"left",RUBY_METHOD_FUNC(OgreBox_get_left),0);
	rb_define_method(rb_cOgreBox,"top",RUBY_METHOD_FUNC(OgreBox_get_top),0);
	rb_define_method(rb_cOgreBox,"right",RUBY_METHOD_FUNC(OgreBox_get_right),0);
	rb_define_method(rb_cOgreBox,"bottom",RUBY_METHOD_FUNC(OgreBox_get_bottom),0);
	rb_define_method(rb_cOgreBox,"front",RUBY_METHOD_FUNC(OgreBox_get_front),0);
	rb_define_method(rb_cOgreBox,"back",RUBY_METHOD_FUNC(OgreBox_get_back),0);

	rb_define_method(rb_cOgreBox,"left=",RUBY_METHOD_FUNC(OgreBox_set_left),1);
	rb_define_method(rb_cOgreBox,"top=",RUBY_METHOD_FUNC(OgreBox_set_top),1);
	rb_define_method(rb_cOgreBox,"right=",RUBY_METHOD_FUNC(OgreBox_set_right),1);
	rb_define_method(rb_cOgreBox,"bottom=",RUBY_METHOD_FUNC(OgreBox_set_bottom),1);
	rb_define_method(rb_cOgreBox,"front=",RUBY_METHOD_FUNC(OgreBox_set_front),1);
	rb_define_method(rb_cOgreBox,"back=",RUBY_METHOD_FUNC(OgreBox_set_back),1);


	rb_define_method(rb_cOgreBox,"width",RUBY_METHOD_FUNC(OgreBox_width),0);
	rb_define_method(rb_cOgreBox,"height",RUBY_METHOD_FUNC(OgreBox_height),0);
	rb_define_method(rb_cOgreBox,"depth",RUBY_METHOD_FUNC(OgreBox_depth),0);	
}
