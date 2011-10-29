#include "ogrerendertarget.hpp"
#include "ogreviewport.hpp"
#include "ogrecamera.hpp"
#define _self wrap<Ogre::RenderTarget*>(self)
VALUE rb_cOgreRenderTarget;

macro_attr_with_func(RenderTarget,Priority,UINT2NUM,NUM2UINT)
/*
*/
VALUE OgreRenderTarget_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for (unsigned int i = 0; i < _self->getNumViewports(); ++i)
		rb_yield(wrap(_self->getViewport(i)));
	return self;
}

/*
*/
VALUE OgreRenderTarget_getName(VALUE self)
{
	return wrap(_self->getName());
}
/*
*/
VALUE OgreRenderTarget_addViewport(int argc,VALUE *argv,VALUE self)
{
	VALUE cam,ZOrder,left,top,width,height;
	rb_scan_args(argc, argv, "15",&cam,&ZOrder,&left,&top,&width,&height);
	if(NIL_P(ZOrder))
		ZOrder = INT2NUM(0);
	if(NIL_P(left))
		left = DBL2NUM(0.0f);
	if(NIL_P(top))
		top = DBL2NUM(0.0f);
	if(NIL_P(width))
		width = DBL2NUM(1.0f);
	if(NIL_P(height))
		height = DBL2NUM(1.0f);
	
return wrap(_self->addViewport(wrap<Ogre::Camera*>(cam), NUM2INT(ZOrder), NUM2DBL(left),NUM2DBL(top),NUM2DBL(width),NUM2DBL(height)));
}
/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE OgreRenderTarget_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=OgreRenderTarget_getName(self);
	return rb_f_sprintf(3,array);
}

VALUE OgreRenderTarget_getActive(VALUE self)
{
	return _self->isActive() ? Qtrue : Qfalse;
}
VALUE OgreRenderTarget_setActive(VALUE self,VALUE val)
{
	_self->setActive(RTEST(val));
	return val;
}
VALUE OgreRenderTarget_getAutoUpdated(VALUE self)
{
	return _self->isAutoUpdated() ? Qtrue : Qfalse;
}
VALUE OgreRenderTarget_setAutoUpdated(VALUE self,VALUE val)
{
	_self->setAutoUpdated(RTEST(val));
	return val;
}
/*
*/
VALUE OgreRenderTarget_getWidth(VALUE self)
{
	return UINT2NUM(_self->getWidth());
}
/*
*/
VALUE OgreRenderTarget_getHeight(VALUE self)
{
	return UINT2NUM(_self->getHeight());
}
/*
*/
VALUE OgreRenderTarget_getColorDepth(VALUE self)
{
	return UINT2NUM(_self->getColourDepth());
}

/*
*/
VALUE OgreRenderTarget_getLastFPS(VALUE self)
{
	return DBL2NUM(_self->getLastFPS());
}
/*
*/
VALUE OgreRenderTarget_getAverageFPS(VALUE self)
{
return DBL2NUM(_self->getAverageFPS());
}
/*
*/
VALUE OgreRenderTarget_getBestFPS(VALUE self)
{
return DBL2NUM(_self->getBestFPS());
}
/*
*/
VALUE OgreRenderTarget_getWorstFPS(VALUE self)
{
return DBL2NUM(_self->getWorstFPS());
}
/*
*/
VALUE OgreRenderTarget_getBestFrameTime(VALUE self)
{
return DBL2NUM(_self->getBestFrameTime());
}
/*
*/
VALUE OgreRenderTarget_getWorstFrameTime(VALUE self)
{
return DBL2NUM(_self->getWorstFrameTime());
}

/*
*/
void Init_OgreRenderTarget(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	rb_define_attr(rb_cOgreRenderTarget,"active",1,1);
	rb_define_attr(rb_cOgreRenderTarget,"autoUpdated",1,1);
	rb_define_attr(rb_cOgreRenderTarget,"priority",1,1);
#endif
	rb_cOgreRenderTarget = rb_define_class_under(rb_mOgre,"RenderTarget",rb_cObject);
	rb_undef_alloc_func(rb_cOgreRenderTarget);

	rb_define_method(rb_cOgreRenderTarget,"name",RUBY_METHOD_FUNC(OgreRenderTarget_getName),0);
	rb_define_method(rb_cOgreRenderTarget,"inspect",RUBY_METHOD_FUNC(OgreRenderTarget_inspect),0);
	
	rb_define_method(rb_cOgreRenderTarget,"each",RUBY_METHOD_FUNC(OgreRenderTarget_each),0);
	rb_include_module(rb_cOgreRenderTarget,rb_mEnumerable);

	rb_define_method(rb_cOgreRenderTarget,"addViewport",RUBY_METHOD_FUNC(OgreRenderTarget_addViewport),-1);

	rb_define_method(rb_cOgreRenderTarget,"width",RUBY_METHOD_FUNC(OgreRenderTarget_getWidth),0);
	rb_define_method(rb_cOgreRenderTarget,"height",RUBY_METHOD_FUNC(OgreRenderTarget_getHeight),0);
	rb_define_method(rb_cOgreRenderTarget,"colordepth",RUBY_METHOD_FUNC(OgreRenderTarget_getColorDepth),0);

	rb_define_attr_method(rb_cOgreRenderTarget,"active",OgreRenderTarget_getActive,OgreRenderTarget_setActive);
	rb_define_attr_method(rb_cOgreRenderTarget,"autoUpdated",OgreRenderTarget_getAutoUpdated,OgreRenderTarget_setAutoUpdated);
	rb_define_attr_method(rb_cOgreRenderTarget,"priority",OgreRenderTarget_getPriority,OgreRenderTarget_setPriority);
}
