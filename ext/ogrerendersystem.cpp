#include "ogrerendersystem.hpp"
#include "ogrerendertarget.hpp"

#define _self wrap<Ogre::RenderSystem*>(self)
VALUE rb_cOgreRenderSystem;

/*
*/
VALUE OgreRenderSystem_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::String,Ogre::RenderTarget*>(_self->getRenderTargetIterator());
	return self;
}

/*
*/
VALUE OgreRenderSystem_getName(VALUE self)
{
	return wrap(_self->getName());
}

/*
*/
VALUE OgreRenderSystem_attach(VALUE self,VALUE render)
{
	_self->attachRenderTarget(*wrap<Ogre::RenderTarget*>(render));
	return self;
}

/*
*/
VALUE OgreRenderSystem_get(VALUE self,VALUE render)
{
	return wrap(_self->getRenderTarget(rb_string_value_cstr(&render)));
}



/*
*/
VALUE OgreRenderSystem_detach(VALUE self,VALUE render)
{
	_self->detachRenderTarget(rb_string_value_cstr(&render));
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
VALUE OgreRenderSystem_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=OgreRenderSystem_getName(self);
	return rb_f_sprintf(3,array);
}


/*
*/
VALUE OgreRenderSystem_getRenderSystemEvents(VALUE self)
{
	return wrap<Ogre::String>(_self->getRenderSystemEvents());
}

/*
*/
VALUE OgreRenderSystem_preExtraThreadsStarted(VALUE self)
{
	_self->preExtraThreadsStarted();
	return self;
}
/*
*/
VALUE OgreRenderSystem_postExtraThreadsStarted(VALUE self)
{
	_self->postExtraThreadsStarted();
	return self;
}
/*
*/
VALUE OgreRenderSystem_registerThread(VALUE self)
{
	_self->registerThread();
	return self;
}
/*
*/
VALUE OgreRenderSystem_unregisterThread(VALUE self)
{
	_self->unregisterThread();
	return self;
}

/*
*/
VALUE OgreRenderSystem_getDisplayMonitorCount(VALUE self)
{
	return UINT2NUM(_self->getDisplayMonitorCount());
}


/*
*/
VALUE OgreRenderSystem_beginFrame(VALUE self)
{
	_self->_beginFrame();
	return self;
}
/*
*/
VALUE OgreRenderSystem_endFrame(VALUE self)
{
	_self->_endFrame();
	return self;
}


VALUE OgreRenderSystem_getViewport(VALUE self)
{
	return wrap(_self->_getViewport());
}
VALUE OgreRenderSystem_setViewport(VALUE self,VALUE val)
{
	_self->_setViewport(wrap<Ogre::Viewport*>(val));
	return val;
}

void Init_OgreRenderSystem(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	rb_define_attr(rb_cOgreRenderSystem,"_viewport",1,1);
#endif
	rb_cOgreRenderSystem = rb_define_class_under(rb_mOgre,"RenderSystem",rb_cObject);
	rb_undef_alloc_func(rb_cOgreRenderSystem);

	rb_define_method(rb_cOgreRenderSystem,"name",RUBY_METHOD_FUNC(OgreRenderSystem_getName),0);
	rb_define_method(rb_cOgreRenderSystem,"inspect",RUBY_METHOD_FUNC(OgreRenderSystem_inspect),0);
		
	rb_define_method(rb_cOgreRenderSystem,"attach",RUBY_METHOD_FUNC(OgreRenderSystem_attach),1);
	rb_define_method(rb_cOgreRenderSystem,"detach",RUBY_METHOD_FUNC(OgreRenderSystem_detach),1);
	
	rb_define_method(rb_cOgreRenderSystem,"[]",RUBY_METHOD_FUNC(OgreRenderSystem_get),1);
	
	rb_define_method(rb_cOgreRenderSystem,"each",RUBY_METHOD_FUNC(OgreRenderSystem_each),0);
	rb_include_module(rb_cOgreRenderSystem,rb_mEnumerable);

	rb_define_method(rb_cOgreRenderSystem,"renderSystemEvents",RUBY_METHOD_FUNC(OgreRenderSystem_getRenderSystemEvents),0);
	rb_define_method(rb_cOgreRenderSystem,"preExtraThreadsStarted",RUBY_METHOD_FUNC(OgreRenderSystem_preExtraThreadsStarted),0);
	rb_define_method(rb_cOgreRenderSystem,"postExtraThreadsStarted",RUBY_METHOD_FUNC(OgreRenderSystem_postExtraThreadsStarted),0);

	rb_define_method(rb_cOgreRenderSystem,"registerThread",RUBY_METHOD_FUNC(OgreRenderSystem_registerThread),0);
	rb_define_method(rb_cOgreRenderSystem,"unregisterThread",RUBY_METHOD_FUNC(OgreRenderSystem_unregisterThread),0);

	rb_define_method(rb_cOgreRenderSystem,"displayMonitorCount",RUBY_METHOD_FUNC(OgreRenderSystem_getDisplayMonitorCount),0);


	rb_define_method(rb_cOgreRenderSystem,"_beginFrame",RUBY_METHOD_FUNC(OgreRenderSystem_beginFrame),0);
	rb_define_method(rb_cOgreRenderSystem,"_endFrame",RUBY_METHOD_FUNC(OgreRenderSystem_endFrame),0);

	rb_define_attr_method(rb_cOgreRenderSystem,"_viewport",OgreRenderSystem_getViewport,OgreRenderSystem_setViewport);
}
