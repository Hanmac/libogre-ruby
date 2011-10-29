#include "ogrerect.hpp"

#define _self wrap<Ogre::Rect*>(self)
VALUE rb_cOgreRect;

VALUE OgreRect_alloc(VALUE self)
{
	return wrap(new Ogre::Rect);
}
macro_attr_prop_with_func(Rect,left,INT2NUM,NUM2INT)
macro_attr_prop_with_func(Rect,top,INT2NUM,NUM2INT)
macro_attr_prop_with_func(Rect,right,INT2NUM,NUM2INT)
macro_attr_prop_with_func(Rect,bottom,INT2NUM,NUM2INT)


/*
*/
VALUE OgreRect_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	OgreRect_set_left(self,OgreRect_get_left(other));
	OgreRect_set_top(self,OgreRect_get_top(other));
	OgreRect_set_right(self,OgreRect_get_right(other));
	OgreRect_set_bottom(self,OgreRect_get_bottom(other));
	return result;
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
/*
*/
VALUE OgreRect_equal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreRect)){
		Ogre::Rect *cother = wrap<Ogre::Rect*>(other);
		return _self->left == cother->left && _self->top == cother->top && _self->right == cother->right && _self->bottom == cother->bottom ? Qtrue : Qfalse;
	}else
		return Qfalse;
}
/*
*/
VALUE OgreRect_merge(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreRect))
		return wrap(_self->merge(*wrap<Ogre::Rect*>(other)));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreRect),rb_obj_classname(other));
}
/*
*/
VALUE OgreRect_intersect(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreRect))
		return wrap(_self->intersect(*wrap<Ogre::Rect*>(other)));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreRect),rb_obj_classname(other));
}
/*
*/
VALUE OgreRect_swap(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreRect)){
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
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreRect),rb_obj_classname(other));
}

/*
 * call-seq:
 *   rect.hash -> Integer
 * 
 * hash from the combined rect values.
 * ===Return value
 * Integer
*/
VALUE OgreRect_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreRect_get_left(self));
	rb_ary_push(result,OgreRect_get_top(self));
	rb_ary_push(result,OgreRect_get_right(self));
	rb_ary_push(result,OgreRect_get_bottom(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Rect into an string.
*/
VALUE OgreRect_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreRect_get_left(self));
	rb_ary_push(result,OgreRect_get_top(self));
	rb_ary_push(result,OgreRect_get_right(self));
	rb_ary_push(result,OgreRect_get_bottom(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Rect.
*/
VALUE OgreRect_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddd"));
	OgreRect_set_bottom(self,rb_ary_pop(result));
	OgreRect_set_right(self,rb_ary_pop(result));
	OgreRect_set_top(self,rb_ary_pop(result));
	OgreRect_set_left(self,rb_ary_pop(result));
	return self;
}

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
	rb_cOgreRect = rb_define_class_under(rb_mOgre,"Rect",rb_cObject);
	rb_define_alloc_func(rb_cOgreRect,OgreRect_alloc);
	rb_define_private_method(rb_cOgreRect,"initialize_copy",RUBY_METHOD_FUNC(OgreRect_initialize_copy),1);

	rb_define_attr_method(rb_cOgreRect,"left",OgreRect_get_left,OgreRect_set_left);
	rb_define_attr_method(rb_cOgreRect,"top",OgreRect_get_top,OgreRect_set_top);
	rb_define_attr_method(rb_cOgreRect,"right",OgreRect_get_right,OgreRect_set_right);
	rb_define_attr_method(rb_cOgreRect,"bottom",OgreRect_get_bottom,OgreRect_set_bottom);

	rb_define_method(rb_cOgreRect,"null?",RUBY_METHOD_FUNC(OgreRect_isNull),0);
	rb_define_method(rb_cOgreRect,"setnull",RUBY_METHOD_FUNC(OgreRect_setNull),0);
	
	rb_define_method(rb_cOgreRect,"merge",RUBY_METHOD_FUNC(OgreRect_merge),1);
	rb_define_method(rb_cOgreRect,"intersect",RUBY_METHOD_FUNC(OgreRect_intersect),1);
	
	rb_define_method(rb_cOgreRect,"==",RUBY_METHOD_FUNC(OgreRect_equal),1);
	rb_define_method(rb_cOgreRect,"swap",RUBY_METHOD_FUNC(OgreRect_swap),1);
	
	rb_define_method(rb_cOgreRect,"hash",RUBY_METHOD_FUNC(OgreRect_hash),0);
	
	rb_define_method(rb_cOgreRect,"marshal_dump",RUBY_METHOD_FUNC(OgreRect_marshal_dump),0);
	rb_define_method(rb_cOgreRect,"marshal_load",RUBY_METHOD_FUNC(OgreRect_marshal_load),1);
}
