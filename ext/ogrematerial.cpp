#include "ogreresource.hpp"
#include "ogreexception.hpp"
#include "ogrematerial.hpp"
#include "ogretechnique.hpp"

#define _self wrap<Ogre::MaterialPtr>(self)
#define _manager Ogre::MaterialManager::getSingletonPtr()

template <>
VALUE wrap< Ogre::MaterialPtr >(Ogre::MaterialPtr *material )
{
	return Data_Wrap_Struct(rb_cOgreMaterial, NULL, free, material);
}

template <>
Ogre::MaterialPtr wrap< Ogre::MaterialPtr >(const VALUE &vmaterial)
{
	if(rb_obj_is_kind_of(vmaterial,rb_cString))
		return _manager->getByName(wrap<Ogre::String>(vmaterial));

	return *unwrapPtr<Ogre::MaterialPtr>(vmaterial, rb_cOgreMaterial);
}

VALUE rb_cOgreMaterial;

namespace RubyOgre
{
namespace Material
{

singlereturn(createTechnique)

/*
*/
VALUE _size(VALUE self)
{
	return UINT2NUM(_self->getNumTechniques());
}
/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::Technique*>(_self->getTechniqueIterator());
	return self;
}
/*
*/
VALUE _singleton_getActiveScheme(VALUE self)
{
	return wrap(_manager->getActiveScheme());
}
/*
*/
VALUE _singleton_setActiveScheme(VALUE self,VALUE val)
{
	_manager->setActiveScheme(wrap<Ogre::String>(val));
	return val;
}

}
}

void Init_OgreMaterial(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);
#endif
	using namespace RubyOgre::Material;
	rb_cOgreMaterial = rb_define_class_under(rb_mOgre,"Material",rb_cOgreResource);
	rb_define_method(rb_cOgreMaterial,"size",RUBY_METHOD_FUNC(_size),0);

	rb_define_method(rb_cOgreMaterial,"create",RUBY_METHOD_FUNC(_createTechnique),0);
	rb_define_method(rb_cOgreMaterial,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cOgreMaterial,rb_mEnumerable);
	
	rb_define_singleton_method(rb_cOgreMaterial,"activeScheme",RUBY_METHOD_FUNC(_singleton_getActiveScheme),0);
	rb_define_singleton_method(rb_cOgreMaterial,"activeScheme=",RUBY_METHOD_FUNC(_singleton_setActiveScheme),1);

	registerklass<Ogre::MaterialPtr>(rb_cOgreMaterial);
}
