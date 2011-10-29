#include "ogreaxisalignedbox.hpp"
#include "ogrevector3.hpp"
#define _self wrap<Ogre::AxisAlignedBox*>(self)
VALUE rb_cOgreAxisAlignedBox;

VALUE OgreAxisAlignedBox_alloc(VALUE self)
{
	return wrap(new Ogre::AxisAlignedBox);
}


macro_attr(AxisAlignedBox,Maximum,Ogre::Vector3)
macro_attr(AxisAlignedBox,Minimum,Ogre::Vector3)


/*
*/
VALUE OgreAxisAlignedBox_equal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreAxisAlignedBox)){
		return _self == wrap<Ogre::AxisAlignedBox*>(other) ? Qtrue : Qfalse;
	}else
		return Qfalse;
}

/*
*/
VALUE OgreAxisAlignedBox_swap(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreAxisAlignedBox)){
		return self;
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreAxisAlignedBox),rb_obj_classname(other));
}

/*
*/
VALUE OgreAxisAlignedBox_center(VALUE self)
{
	if(_self->isFinite())
		return wrap(_self->getCenter());
	return Qnil;
}
/*
*/
VALUE OgreAxisAlignedBox_size(VALUE self)
{
	return wrap(_self->getSize());
}
/*
*/
VALUE OgreAxisAlignedBox_volume(VALUE self)
{
	return DBL2NUM(_self->volume());
}
/*
 * call-seq:
 *   rect.hash -> Integer
 * 
 * hash from the combined rect values.
 * ===Return value
 * Integer
*/
VALUE OgreAxisAlignedBox_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	
	rb_ary_push(result,OgreAxisAlignedBox_getMaximum(self));
	rb_ary_push(result,OgreAxisAlignedBox_getMinimum(self));
	return rb_funcall(result,rb_intern("hash"),0);
}



/*
	
*/
VALUE OgreAxisAlignedBox_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,DBL2NUM(_self->getMaximum().x));
	rb_ary_push(result,DBL2NUM(_self->getMaximum().y));
	rb_ary_push(result,DBL2NUM(_self->getMaximum().z));
	rb_ary_push(result,DBL2NUM(_self->getMinimum().x));
	rb_ary_push(result,DBL2NUM(_self->getMinimum().y));
	rb_ary_push(result,DBL2NUM(_self->getMinimum().z));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddddd"));
}
/*

*/
VALUE OgreAxisAlignedBox_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddddd"));
	Ogre::Real x,y,z;
	z=NUM2DBL(rb_ary_pop(result));
	y=NUM2DBL(rb_ary_pop(result));
	x=NUM2DBL(rb_ary_pop(result));
	_self->setMinimum(x,y,z);
	z=NUM2DBL(rb_ary_pop(result));
	y=NUM2DBL(rb_ary_pop(result));
	x=NUM2DBL(rb_ary_pop(result));
	_self->setMaximum(x,y,z);
	return self;
}

void Init_OgreAxisAlignedBox(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_define_attr(rb_cOgreAxisAlignedBox,"maximum",1,1);
	rb_define_attr(rb_cOgreAxisAlignedBox,"minimum",1,1);
#endif
	rb_cOgreAxisAlignedBox = rb_define_class_under(rb_mOgre,"AxisAlignedBox",rb_cObject);
	rb_define_alloc_func(rb_cOgreAxisAlignedBox,OgreAxisAlignedBox_alloc);

	rb_define_method(rb_cOgreAxisAlignedBox,"==",RUBY_METHOD_FUNC(OgreAxisAlignedBox_equal),1);
//	rb_define_method(rb_cOgreAxisAlignedBox,"swap",RUBY_METHOD_FUNC(OgreAxisAlignedBox_swap),1);
	rb_define_method(rb_cOgreAxisAlignedBox,"hash",RUBY_METHOD_FUNC(OgreAxisAlignedBox_hash),0);
	
	rb_define_method(rb_cOgreAxisAlignedBox,"marshal_dump",RUBY_METHOD_FUNC(OgreAxisAlignedBox_marshal_dump),0);
	rb_define_method(rb_cOgreAxisAlignedBox,"marshal_load",RUBY_METHOD_FUNC(OgreAxisAlignedBox_marshal_load),1);

	rb_define_method(rb_cOgreAxisAlignedBox,"center",RUBY_METHOD_FUNC(OgreAxisAlignedBox_center),0);
	rb_define_method(rb_cOgreAxisAlignedBox,"size",RUBY_METHOD_FUNC(OgreAxisAlignedBox_size),0);
	rb_define_method(rb_cOgreAxisAlignedBox,"volume",RUBY_METHOD_FUNC(OgreAxisAlignedBox_volume),0);
	
	
	rb_define_attr_method(rb_cOgreAxisAlignedBox,"maximum",OgreAxisAlignedBox_getMaximum,OgreAxisAlignedBox_setMaximum);
	rb_define_attr_method(rb_cOgreAxisAlignedBox,"minimum",OgreAxisAlignedBox_getMinimum,OgreAxisAlignedBox_setMinimum);
}
