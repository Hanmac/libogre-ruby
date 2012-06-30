#include "ogreresource.hpp"
#include "ogrematerial.hpp"
#include "ogretechnique.hpp"

template <>
VALUE wrap< Ogre::MaterialPtr >(Ogre::MaterialPtr *material )
{
	return Data_Wrap_Struct(rb_cOgreMaterial, NULL, free, material);
}

template <>
Ogre::Material* wrap< Ogre::Material* >(const VALUE &vmaterial)
{
	return unwrapPtr<Ogre::MaterialPtr>(vmaterial, rb_cOgreMaterial)->get();
}

#define _self wrap<Ogre::Material*>(self)
#define _singleton Ogre::MaterialManager::getSingletonPtr()
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
	return wrap(_singleton->getActiveScheme());
}
/*
*/
VALUE _singleton_setActiveScheme(VALUE self,VALUE val)
{
	_singleton->setActiveScheme(wrap<Ogre::String>(val));
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

}
