#include "ogrepass.hpp"
#include "ogrecolor.hpp"
#include "ogretextureunitstate.hpp"
#define _self wrap<Ogre::Pass*>(self)
VALUE rb_cOgrePass;

macro_attr(Pass,Name,Ogre::String)

macro_attr(Pass,Ambient,Ogre::ColourValue)
macro_attr(Pass,Diffuse,Ogre::ColourValue)
macro_attr(Pass,Specular,Ogre::ColourValue)
macro_attr(Pass,SelfIllumination,Ogre::ColourValue)

/*
*/
VALUE OgrePass_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::TextureUnitState*>( _self->getTextureUnitStateIterator());
	return self;
}

/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE OgrePass_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=OgrePass_getName(self);
	return rb_f_sprintf(3,array);
}


void Init_OgrePass(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");

	rb_define_attr(rb_cOgrePass,"name",1,1);
	rb_define_attr(rb_cOgrePass,"index",1,0);

	rb_define_attr(rb_cOgrePass,"pointsize",1,1);
	rb_define_attr(rb_cOgrePass,"pointminsize",1,1);
	rb_define_attr(rb_cOgrePass,"pointmaxsize",1,1);
	
	rb_define_attr(rb_cOgrePass,"ambient",1,1);
	rb_define_attr(rb_cOgrePass,"diffuse",1,1);
	rb_define_attr(rb_cOgrePass,"specular",1,1);
	rb_define_attr(rb_cOgrePass,"selfIllumination",1,1);
	
	rb_define_attr(rb_cOgrePass,"shininess",1,1);
#endif
	rb_cOgrePass = rb_define_class_under(rb_mOgre,"Pass",rb_cObject);
	rb_undef_alloc_func(rb_cOgrePass);
	rb_define_attr_method(rb_cOgrePass,"name",OgrePass_getName,OgrePass_setName);

	rb_define_attr_method(rb_cOgrePass,"ambient",OgrePass_getAmbient,OgrePass_setAmbient);
	rb_define_attr_method(rb_cOgrePass,"diffuse",OgrePass_getDiffuse,OgrePass_setDiffuse);
	rb_define_attr_method(rb_cOgrePass,"specular",OgrePass_getSpecular,OgrePass_setSpecular);
	rb_define_attr_method(rb_cOgrePass,"selfIllumination",OgrePass_getSelfIllumination,OgrePass_setSelfIllumination);
	
	rb_define_method(rb_cOgrePass,"each",RUBY_METHOD_FUNC(OgrePass_each),0);
	rb_include_module(rb_cOgrePass,rb_mEnumerable);
	
	rb_define_method(rb_cOgrePass,"inspect",RUBY_METHOD_FUNC(OgrePass_inspect),0);
}
