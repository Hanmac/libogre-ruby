#include "ogretexturedefinition.hpp"
#include "ogrecompositiontechnique.hpp"

#include "ogreexception.hpp"

#define _self wrap<Ogre::CompositionTechnique::TextureDefinition*>(self)
VALUE rb_cOgreTextureDefinition;
namespace RubyOgre {
namespace TextureDefinition {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::CompositionTechnique::TextureDefinition);
}
macro_attr_prop(name,Ogre::String)
macro_attr_prop(refCompName,Ogre::String)
macro_attr_prop(refTexName,Ogre::String)

macro_attr_prop(width,size_t)
macro_attr_prop(height,size_t)

macro_attr_prop(widthFactor,double)
macro_attr_prop(heightFactor,double)

}}

void Init_OgreTextureDefinition(VALUE rb_mOgre)
{
	#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreCompositionTechnique = rb_define_class_under(rb_mOgre,"CompositionTechnique",rb_cObject);
	
	rb_define_attr(rb_cOgreTextureDefinition,"name",1,1);
	rb_define_attr(rb_cOgreTextureDefinition,"refCompName",1,1);
	rb_define_attr(rb_cOgreTextureDefinition,"refTexName",1,1);

	rb_define_attr(rb_cOgreTextureDefinition,"width",1,1);
	rb_define_attr(rb_cOgreTextureDefinition,"height",1,1);

	rb_define_attr(rb_cOgreTextureDefinition,"width_factor",1,1);
	rb_define_attr(rb_cOgreTextureDefinition,"height_factor",1,1);

	#endif
	using namespace RubyOgre::TextureDefinition;
	rb_cOgreTextureDefinition = rb_define_class_under(rb_mOgre,"TextureDefinition",rb_cOgreCompositionTechnique);
	rb_define_alloc_func(rb_cOgreTextureDefinition,_alloc);

	rb_define_attr_method(rb_cOgreTextureDefinition,"name",_get_name,_set_name);
	rb_define_attr_method(rb_cOgreTextureDefinition,"refCompName",_get_refCompName,_set_refCompName);
	rb_define_attr_method(rb_cOgreTextureDefinition,"refTexName",_get_refTexName,_set_refTexName);

	rb_define_attr_method(rb_cOgreTextureDefinition,"width",_get_width,_set_width);
	rb_define_attr_method(rb_cOgreTextureDefinition,"height",_get_height,_set_height);
	rb_define_attr_method(rb_cOgreTextureDefinition,"width_factor",_get_widthFactor,_set_widthFactor);
	rb_define_attr_method(rb_cOgreTextureDefinition,"height_factor",_get_heightFactor,_set_heightFactor);

	registerklass<Ogre::CompositionTechnique::TextureDefinition>(rb_cOgreTextureDefinition);
}
