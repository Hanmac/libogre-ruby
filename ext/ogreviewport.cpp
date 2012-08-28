#include "ogreviewport.hpp"
#include "ogreviewportlistener.hpp"
#include "ogreexception.hpp"
#include "ogrerendertarget.hpp"
#include "ogrecamera.hpp"
#include "ogrecolor.hpp"

#define _self wrap<Ogre::Viewport*>(self)
VALUE rb_cOgreViewport;
namespace RubyOgre {
namespace Viewport {

singlereturn(getTarget)

macro_attr(BackgroundColour,Ogre::ColourValue)
macro_attr(MaterialScheme,Ogre::String)
macro_attr(Camera,Ogre::Camera*)

macro_attr(VisibilityMask,uint)

macro_attr(OverlaysEnabled,bool)
macro_attr(ShadowsEnabled,bool)
macro_attr(SkiesEnabled,bool)

singlereturn(getLeft)
singlereturn(getTop)
singlereturn(getWidth)
singlereturn(getHeight)

singlereturn(getActualLeft)
singlereturn(getActualTop)
singlereturn(getActualWidth)
singlereturn(getActualHeight)


singlefunc(update)

//
VALUE _setLeft(VALUE self,VALUE val)
{
	_self->setDimensions(NUM2DBL(val),_self->getTop(),_self->getWidth(),_self->getHeight());
	return val;
}
VALUE _setTop(VALUE self,VALUE val)
{
	_self->setDimensions(_self->getLeft(),NUM2DBL(val),_self->getWidth(),_self->getHeight());
	return val;
}
VALUE _setWidth(VALUE self,VALUE val)
{
	_self->setDimensions(_self->getLeft(),_self->getTop(),NUM2DBL(val),_self->getHeight());
	return val;
}
VALUE _setHeight(VALUE self,VALUE val)
{
	_self->setDimensions(_self->getLeft(),_self->getTop(),_self->getWidth(),NUM2DBL(val));
	return val;
}

VALUE _addListener(VALUE self,VALUE obj)
{
	_self->addListener(wrap<Ogre::Viewport::Listener*>(obj));
	return self;
}


VALUE _compositorchain(VALUE self)
{
	return wrap(Ogre::CompositorManager::getSingletonPtr()->getCompositorChain(_self));
}

}
}

void Init_OgreViewport(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	rb_define_attr(rb_cOgreViewport,"background_color",1,1);
	rb_define_attr(rb_cOgreViewport,"scheme_name",1,1);
	rb_define_attr(rb_cOgreViewport,"camera",1,1);
	
	rb_define_attr(rb_cOgreViewport,"visibility_mask",1,1);

	rb_define_attr(rb_cOgreViewport,"overlays_enabled",1,1);
	rb_define_attr(rb_cOgreViewport,"shadows_enabled",1,1);
	rb_define_attr(rb_cOgreViewport,"skies_enabled",1,1);
	
	rb_define_attr(rb_cOgreViewport,"left",1,1);
	rb_define_attr(rb_cOgreViewport,"top",1,1);
	rb_define_attr(rb_cOgreViewport,"wight",1,1);
	rb_define_attr(rb_cOgreViewport,"height",1,1);
#endif
	using namespace RubyOgre::Viewport;

	rb_cOgreViewport = rb_define_class_under(rb_mOgre,"Viewport",rb_cObject);
	rb_undef_alloc_func(rb_cOgreViewport);

	rb_define_method(rb_cOgreViewport,"target",RUBY_METHOD_FUNC(_getTarget),0);
	rb_define_method(rb_cOgreViewport,"update",RUBY_METHOD_FUNC(_update),0);
	
	rb_define_attr_method(rb_cOgreViewport,"background_color",_getBackgroundColour,_setBackgroundColour);
	rb_define_attr_method(rb_cOgreViewport,"scheme_name",_getMaterialScheme,_setMaterialScheme);
	rb_define_attr_method(rb_cOgreViewport,"camera",_getCamera,_setCamera);


	rb_define_attr_method(rb_cOgreViewport,"visibility_mask",_getVisibilityMask,_setVisibilityMask);
	
	rb_define_attr_method(rb_cOgreViewport,"overlays_enabled",_getOverlaysEnabled,_setOverlaysEnabled);
	rb_define_attr_method(rb_cOgreViewport,"shadows_enabled",_getShadowsEnabled,_setShadowsEnabled);
	rb_define_attr_method(rb_cOgreViewport,"skies_enabled",_getSkiesEnabled,_setSkiesEnabled);
	
	rb_define_attr_method(rb_cOgreViewport,"left",_getLeft,_setLeft);
	rb_define_attr_method(rb_cOgreViewport,"top",_getTop,_setTop);
	rb_define_attr_method(rb_cOgreViewport,"width",_getWidth,_setWidth);
	rb_define_attr_method(rb_cOgreViewport,"height",_getHeight,_setHeight);

	rb_define_method(rb_cOgreViewport,"compositor_chain",RUBY_METHOD_FUNC(_compositorchain),0);


	rb_define_method(rb_cOgreViewport,"actual_left",RUBY_METHOD_FUNC(_getActualLeft),0);
	rb_define_method(rb_cOgreViewport,"actual_top",RUBY_METHOD_FUNC(_getActualTop),0);
	rb_define_method(rb_cOgreViewport,"actual_width",RUBY_METHOD_FUNC(_getActualWidth),0);
	rb_define_method(rb_cOgreViewport,"actual_height",RUBY_METHOD_FUNC(_getActualHeight),0);

	rb_define_method(rb_cOgreViewport,"add_listener",RUBY_METHOD_FUNC(_addListener),1);

	registerklass<Ogre::Viewport>(rb_cOgreViewport);
}
