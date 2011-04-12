#include "ogrerect.hpp"

#define _self wrap<Ogre::Rect*>(self)
VALUE rb_cOgreRect;

VALUE OgreRect_alloc(VALUE self)
{
	Ogre::Rect *temp = new Ogre::Rect;
	return wrap(temp);
}
/*


*/
VALUE OgreRect_get_left(VALUE self)
{
	return INT2NUM(_self->left);
}
/*


*/
VALUE OgreRect_get_top(VALUE self)
{
	return INT2NUM(_self->top);
}
/*


*/
VALUE OgreRect_get_right(VALUE self)
{
	return INT2NUM(_self->right);
}
/*


*/
VALUE OgreRect_get_bottom(VALUE self)
{
	return INT2NUM(_self->bottom);
}
/*


*/
VALUE OgreRect_set_left(VALUE self,VALUE val)
{
	_self->left = NUM2INT(val);
	return val;
}
/*


*/
VALUE OgreRect_set_top(VALUE self,VALUE val)
{
	_self->top = NUM2INT(val);
	return val;
}
/*


*/
VALUE OgreRect_set_right(VALUE self,VALUE val)
{
	_self->right = NUM2INT(val);
	return val;
}
/*


*/
VALUE OgreRect_set_bottom(VALUE self,VALUE val)
{
	_self->bottom = NUM2INT(val);
	return val;
}
/*


*/
VALUE OgreRect_isNull(VALUE self)
{
	return _self->isNull() ? Qtrue : Qfalse;
}
/*


*/
VALUE OgreRect_setNull(VALUE self)
{
	_self->setNull();
	return self;
}


void Init_OgreRect(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreRect = rb_define_class_under(rb_mOgre,"Rect",rb_cObject);
	rb_define_alloc_func(rb_cOgreRect,OgreRect_alloc);

	rb_define_method(rb_cOgreRect,"left",RUBY_METHOD_FUNC(OgreRect_get_left),0);
	rb_define_method(rb_cOgreRect,"top",RUBY_METHOD_FUNC(OgreRect_get_top),0);
	rb_define_method(rb_cOgreRect,"right",RUBY_METHOD_FUNC(OgreRect_get_right),0);
	rb_define_method(rb_cOgreRect,"bottom",RUBY_METHOD_FUNC(OgreRect_get_bottom),0);

	rb_define_method(rb_cOgreRect,"left=",RUBY_METHOD_FUNC(OgreRect_set_left),1);
	rb_define_method(rb_cOgreRect,"top=",RUBY_METHOD_FUNC(OgreRect_set_top),1);
	rb_define_method(rb_cOgreRect,"right=",RUBY_METHOD_FUNC(OgreRect_set_right),1);
	rb_define_method(rb_cOgreRect,"bottom=",RUBY_METHOD_FUNC(OgreRect_set_bottom),1);

	rb_define_method(rb_cOgreRect,"null?",RUBY_METHOD_FUNC(OgreRect_isNull),0);
	rb_define_method(rb_cOgreRect,"setnull",RUBY_METHOD_FUNC(OgreRect_setNull),0);
}
