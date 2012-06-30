#include "ogrebox.hpp"
#include "ogreexception.hpp"

#define _self wrap<Ogre::Box*>(self)
VALUE rb_cOgreBox;

template <>
VALUE wrap< Ogre::Box >(Ogre::Box *box )
{
	return Data_Wrap_Struct(rb_cOgreBox, NULL, free, box);
}


namespace RubyOgre {
namespace Box {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::Box);
}
macro_attr_prop(left,uint)
macro_attr_prop(top,uint)
macro_attr_prop(right,uint)
macro_attr_prop(bottom,uint)
macro_attr_prop(front,uint)
macro_attr_prop(back,uint)

/*
*/
VALUE _width(VALUE self)
{
	return UINT2NUM(_self->getWidth());
}
/*
*/
VALUE _height(VALUE self)
{
	return UINT2NUM(_self->getHeight());
}
/*
*/
VALUE _depth(VALUE self)
{
	return UINT2NUM(_self->getDepth());
}

/*
*/
VALUE _equal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreBox)){
		Ogre::Box *cother = wrap<Ogre::Box*>(other);
		return wrap(_self->left == cother->left && _self->top == cother->top &&
		_self->right == cother->right && _self->bottom == cother->bottom &&
		_self->front == cother->front && _self->back == cother->back);
	}else
		return Qfalse;
}

/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	Ogre::Box *cother = wrap<Ogre::Box*>(other);
	Ogre::Real temp[6];
	temp[0] = _self->left;
	temp[1] = _self->top;
	temp[2] = _self->right;
	temp[3] = _self->bottom;
	temp[4] = _self->front;
	temp[5] = _self->back;

	_self->left = cother->left;
	_self->top = cother->top;
	_self->right = cother->right;
	_self->bottom = cother->bottom;
	_self->front = cother->front;
	_self->back = cother->back;

	cother->left =temp[0];
	cother->top =temp[1];
	cother->right =temp[2];
	cother->bottom =temp[3];
	cother->front =temp[4];
	cother->back =temp[5];

	return self;
}

/*
 * call-seq:
 *   rect.hash -> Integer
 * 
 * hash from the combined rect values.
 * ===Return value
 * Integer
*/
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_left(self));
	rb_ary_push(result,_get_top(self));
	rb_ary_push(result,_get_right(self));
	rb_ary_push(result,_get_bottom(self));
	rb_ary_push(result,_get_front(self));
	rb_ary_push(result,_get_back(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Box into an string.	
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_left(self));
	rb_ary_push(result,_get_top(self));
	rb_ary_push(result,_get_right(self));
	rb_ary_push(result,_get_bottom(self));
	rb_ary_push(result,_get_front(self));
	rb_ary_push(result,_get_back(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("d*"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Box.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("d*"));
	
	_set_back(self,rb_ary_pop(result));
	_set_front(self,rb_ary_pop(result));
	_set_bottom(self,rb_ary_pop(result));
	_set_right(self,rb_ary_pop(result));
	_set_top(self,rb_ary_pop(result));
	_set_left(self,rb_ary_pop(result));
	return self;
}

}}

/*
 * Document-class: Ogre::Box
 * 
 * This class represents an Box.
*/ 
/* Document-attr: left
 * returns the left value of Box. */
/* Document-attr: top
 * returns the top value of Box. */
/* Document-attr: right
 * returns the right value of Box. */
/* Document-attr: bottom
 * returns the bottom value of Box. */
/* Document-attr: front
 * returns the front value of Box. */
/* Document-attr: back
 * returns the back value of Box. */

void Init_OgreBox(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_define_attr(rb_cOgreBox,"left",1,1);
	rb_define_attr(rb_cOgreBox,"top",1,1);
	rb_define_attr(rb_cOgreBox,"right",1,1);
	rb_define_attr(rb_cOgreBox,"bottom",1,1);
	rb_define_attr(rb_cOgreBox,"front",1,1);
	rb_define_attr(rb_cOgreBox,"back",1,1);
#endif
	using namespace RubyOgre::Box;

	rb_cOgreBox = rb_define_class_under(rb_mOgre,"Box",rb_cObject);
	rb_define_alloc_func(rb_cOgreBox,_alloc);


	rb_define_attr_method(rb_cOgreBox,"left",_get_left,_set_left);
	rb_define_attr_method(rb_cOgreBox,"top",_get_top,_set_top);
	rb_define_attr_method(rb_cOgreBox,"right",_get_right,_set_right);
	rb_define_attr_method(rb_cOgreBox,"bottom",_get_bottom,_set_bottom);
	rb_define_attr_method(rb_cOgreBox,"front",_get_front,_set_front);
	rb_define_attr_method(rb_cOgreBox,"back",_get_back,_set_back);



	rb_define_method(rb_cOgreBox,"width",RUBY_METHOD_FUNC(_width),0);
	rb_define_method(rb_cOgreBox,"height",RUBY_METHOD_FUNC(_height),0);
	rb_define_method(rb_cOgreBox,"depth",RUBY_METHOD_FUNC(_depth),0);

	rb_define_method(rb_cOgreBox,"==",RUBY_METHOD_FUNC(_equal),1);
	rb_define_method(rb_cOgreBox,"swap",RUBY_METHOD_FUNC(_swap),1);
	rb_define_method(rb_cOgreBox,"hash",RUBY_METHOD_FUNC(_hash),0);
	
	rb_define_method(rb_cOgreBox,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cOgreBox,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

	registerklass<Ogre::Box>(rb_cOgreBox);
}
