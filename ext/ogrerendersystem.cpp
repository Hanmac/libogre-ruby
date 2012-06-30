#include "ogrerendersystem.hpp"
#include "ogrerendertarget.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::RenderSystem*>(self)
VALUE rb_cOgreRenderSystem;

namespace RubyOgre {
namespace RenderSystem {

macro_attr(WBufferEnabled,bool)

singlereturn(getName)

singlefunc(preExtraThreadsStarted)
singlefunc(postExtraThreadsStarted)
singlefunc(registerThread)
singlefunc(unregisterThread)


singlefunc(_beginFrame)
singlefunc(_endFrame)
/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::String,Ogre::RenderTarget*>(_self->getRenderTargetIterator());
	return self;
}

/*
*/
VALUE _attach(VALUE self,VALUE render)
{
	_self->attachRenderTarget(*wrap<Ogre::RenderTarget*>(render));
	return self;
}

/*
*/
VALUE _get(VALUE self,VALUE render)
{
	return wrap(_self->getRenderTarget(wrap<Ogre::String>(render)));
}



/*
*/
VALUE _detach(VALUE self,VALUE render)
{
	return wrap(_self->detachRenderTarget(wrap<Ogre::String>(render)));
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
VALUE _getRenderSystemEvents(VALUE self)
{
	return wrap<Ogre::String>(_self->getRenderSystemEvents());
}

/*
*/
VALUE _getDisplayMonitorCount(VALUE self)
{
	return UINT2NUM(_self->getDisplayMonitorCount());
}

VALUE _getViewport(VALUE self)
{
	return wrap(_self->_getViewport());
}
VALUE _setViewport(VALUE self,VALUE val)
{
	_self->_setViewport(wrap<Ogre::Viewport*>(val));
	return val;
}

}}

void Init_OgreRenderSystem(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	rb_define_attr(rb_cOgreRenderSystem,"_viewport",1,1);
#endif
	using namespace RubyOgre::RenderSystem;

	rb_cOgreRenderSystem = rb_define_class_under(rb_mOgre,"RenderSystem",rb_cObject);
	rb_undef_alloc_func(rb_cOgreRenderSystem);

	rb_define_method(rb_cOgreRenderSystem,"name",RUBY_METHOD_FUNC(_getName),0);
	rb_define_method(rb_cOgreRenderSystem,"inspect",RUBY_METHOD_FUNC(_inspect),0);
		
	rb_define_method(rb_cOgreRenderSystem,"attach",RUBY_METHOD_FUNC(_attach),1);
	rb_define_method(rb_cOgreRenderSystem,"detach",RUBY_METHOD_FUNC(_detach),1);
	
	rb_define_method(rb_cOgreRenderSystem,"[]",RUBY_METHOD_FUNC(_get),1);
	
	rb_define_method(rb_cOgreRenderSystem,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cOgreRenderSystem,rb_mEnumerable);

	rb_define_method(rb_cOgreRenderSystem,"renderSystemEvents",RUBY_METHOD_FUNC(_getRenderSystemEvents),0);
	rb_define_method(rb_cOgreRenderSystem,"preExtraThreadsStarted",RUBY_METHOD_FUNC(_preExtraThreadsStarted),0);
	rb_define_method(rb_cOgreRenderSystem,"postExtraThreadsStarted",RUBY_METHOD_FUNC(_postExtraThreadsStarted),0);

	rb_define_method(rb_cOgreRenderSystem,"registerThread",RUBY_METHOD_FUNC(_registerThread),0);
	rb_define_method(rb_cOgreRenderSystem,"unregisterThread",RUBY_METHOD_FUNC(_unregisterThread),0);

	rb_define_method(rb_cOgreRenderSystem,"displayMonitorCount",RUBY_METHOD_FUNC(_getDisplayMonitorCount),0);


	rb_define_method(rb_cOgreRenderSystem,"_beginFrame",RUBY_METHOD_FUNC(__beginFrame),0);
	rb_define_method(rb_cOgreRenderSystem,"_endFrame",RUBY_METHOD_FUNC(__endFrame),0);

	rb_define_attr_method(rb_cOgreRenderSystem,"_viewport",_getViewport,_setViewport);
}
