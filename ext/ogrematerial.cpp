#include "ogreresource.hpp"
#include "ogrematerial.hpp"
#include "ogretechnique.hpp"
#define _self wrap<Ogre::Material*>(self)
#define _singleton Ogre::MaterialManager::getSingletonPtr()
VALUE rb_cOgreMaterial;
/*
*/
VALUE OgreMaterial_count(VALUE self)
{
	return UINT2NUM(_self->getNumTechniques());
}
/*
*/
VALUE OgreMaterial_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::Technique*>(_self->getTechniqueIterator());
	return self;
}
/*
*/
VALUE OgreMaterial_singleton_getActiveScheme(VALUE self)
{
	return wrap(_singleton->getActiveScheme());
}
/*
*/
VALUE OgreMaterial_singleton_setActiveScheme(VALUE self,VALUE val)
{
	_singleton->setActiveScheme(rb_string_value_cstr(&val));
	return val;
}

void Init_OgreMaterial(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);
#endif
	rb_cOgreMaterial = rb_define_class_under(rb_mOgre,"Material",rb_cOgreResource);
	rb_define_method(rb_cOgreMaterial,"count",RUBY_METHOD_FUNC(OgreMaterial_count),0);
	rb_define_method(rb_cOgreMaterial,"each",RUBY_METHOD_FUNC(OgreMaterial_each),0);
	rb_include_module(rb_cOgreMaterial,rb_mEnumerable);
	
	rb_define_singleton_method(rb_cOgreMaterial,"activeScheme",RUBY_METHOD_FUNC(OgreMaterial_singleton_getActiveScheme),0);
	rb_define_singleton_method(rb_cOgreMaterial,"activeScheme=",RUBY_METHOD_FUNC(OgreMaterial_singleton_setActiveScheme),1);

}
