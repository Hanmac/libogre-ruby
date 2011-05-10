#include "ogrelight.hpp"
#include "ogrecolor.hpp"
#include "ogreradian.hpp"
#include "ogrevector3.hpp"
#include "ogremovableobject.hpp"
#define _self wrap<Ogre::Light*>(self)
VALUE rb_cOgreLight;

/*
*/
VALUE OgreLight_getDiffuseColor(VALUE self)
{
	return wrap(_self->getDiffuseColour());
}
/*
*/
VALUE OgreLight_setDiffuseColor(VALUE self,VALUE other)
{
	_self->setDiffuseColour(*wrap<Ogre::ColourValue*>(other));
	return other;
}
/*
*/
VALUE OgreLight_getSpecularColor(VALUE self)
{
	return wrap(_self->getSpecularColour());
}
/*
*/
VALUE OgreLight_setSpecularColor(VALUE self,VALUE other)
{
	_self->setSpecularColour(*wrap<Ogre::ColourValue*>(other));
	return other;
}
/*
*/
VALUE OgreLight_getPosition(VALUE self)
{
	return wrap(_self->getPosition());
}
/*
*/
VALUE OgreLight_setPosition(VALUE self,VALUE other)
{
	_self->setPosition(*wrap<Ogre::Vector3*>(other));
	return other;
}
/*
*/
VALUE OgreLight_getDirection(VALUE self)
{
	return wrap(_self->getPosition());
}
/*
*/
VALUE OgreLight_setDirection(VALUE self,VALUE other)
{
	_self->setDirection(*wrap<Ogre::Vector3*>(other));
	return other;
}

void Init_OgreLight(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreLight = rb_define_class_under(rb_mOgre,"Light",rb_cObject);
	rb_undef_alloc_func(rb_cOgreLight);
	rb_include_module(rb_cOgreLight,rb_mOgreMovableObject);
	
	rb_define_method(rb_cOgreLight,"diffuseColor",RUBY_METHOD_FUNC(OgreLight_getDiffuseColor),0);
	rb_define_method(rb_cOgreLight,"diffuseColor=",RUBY_METHOD_FUNC(OgreLight_setDiffuseColor),1);
	rb_define_method(rb_cOgreLight,"specularColor",RUBY_METHOD_FUNC(OgreLight_getSpecularColor),0);
	rb_define_method(rb_cOgreLight,"specularColor=",RUBY_METHOD_FUNC(OgreLight_setSpecularColor),1);

	rb_define_method(rb_cOgreLight,"position",RUBY_METHOD_FUNC(OgreLight_getPosition),0);
	rb_define_method(rb_cOgreLight,"position=",RUBY_METHOD_FUNC(OgreLight_setPosition),1);
	rb_define_method(rb_cOgreLight,"direction",RUBY_METHOD_FUNC(OgreLight_getDirection),0);
	rb_define_method(rb_cOgreLight,"direction=",RUBY_METHOD_FUNC(OgreLight_setDirection),1);
}
