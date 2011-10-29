#include "ogretextureunitstate.hpp"
#include "ogrecolor.hpp"
#include "ogreradian.hpp"
#include "ogrelayerblendmode.hpp"
#define _self wrap<Ogre::TextureUnitState*>(self)
VALUE rb_cOgreTextureUnitState;

macro_attr_with_func(TextureUnitState,IsAlpha,RBOOL,RTEST)

macro_attr_with_func(TextureUnitState,CurrentFrame,DBL2NUM,NUM2DBL)

macro_attr_with_func(TextureUnitState,TextureUScroll,DBL2NUM,NUM2DBL)
macro_attr_with_func(TextureUnitState,TextureVScroll,DBL2NUM,NUM2DBL)
macro_attr_with_func(TextureUnitState,TextureUScale,DBL2NUM,NUM2DBL)
macro_attr_with_func(TextureUnitState,TextureVScale,DBL2NUM,NUM2DBL)

macro_attr(TextureUnitState,TextureRotate,Ogre::Radian)

VALUE OgreTextureUnitState_getColorBlendMode(VALUE self)
{
	return wrap(_self->getColourBlendMode());
}
VALUE OgreTextureUnitState_getAlphaBlendMode(VALUE self)
{
	return wrap(_self->getAlphaBlendMode());
}

void Init_OgreTextureUnitState(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_define_attr(rb_cOgreTextureUnitState,"textureName",1,1);
	
	rb_define_attr(rb_cOgreTextureUnitState,"currentFrame",1,1);
	
	rb_define_attr(rb_cOgreTextureUnitState,"textureBorderColor",1,1);
	rb_define_attr(rb_cOgreTextureUnitState,"alpha",1,1);
	rb_define_attr(rb_cOgreTextureUnitState,"textureUScroll",1,1);
	rb_define_attr(rb_cOgreTextureUnitState,"textureVScroll",1,1);
	rb_define_attr(rb_cOgreTextureUnitState,"textureUScale",1,1);
	rb_define_attr(rb_cOgreTextureUnitState,"textureVScale",1,1);
	rb_define_attr(rb_cOgreTextureUnitState,"textureRotate",1,1);
	
	rb_define_attr(rb_cOgreTextureUnitState,"colorBlendMode",1,1);
	rb_define_attr(rb_cOgreTextureUnitState,"alphaBlendMode",1,1);
#endif
	rb_cOgreTextureUnitState = rb_define_class_under(rb_mOgre,"TextureUnitState",rb_cObject);
	rb_undef_alloc_func(rb_cOgreTextureUnitState);

	rb_define_attr_method(rb_cOgreTextureUnitState,"alpha",OgreTextureUnitState_getIsAlpha,OgreTextureUnitState_setIsAlpha);
	rb_define_attr_method(rb_cOgreTextureUnitState,"currentFrame",OgreTextureUnitState_getCurrentFrame,OgreTextureUnitState_setCurrentFrame);

	
	rb_define_attr_method(rb_cOgreTextureUnitState,"textureUScroll",OgreTextureUnitState_getTextureUScroll,OgreTextureUnitState_setTextureUScroll);
	rb_define_attr_method(rb_cOgreTextureUnitState,"textureVScroll",OgreTextureUnitState_getTextureVScroll,OgreTextureUnitState_setTextureVScroll);

	rb_define_attr_method(rb_cOgreTextureUnitState,"textureUScale",OgreTextureUnitState_getTextureUScale,OgreTextureUnitState_setTextureUScale);
	rb_define_attr_method(rb_cOgreTextureUnitState,"textureVScale",OgreTextureUnitState_getTextureVScale,OgreTextureUnitState_setTextureVScale);


	rb_define_attr_method(rb_cOgreTextureUnitState,"textureRotate",OgreTextureUnitState_getTextureRotate,OgreTextureUnitState_setTextureRotate);

	rb_define_method(rb_cOgreTextureUnitState,"colorBlendMode",RUBY_METHOD_FUNC(OgreTextureUnitState_getColorBlendMode),0);
	rb_define_method(rb_cOgreTextureUnitState,"alphaBlendMode",RUBY_METHOD_FUNC(OgreTextureUnitState_getAlphaBlendMode),0);
}
