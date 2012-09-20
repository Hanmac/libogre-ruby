/*
 * ogrecompositorchain.cpp
 *
 *  Created on: 06.07.2012
 *      Author: hanmac
 */

#include "ogreexception.hpp"
#include "ogrecompositor.hpp"
#include "ogrecompositorchain.hpp"

#define _self wrap<Ogre::CompositorChain*>(self)

VALUE rb_cOgreCompositorChain;

namespace RubyOgre {
namespace CompositorChain {

singlereturn(getViewport)
singlereturn(getNumCompositors)

singlefunc(removeAllCompositors)

/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::CompositorInstance*>(_self->getCompositors());
	return self;
}

VALUE _push(int argc,VALUE *argv,VALUE self)
{
	VALUE compositor, scheme;
	rb_scan_args(argc, argv, "11",&compositor, &scheme);
	RUBYTRY(
		return wrap(_self->addCompositor(
			wrap<Ogre::CompositorPtr>(compositor),
			Ogre::CompositorChain::LAST,
			wrap<Ogre::String>(scheme))
		);
	)
	return Qnil;
}

VALUE _insert(int argc,VALUE *argv,VALUE self)
{
	VALUE index,compositor, scheme;
	rb_scan_args(argc, argv, "21",&index,&compositor, &scheme);
	RUBYTRY(
		return wrap(_self->addCompositor(
			wrap<Ogre::CompositorPtr>(compositor),
			NUM2INT(index),
			wrap<Ogre::String>(scheme))
		);
	)
	return Qnil;
}


VALUE _add_shift(VALUE self,VALUE obj)
{
	RUBYTRY(_self->addCompositor(wrap<Ogre::CompositorPtr>(obj));)
	return self;
}

VALUE _getCompositor(VALUE self,VALUE idx)
{
	if(rb_obj_is_kind_of(idx,rb_cString))
		return wrap(_self->getCompositor(wrap<Ogre::String>(idx)));
	else{
		int tmp = NUM2INT(idx);

		if(tmp >= (int)_self->getNumCompositors())
			return Qnil;
		if(tmp >= 0)
			return wrap(_self->getCompositor(NUM2UINT(idx)));
		tmp = _self->getNumCompositors() - tmp;
		if(tmp >= 0)
			return wrap(_self->getCompositor(NUM2UINT(idx)));
		return Qnil;

	}
}

VALUE _getEnable(VALUE self)
{
	size_t enabled=0;
	size_t count = _self->getNumCompositors();
	if (count == 0)
		return Qnil;

	for(size_t i = 0;i < count;++i)
		if(_self->getCompositor(i)->getEnabled())
			++enabled;

	if(enabled == count)
		return Qtrue;

	if(enabled == 0)
		return Qfalse;

	VALUE result = rb_ary_new();

	for(size_t i = 0;i < count;++i)
		rb_ary_push(result,wrap(_self->getCompositor(i)->getEnabled()));

	return result;
}

VALUE _setEnable(VALUE self,VALUE val)
{
	size_t count = _self->getNumCompositors();
	for(size_t i = 0;i < count;++i)
		_self->setCompositorEnabled(i,RTEST(val));
	return self;
}

VALUE _delete(VALUE self,VALUE id)
{
	_self->_removeInstance(_self->getCompositor(wrap<Ogre::String>(id)));
	return self;
}

VALUE _delete_at(VALUE self,VALUE idx)
{
	_self->removeCompositor(NUM2INT(idx));
	return self;
}
/*
*/
VALUE _delete_if(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);

	for(Ogre::CompositorChain::InstanceIterator it = _self->getCompositors();
		it.hasMoreElements();
		)
	{
		Ogre::CompositorInstance *ci = it.getNext();
		if(RTEST(rb_yield(wrap(ci))))
			_self->_removeInstance(ci);
	}
	return self;
}

}}

void Init_OgreCompositorChain(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreCompositor = rb_define_class_under(rb_mOgre,"Compositor",rb_cOgreResource);
#endif
	using namespace RubyOgre::CompositorChain;

	rb_cOgreCompositorChain = rb_define_class_under(rb_cOgreCompositor,"Chain",rb_cObject);
	rb_undef_alloc_func(rb_cOgreCompositorChain);

	rb_define_method(rb_cOgreCompositorChain,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cOgreCompositorChain,rb_mEnumerable);

	rb_define_method(rb_cOgreCompositorChain,"size",RUBY_METHOD_FUNC(_getNumCompositors),0);
	rb_define_method(rb_cOgreCompositorChain,"clear",RUBY_METHOD_FUNC(_removeAllCompositors),0);

	rb_define_method(rb_cOgreCompositorChain,"push",RUBY_METHOD_FUNC(_push),-1);
	rb_define_method(rb_cOgreCompositorChain,"insert",RUBY_METHOD_FUNC(_insert),-1);

	rb_define_method(rb_cOgreCompositorChain,"<<",RUBY_METHOD_FUNC(_add_shift),1);
	rb_define_method(rb_cOgreCompositorChain,"[]",RUBY_METHOD_FUNC(_getCompositor),1);

	rb_define_method(rb_cOgreCompositorChain,"delete",RUBY_METHOD_FUNC(_delete),1);
	rb_define_method(rb_cOgreCompositorChain,"delete_at",RUBY_METHOD_FUNC(_delete_at),1);
	rb_define_method(rb_cOgreCompositorChain,"delete_if",RUBY_METHOD_FUNC(_delete_if),0);

	rb_define_method(rb_cOgreCompositorChain,"viewport",RUBY_METHOD_FUNC(_getViewport),0);

	registerklass<Ogre::CompositorChain>(rb_cOgreCompositorChain);
}
