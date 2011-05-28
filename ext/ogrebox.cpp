#include "ogrebox.hpp"

#define _self wrap<Ogre::Box*>(self)
VALUE rb_cOgreBox;

VALUE OgreBox_alloc(VALUE self)
{
	return wrap(new Ogre::Box);
}
/*:nodoc:
*/
VALUE OgreBox_get_left(VALUE self)
{
	return UINT2NUM(_self->left);
}
/*:nodoc:
*/
VALUE OgreBox_get_top(VALUE self)
{
	return UINT2NUM(_self->top);
}
/*:nodoc:
*/
VALUE OgreBox_get_right(VALUE self)
{
	return UINT2NUM(_self->right);
}
/*:nodoc:
*/
VALUE OgreBox_get_bottom(VALUE self)
{
	return UINT2NUM(_self->bottom);
}
/*:nodoc:
*/
VALUE OgreBox_get_front(VALUE self)
{
	return UINT2NUM(_self->front);
}
/*:nodoc:
*/
VALUE OgreBox_get_back(VALUE self)
{
	return UINT2NUM(_self->back);
}
/*:nodoc:
*/
VALUE OgreBox_set_left(VALUE self,VALUE val)
{
	_self->left = NUM2UINT(val);
	return val;
}
/*:nodoc:
*/
VALUE OgreBox_set_top(VALUE self,VALUE val)
{
	_self->top = NUM2UINT(val);
	return val;
}
/*:nodoc:
*/
VALUE OgreBox_set_right(VALUE self,VALUE val)
{
	_self->right = NUM2UINT(val);
	return val;
}
/*:nodoc:
*/
VALUE OgreBox_set_bottom(VALUE self,VALUE val)
{
	_self->bottom = NUM2UINT(val);
	return val;
}
/*:nodoc:
*/
VALUE OgreBox_set_front(VALUE self,VALUE val)
{
	_self->front = NUM2UINT(val);
	return val;
}
/*:nodoc:
*/
VALUE OgreBox_set_back(VALUE self,VALUE val)
{
	_self->back = NUM2UINT(val);
	return val;
}
/*
*/
VALUE OgreBox_width(VALUE self)
{
	return UINT2NUM(_self->getWidth());
}
/*
*/
VALUE OgreBox_height(VALUE self)
{
	return UINT2NUM(_self->getHeight());
}
/*
*/
VALUE OgreBox_depth(VALUE self)
{
	return UINT2NUM(_self->getDepth());
}

/*
*/
VALUE OgreBox_equal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreBox)){
		Ogre::Box *cother = wrap<Ogre::Box*>(other);
		return _self->left == cother->left && _self->top == cother->top &&
		_self->right == cother->right && _self->bottom == cother->bottom &&
		_self->front == cother->front && _self->back == cother->back ? Qtrue : Qfalse;
	}else
		return Qfalse;
}

/*
*/
VALUE OgreBox_swap(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreBox)){
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
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreBox),rb_obj_classname(other));
}

/*
 * call-seq:
 *   rect.hash -> Integer
 * 
 * hash from the combined rect values.
 * ===Return value
 * Integer
*/
VALUE OgreBox_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreBox_get_left(self));
	rb_ary_push(result,OgreBox_get_top(self));
	rb_ary_push(result,OgreBox_get_right(self));
	rb_ary_push(result,OgreBox_get_bottom(self));
	rb_ary_push(result,OgreBox_get_front(self));
	rb_ary_push(result,OgreBox_get_back(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Box into an string.	
*/
VALUE OgreBox_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreBox_get_left(self));
	rb_ary_push(result,OgreBox_get_top(self));
	rb_ary_push(result,OgreBox_get_right(self));
	rb_ary_push(result,OgreBox_get_bottom(self));
	rb_ary_push(result,OgreBox_get_front(self));
	rb_ary_push(result,OgreBox_get_back(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Box.
*/
VALUE OgreBox_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddddd"));
	
	OgreBox_set_back(self,rb_ary_pop(result));
	OgreBox_set_front(self,rb_ary_pop(result));
	OgreBox_set_bottom(self,rb_ary_pop(result));
	OgreBox_set_right(self,rb_ary_pop(result));
	OgreBox_set_top(self,rb_ary_pop(result));
	OgreBox_set_left(self,rb_ary_pop(result));
	return self;
}


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

	rb_define_method(rb_cOgreBox,"==",RUBY_METHOD_FUNC(OgreBox_equal),1);
	rb_define_method(rb_cOgreBox,"swap",RUBY_METHOD_FUNC(OgreBox_swap),1);
	rb_define_method(rb_cOgreBox,"hash",RUBY_METHOD_FUNC(OgreBox_hash),0);
	
	rb_define_method(rb_cOgreBox,"marshal_dump",RUBY_METHOD_FUNC(OgreBox_marshal_dump),0);
	rb_define_method(rb_cOgreBox,"marshal_load",RUBY_METHOD_FUNC(OgreBox_marshal_load),1);
}
