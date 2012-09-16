/*
 * ogrecompositorinstance.cpp
 *
 *  Created on: 29.08.2012
 *      Author: hanmac
 */

#include "ogreexception.hpp"
#include "ogrecompositor.hpp"
#include "ogrecompositiontechnique.hpp"
#include "ogrecompositorinstance.hpp"

#define _self wrap<Ogre::CompositorInstance*>(self)

VALUE rb_cOgreCompositorInstance;

namespace RubyOgre {
namespace CompositorInstance {

macro_attr(Enabled,bool)
macro_attr(Alive,bool)
macro_attr(Scheme,Ogre::String)


singlereturn(getCompositor)
singlereturn(getTechnique)
singlereturn(getChain)

VALUE _enable(VALUE self)
{
	_self->setEnabled(true);
	return self;
}

VALUE _disable(VALUE self)
{
	_self->setEnabled(false);
	return self;
}

VALUE _next(int argc,VALUE *argv,VALUE self)
{
	VALUE active;
	rb_scan_args(argc, argv, "01",&active);

	if(NIL_P(active))
		active = Qtrue;

	return wrap(_self->getChain()->getNextInstance(_self,RTEST(active)));
}

VALUE _prev(int argc,VALUE *argv,VALUE self)
{
	VALUE active;
	rb_scan_args(argc, argv, "01",&active);

	if(NIL_P(active))
		active = Qtrue;

	return wrap(_self->getChain()->getPreviousInstance(_self,RTEST(active)));
}


}}

void Init_OgreCompositorInstance(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreCompositor = rb_define_class_under(rb_mOgre,"Compositor",rb_cOgreResource);


#endif
	using namespace RubyOgre::CompositorInstance;

	rb_cOgreCompositorInstance = rb_define_class_under(rb_cOgreCompositor,"Instance",rb_cObject);
	rb_undef_alloc_func(rb_cOgreCompositorInstance);

	rb_define_attr_method(rb_cOgreCompositorInstance,"enabled",_getEnabled,_setEnabled);
	rb_define_attr_method(rb_cOgreCompositorInstance,"alive",_getAlive,_setAlive);
	rb_define_attr_method(rb_cOgreCompositorInstance,"scheme",_getScheme,_setScheme);

	rb_define_method(rb_cOgreCompositorInstance,"compositor",RUBY_METHOD_FUNC(_getCompositor),0);
	rb_define_method(rb_cOgreCompositorInstance,"technique",RUBY_METHOD_FUNC(_getTechnique),0);
	rb_define_method(rb_cOgreCompositorInstance,"chain",RUBY_METHOD_FUNC(_getChain),0);

	rb_define_method(rb_cOgreCompositorInstance,"enable",RUBY_METHOD_FUNC(_enable),0);
	rb_define_method(rb_cOgreCompositorInstance,"disable",RUBY_METHOD_FUNC(_disable),0);

	rb_define_method(rb_cOgreCompositorInstance,"next",RUBY_METHOD_FUNC(_next),-1);
	rb_define_method(rb_cOgreCompositorInstance,"prev",RUBY_METHOD_FUNC(_prev),-1);


	registerklass<Ogre::CompositorInstance>(rb_cOgreCompositorInstance);
}

