#include "ogrequaternion.hpp"
#include "ogrerotationalspline.hpp"
#define _self wrap<Ogre::RotationalSpline*>(self)
VALUE rb_cOgreRotationalSpline;

template <>
VALUE wrap< Ogre::RotationalSpline >(Ogre::RotationalSpline *spline )
{
	return Data_Wrap_Struct(rb_cOgreRotationalSpline, NULL, free, spline);
}

namespace RubyOgre {
namespace RotationalSpline {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::RotationalSpline);
}
/*
*/
VALUE _addPoint(VALUE self,VALUE vector)
{
	_self->addPoint(wrap<Ogre::Quaternion>(vector));
	return self;
}
/*
*/
VALUE _size(VALUE self)
{
	return UINT2NUM(_self->getNumPoints());
}
/*
*/
VALUE _clear(VALUE self)
{
	_self->clear();
	return self;
}

/*
*/
VALUE _get(VALUE self,VALUE index)
{
	if(NUM2UINT(index) < _self->getNumPoints())
		return wrap(_self->getPoint(NUM2ULONG(index)));
	return Qnil;
}
/*
*/
VALUE _set(VALUE self,VALUE index,VALUE val)
{
	if(NUM2ULONG(index) < _self->getNumPoints())
		_self->updatePoint(NUM2UINT(index),wrap<Ogre::Quaternion>(val));
	return val;
}

/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for (unsigned int i = 0; i < _self->getNumPoints(); ++i)
	{
		rb_yield(wrap(_self->getPoint(i)));
	}
	return self;
}
/*
*/
VALUE _interpolate(int argc,VALUE* argv,VALUE self)
{
	VALUE t,index;
	rb_scan_args(argc, argv, "11",&t,&index);
	if(NIL_P(index))
		return wrap(_self->interpolate((Ogre::Real)NUM2DBL(t)));
	else if(NUM2UINT(index) < _self->getNumPoints())
		return wrap(_self->interpolate(NUM2DBL(index),(Ogre::Real)NUM2DBL(t)));
	else
		return Qnil;
}

}
}
/*
*/
void Init_OgreRotationalSpline(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	using namespace RubyOgre::RotationalSpline;

	rb_cOgreRotationalSpline = rb_define_class_under(rb_mOgre,"RotationalSpline",rb_cObject);
	rb_define_alloc_func(rb_cOgreRotationalSpline,_alloc);
	
	rb_define_method(rb_cOgreRotationalSpline,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cOgreRotationalSpline,rb_mEnumerable);
	
	rb_define_method(rb_cOgreRotationalSpline,"<<",RUBY_METHOD_FUNC(_addPoint),1);
	rb_define_method(rb_cOgreRotationalSpline,"size",RUBY_METHOD_FUNC(_size),0);
	
	rb_define_method(rb_cOgreRotationalSpline,"[]",RUBY_METHOD_FUNC(_get),1);
	rb_define_method(rb_cOgreRotationalSpline,"[]=",RUBY_METHOD_FUNC(_set),2);
	rb_define_method(rb_cOgreRotationalSpline,"clear",RUBY_METHOD_FUNC(_clear),0);
	rb_define_method(rb_cOgreRotationalSpline,"interpolate",RUBY_METHOD_FUNC(_interpolate),-1);

	registerklass<Ogre::RotationalSpline>(rb_cOgreRotationalSpline);
}
