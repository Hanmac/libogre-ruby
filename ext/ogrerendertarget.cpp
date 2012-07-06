#include "ogrerendertarget.hpp"
#include "ogreviewport.hpp"
#include "ogrecamera.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::RenderTarget*>(self)
VALUE rb_cOgreRenderTarget;

namespace RubyOgre {
namespace RenderTarget {

macro_attr(Priority,Ogre::uchar)
macro_attr_bool(Active)
macro_attr_bool(AutoUpdated)

singlereturn(getName)
singlereturn(isPrimary)

singlereturn(getLastFPS)
singlereturn(getAverageFPS)
singlereturn(getBestFPS)
singlereturn(getWorstFPS)
singlereturn(getBestFrameTime)
singlereturn(getWorstFrameTime)

/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for (unsigned int i = 0; i < _self->getNumViewports(); ++i)
		rb_yield(wrap(_self->getViewport(i)));
	return self;
}

/*
*/
VALUE _addViewport(int argc,VALUE *argv,VALUE self)
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

VALUE _removeViewport(VALUE self,VALUE ZOrder)
{
	if(NIL_P(ZOrder))
		_self->removeAllViewports();
	else
		_self->removeViewport(NUM2INT(ZOrder));

	return self;
}
/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=_getName(self);
	return rb_f_sprintf(3,array);
}


/*
*/
VALUE _getWidth(VALUE self)
{
	return UINT2NUM(_self->getWidth());
}
/*
*/
VALUE _getHeight(VALUE self)
{
	return UINT2NUM(_self->getHeight());
}
/*
*/
VALUE _getColorDepth(VALUE self)
{
	return UINT2NUM(_self->getColourDepth());
}

}}
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
	using namespace RubyOgre::RenderTarget;

	rb_cOgreRenderTarget = rb_define_class_under(rb_mOgre,"RenderTarget",rb_cObject);
	rb_undef_alloc_func(rb_cOgreRenderTarget);

	rb_define_method(rb_cOgreRenderTarget,"name",RUBY_METHOD_FUNC(_getName),0);
	rb_define_method(rb_cOgreRenderTarget,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	
	rb_define_method(rb_cOgreRenderTarget,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cOgreRenderTarget,rb_mEnumerable);

	rb_define_method(rb_cOgreRenderTarget,"addViewport",RUBY_METHOD_FUNC(_addViewport),-1);
	rb_define_method(rb_cOgreRenderTarget,"removeViewport",RUBY_METHOD_FUNC(_removeViewport),1);

	rb_define_method(rb_cOgreRenderTarget,"primary?",RUBY_METHOD_FUNC(_isPrimary),0);

	rb_define_method(rb_cOgreRenderTarget,"width",RUBY_METHOD_FUNC(_getWidth),0);
	rb_define_method(rb_cOgreRenderTarget,"height",RUBY_METHOD_FUNC(_getHeight),0);
	rb_define_method(rb_cOgreRenderTarget,"colordepth",RUBY_METHOD_FUNC(_getColorDepth),0);


	rb_define_method(rb_cOgreRenderTarget,"lastFPS",RUBY_METHOD_FUNC(_getLastFPS),0);
	rb_define_method(rb_cOgreRenderTarget,"averageFPS",RUBY_METHOD_FUNC(_getAverageFPS),0);
	rb_define_method(rb_cOgreRenderTarget,"bestFPS",RUBY_METHOD_FUNC(_getBestFPS),0);
	rb_define_method(rb_cOgreRenderTarget,"worstFPS",RUBY_METHOD_FUNC(_getWorstFPS),0);

	rb_define_method(rb_cOgreRenderTarget,"bestFrameTime",RUBY_METHOD_FUNC(_getBestFrameTime),0);
	rb_define_method(rb_cOgreRenderTarget,"worstFrameTime",RUBY_METHOD_FUNC(_getWorstFrameTime),0);

	rb_define_attr_method(rb_cOgreRenderTarget,"active",_getActive,_setActive);
	rb_define_attr_method(rb_cOgreRenderTarget,"autoUpdated",_getAutoUpdated,_setAutoUpdated);
	rb_define_attr_method(rb_cOgreRenderTarget,"priority",_getPriority,_setPriority);

	registerklass<Ogre::RenderTarget>(rb_cOgreRenderTarget);
}
