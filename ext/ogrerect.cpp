#include "ogrerect.hpp"
#include "ogreexception.hpp"

#define _self wrap<Ogre::Rect*>(self)
VALUE rb_cOgreRect;

template <>
VALUE wrap< Ogre::Rect >(Ogre::Rect *rect )
{
	return Data_Wrap_Struct(rb_cOgreRect, NULL, free, rect);
}


namespace RubyOgre {
namespace Rect {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::Rect);
}
macro_attr_prop(left,long)
macro_attr_prop(top,long)
macro_attr_prop(right,long)
macro_attr_prop(bottom,long)

/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_left(self,_get_left(other));
	_set_top(self,_get_top(other));
	_set_right(self,_get_right(other));
	_set_bottom(self,_get_bottom(other));
	return result;
}
/*
*/
VALUE _isNull(VALUE self)
{
	return _self->isNull() ? Qtrue : Qfalse;
}
/*
*/
VALUE _setNull(VALUE self)
{
	_self->setNull();
	return self;
}
/*
*/
VALUE _equal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreRect)){
		Ogre::Rect *cother = wrap<Ogre::Rect*>(other);
		return wrap(_self->left == cother->left && _self->top == cother->top && _self->right == cother->right && _self->bottom == cother->bottom);
	}else
		return Qfalse;
}
/*
*/
VALUE _merge(VALUE self,VALUE other)
{
	return wrap(_self->merge(*wrap<Ogre::Rect*>(other)));
}
/*
*/
VALUE _intersect(VALUE self,VALUE other)
{
	return wrap(_self->intersect(*wrap<Ogre::Rect*>(other)));
}
/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	Ogre::Rect *cother = wrap<Ogre::Rect*>(other);
	Ogre::Real temp[4];
	temp[0] = _self->left;
	temp[1] = _self->top;
	temp[2] = _self->right;
	temp[3] = _self->bottom;

	_self->left = cother->left;
	_self->top = cother->top;
	_self->right = cother->right;
	_self->bottom = cother->bottom;

	cother->left =temp[0];
	cother->top =temp[1];
	cother->right =temp[2];
	cother->bottom =temp[3];

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
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Rect into an string.
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_left(self));
	rb_ary_push(result,_get_top(self));
	rb_ary_push(result,_get_right(self));
	rb_ary_push(result,_get_bottom(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("d*"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Rect.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("d*"));
	_set_bottom(self,rb_ary_pop(result));
	_set_right(self,rb_ary_pop(result));
	_set_top(self,rb_ary_pop(result));
	_set_left(self,rb_ary_pop(result));
	return self;
}

}}

/*
 * Document-class: Ogre::Rect
 * 
 * This class represents an 2dimensional Rect.
*/
/* Document-attr: left
 * the left value */
/* Document-attr: top
 * the top value */
/* Document-attr: right
 * the right value */
/* Document-attr: bottom
 * the bottom value */
void Init_OgreRect(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");

	rb_define_attr(rb_cOgreRect,"left",1,1);
	rb_define_attr(rb_cOgreRect,"top",1,1);
	rb_define_attr(rb_cOgreRect,"right",1,1);
	rb_define_attr(rb_cOgreRect,"bottom",1,1);
#endif
	using namespace RubyOgre::Rect;

	rb_cOgreRect = rb_define_class_under(rb_mOgre,"Rect",rb_cObject);
	rb_define_alloc_func(rb_cOgreRect,_alloc);
	rb_define_private_method(rb_cOgreRect,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);

	rb_define_attr_method(rb_cOgreRect,"left",_get_left,_set_left);
	rb_define_attr_method(rb_cOgreRect,"top",_get_top,_set_top);
	rb_define_attr_method(rb_cOgreRect,"right",_get_right,_set_right);
	rb_define_attr_method(rb_cOgreRect,"bottom",_get_bottom,_set_bottom);

	rb_define_method(rb_cOgreRect,"null?",RUBY_METHOD_FUNC(_isNull),0);
	rb_define_method(rb_cOgreRect,"setnull",RUBY_METHOD_FUNC(_setNull),0);
	
	rb_define_method(rb_cOgreRect,"merge",RUBY_METHOD_FUNC(_merge),1);
	rb_define_method(rb_cOgreRect,"intersect",RUBY_METHOD_FUNC(_intersect),1);
	
	rb_define_method(rb_cOgreRect,"==",RUBY_METHOD_FUNC(_equal),1);
	rb_define_method(rb_cOgreRect,"swap",RUBY_METHOD_FUNC(_swap),1);
	
	rb_define_method(rb_cOgreRect,"hash",RUBY_METHOD_FUNC(_hash),0);
	
	rb_define_method(rb_cOgreRect,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cOgreRect,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

	registerklass<Ogre::Rect>(rb_cOgreRect);
}
