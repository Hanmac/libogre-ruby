#include "ogreplaneboundedvolume.hpp"
#include "ogreplane.hpp"
#define _self wrap<Ogre::PlaneBoundedVolume*>(self)
VALUE rb_cOgrePlaneBoundedVolume;

VALUE OgrePlaneBoundedVolume_alloc(VALUE self)
{
	return wrap(new Ogre::PlaneBoundedVolume);
}
/*
*/
VALUE OgrePlaneBoundedVolume_equal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgrePlaneBoundedVolume)){
		return _self == wrap<Ogre::PlaneBoundedVolume*>(other) ? Qtrue : Qfalse;
	}else
		return Qfalse;
}

/*
*/
VALUE OgrePlaneBoundedVolume_swap(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgrePlaneBoundedVolume)){
		return self;
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgrePlaneBoundedVolume),rb_obj_classname(other));
}

/*
*/
VALUE OgrePlaneBoundedVolume_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::Plane>(Ogre::VectorIterator<Ogre::PlaneBoundedVolume::PlaneList>(_self->planes.begin(),_self->planes.begin()));
	return self;
}
/*
*/
VALUE OgrePlaneBoundedVolume_push(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgrePlane)){
		_self->planes.push_back(*wrap<Ogre::Plane*>(other));
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgrePlane),rb_obj_classname(other));
	return self;
}

/*
*/
VALUE OgrePlaneBoundedVolume_pop(VALUE self)
{
	VALUE result = wrap(_self->planes.back());
	_self->planes.pop_back();
	return result;
}

/*
 * call-seq:
 *   rect.hash -> Integer
 * 
 * hash from the combined rect values.
 * ===Return value
 * Integer
*/
VALUE OgrePlaneBoundedVolume_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	Ogre::PlaneBoundedVolume::PlaneList::iterator it;
	for (it = _self->planes.begin(); it != _self->planes.begin(); ++it)
	{
		rb_ary_push(result,wrap(*it));
	}

	return rb_funcall(result,rb_intern("hash"),0);
}
/*
	
*/
VALUE OgrePlaneBoundedVolume_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("da*"));
}
/*

*/
VALUE OgrePlaneBoundedVolume_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddddd"));
	
	return self;
}

void Init_OgrePlaneBoundedVolume(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgrePlaneBoundedVolume = rb_define_class_under(rb_mOgre,"PlaneBoundedVolume",rb_cObject);
	rb_define_alloc_func(rb_cOgrePlaneBoundedVolume,OgrePlaneBoundedVolume_alloc);

	rb_define_method(rb_cOgrePlaneBoundedVolume,"==",RUBY_METHOD_FUNC(OgrePlaneBoundedVolume_equal),1);
//	rb_define_method(rb_cOgrePlaneBoundedVolume,"swap",RUBY_METHOD_FUNC(OgrePlaneBoundedVolume_swap),1);
//	rb_define_method(rb_cOgrePlaneBoundedVolume,"hash",RUBY_METHOD_FUNC(OgrePlaneBoundedVolume_hash),0);
	rb_define_method(rb_cOgrePlaneBoundedVolume,"each",RUBY_METHOD_FUNC(OgrePlaneBoundedVolume_each),0);
	rb_include_module(rb_cOgrePlaneBoundedVolume,rb_mEnumerable);
	
	rb_define_method(rb_cOgrePlaneBoundedVolume,"push",RUBY_METHOD_FUNC(OgrePlaneBoundedVolume_push),1);
	rb_define_method(rb_cOgrePlaneBoundedVolume,"pop",RUBY_METHOD_FUNC(OgrePlaneBoundedVolume_pop),0);
//	rb_define_method(rb_cOgrePlaneBoundedVolume,"marshal_dump",RUBY_METHOD_FUNC(OgrePlaneBoundedVolume_marshal_dump),0);
//	rb_define_method(rb_cOgrePlaneBoundedVolume,"marshal_load",RUBY_METHOD_FUNC(OgrePlaneBoundedVolume_marshal_load),1);
}
