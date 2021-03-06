#include "ogreresource.hpp"
#include "ogreexception.hpp"
#include "ogrecompositor.hpp"
#include "ogrerendertarget.hpp"
#define _self wrap<Ogre::CompositorPtr>(self)
#define _manager Ogre::CompositorManager::getSingletonPtr()
VALUE rb_cOgreCompositor;

template <>
VALUE wrap< Ogre::CompositorPtr >(const Ogre::CompositorPtr &compositor )
{
	if(compositor.isNull())
		return Qnil;
	return Data_Wrap_Struct(rb_cOgreCompositor, NULL, free,new Ogre::CompositorPtr(compositor));
}

template <>
Ogre::CompositorPtr wrap< Ogre::CompositorPtr >(const VALUE &vcompositor)
{
	if(rb_obj_is_kind_of(vcompositor,rb_cString))
	{
		Ogre::CompositorPtr ptr(_manager->getByName(wrap<Ogre::String>(vcompositor)));
		if(ptr.isNull())
			rb_raise(rb_eTypeError,"\"%s\" is not a %s",rb_string_value_cstr((volatile VALUE*)(&vcompositor)),rb_class2name(rb_cOgreCompositor));
		return ptr;
	}
	return *unwrapPtr<Ogre::CompositorPtr>(vcompositor, rb_cOgreCompositor);
}


namespace RubyOgre {
namespace Compositor {

singlereturn(createTechnique)

/*
*/
VALUE _getTechnique(VALUE self,VALUE id)
{
	return wrap(_self->getTechnique(NUM2UINT(id)));
}


/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::CompositionTechnique*>(_self->getTechniqueIterator());
	return self;
}


/*
*/
VALUE _each_supported(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::CompositionTechnique*>(_self->getSupportedTechniqueIterator());
	return self;
}

/*
*/
VALUE _texturename(VALUE self,VALUE name,VALUE index)
{
	return wrap(_self->getTextureInstanceName(wrap<Ogre::String>(name),NUM2UINT(index)));
}
/*
*/
VALUE _texture(VALUE self,VALUE name,VALUE index)
{
	return wrap(_self->getTextureInstance(wrap<Ogre::String>(name),NUM2UINT(index)));
}
/*
*/
VALUE _getRenderTarget(VALUE self,VALUE val)
{
	return wrap(_self->getRenderTarget(wrap<Ogre::String>(val)));
}

}
}

void Init_OgreCompositor(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);
#endif
	using namespace RubyOgre::Compositor;

	rb_cOgreCompositor = rb_define_class_under(rb_mOgre,"Compositor",rb_cOgreResource);

	rb_define_method(rb_cOgreCompositor,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cOgreCompositor,rb_mEnumerable);
	
	rb_define_method(rb_cOgreCompositor,"each_supported",RUBY_METHOD_FUNC(_each_supported),0);
	
	rb_define_method(rb_cOgreCompositor,"create_technique",RUBY_METHOD_FUNC(_createTechnique),0);
	rb_define_method(rb_cOgreCompositor,"[]",RUBY_METHOD_FUNC(_getTechnique),1);

	rb_define_method(rb_cOgreCompositor,"render_target",RUBY_METHOD_FUNC(_getRenderTarget),1);
	
	rb_define_method(rb_cOgreCompositor,"texture",RUBY_METHOD_FUNC(_texture),2);
	rb_define_method(rb_cOgreCompositor,"texturename",RUBY_METHOD_FUNC(_texturename),2);
}
