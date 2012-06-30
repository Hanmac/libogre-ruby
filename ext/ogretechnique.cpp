#include "ogretechnique.hpp"
#include "ogrepass.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::Technique*>(self)
VALUE rb_cOgreTechnique;

namespace RubyOgre {
namespace Technique {

macro_attr(Name,Ogre::String)
macro_attr(SchemeName,Ogre::String)
macro_attr(LodIndex,unsigned short)

singlereturn(isSupported);
singlereturn(isTransparent);
singlereturn(isTransparentSortingEnabled);
singlereturn(isTransparentSortingForced);
singlereturn(isLoaded);

singlereturn(createPass);
/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::Pass*>(_self->getPassIterator());
	return self;
}

}}

void Init_OgreTechnique(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");

	rb_define_attr(rb_cOgreTechnique,"name",1,1);
	rb_define_attr(rb_cOgreTechnique,"schemename",1,1);
#endif
	using namespace RubyOgre::Technique;

	rb_cOgreTechnique = rb_define_class_under(rb_mOgre,"Technique",rb_cObject);
	rb_undef_alloc_func(rb_cOgreTechnique);
	
	rb_define_method(rb_cOgreTechnique,"create",RUBY_METHOD_FUNC(_createPass),0);
	
	rb_define_method(rb_cOgreTechnique,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cOgreTechnique,rb_mEnumerable);
	
	rb_define_attr_method(rb_cOgreTechnique,"name",_getName,_setName);
	rb_define_attr_method(rb_cOgreTechnique,"schemename",_getSchemeName,_setSchemeName);
	
	rb_define_method(rb_cOgreTechnique,"supported?",RUBY_METHOD_FUNC(_isSupported),0);
	rb_define_method(rb_cOgreTechnique,"transparent?",RUBY_METHOD_FUNC(_isTransparent),0);
	rb_define_method(rb_cOgreTechnique,"transparentSortingEnabled?",RUBY_METHOD_FUNC(_isTransparentSortingEnabled),0);
	rb_define_method(rb_cOgreTechnique,"transparentSortingForced?",RUBY_METHOD_FUNC(_isTransparentSortingForced),0);
	rb_define_method(rb_cOgreTechnique,"loaded?",RUBY_METHOD_FUNC(_isLoaded),0);

	registerklass<Ogre::Technique>(rb_cOgreTechnique);
}
