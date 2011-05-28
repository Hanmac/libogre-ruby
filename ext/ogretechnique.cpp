#include "ogretechnique.hpp"
#include "ogrepass.hpp"
#define _self wrap<Ogre::Technique*>(self)
VALUE rb_cOgreTechnique;

/*:nodoc:
*/
VALUE OgreTechnique_getName(VALUE self)
{
	return wrap(_self->getName());
}
/*:nodoc:
*/
VALUE OgreTechnique_setName(VALUE self,VALUE val)
{
	_self->setName(rb_string_value_cstr(&val));
	return val;
}
/*:nodoc:
*/
VALUE OgreTechnique_getSchemeName(VALUE self)
{
	return wrap(_self->getSchemeName());
}
/*:nodoc:
*/
VALUE OgreTechnique_setSchemeName(VALUE self,VALUE val)
{
	_self->setSchemeName(rb_string_value_cstr(&val));
	return val;
}
/*
*/
VALUE OgreTechnique_isSupported(VALUE self)
{
	return _self->isSupported() ? Qtrue : Qfalse;
}
/*
*/
VALUE OgreTechnique_isTransparent(VALUE self)
{
	return _self->isTransparent() ? Qtrue : Qfalse;
}
/*
*/
VALUE OgreTechnique_isTransparentSortingEnabled(VALUE self)
{
	return _self->isTransparentSortingEnabled() ? Qtrue : Qfalse;
}
/*
*/
VALUE OgreTechnique_isTransparentSortingForced(VALUE self)
{
	return _self->isTransparentSortingForced() ? Qtrue : Qfalse;
}
/*
*/
VALUE OgreTechnique_isLoaded(VALUE self)
{
	return _self->isLoaded() ? Qtrue : Qfalse;
}


/*
*/
VALUE OgreTechnique_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	Ogre::Technique::PassIterator pit = _self->getPassIterator();
	for (Ogre::Technique::PassIterator::iterator it = pit.begin(); it != pit.end(); ++it)
		rb_yield(wrap(*it));
	return self;
}
/*
bool 	isTransparent (void) const
 	Returns true if this Technique involves transparency.
bool 	isTransparentSortingEnabled (void) const
 	Returns true if this Technique has transparent sorting enabled.
bool 	isTransparentSortingForced (void) const 
*/
void Init_OgreTechnique(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");

	rb_define_attr(rb_cOgreTechnique,"name",1,1);
	rb_define_attr(rb_cOgreTechnique,"schemename",1,1);
#endif
	rb_cOgreTechnique = rb_define_class_under(rb_mOgre,"Technique",rb_cObject);
	rb_undef_alloc_func(rb_cOgreTechnique);
	
	
	rb_define_method(rb_cOgreTechnique,"each",RUBY_METHOD_FUNC(OgreTechnique_each),0);
	rb_include_module(rb_cOgreTechnique,rb_mEnumerable);
	
	rb_define_method(rb_cOgreTechnique,"name",RUBY_METHOD_FUNC(OgreTechnique_getName),0);	
	rb_define_method(rb_cOgreTechnique,"name=",RUBY_METHOD_FUNC(OgreTechnique_setName),1);
	rb_define_method(rb_cOgreTechnique,"schemename",RUBY_METHOD_FUNC(OgreTechnique_getSchemeName),0);	
	rb_define_method(rb_cOgreTechnique,"schemename=",RUBY_METHOD_FUNC(OgreTechnique_setSchemeName),1);
	
	rb_define_method(rb_cOgreTechnique,"supported?",RUBY_METHOD_FUNC(OgreTechnique_isSupported),0);	
	rb_define_method(rb_cOgreTechnique,"transparent?",RUBY_METHOD_FUNC(OgreTechnique_isTransparent),0);
	rb_define_method(rb_cOgreTechnique,"transparentSortingEnabled?",RUBY_METHOD_FUNC(OgreTechnique_isTransparentSortingEnabled),0);
	rb_define_method(rb_cOgreTechnique,"transparentSortingForced?",RUBY_METHOD_FUNC(OgreTechnique_isTransparentSortingForced),0);
	rb_define_method(rb_cOgreTechnique,"loaded?",RUBY_METHOD_FUNC(OgreTechnique_isLoaded),0);
}
