#include "ogretextureunitstate.hpp"
#include "ogrecolor.hpp"
#include "ogreradian.hpp"
#include "ogrematrix4.hpp"
#include "ogrelayerblendmode.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::TextureUnitState*>(self)
VALUE rb_cOgreTextureUnitState;

namespace RubyOgre
{

namespace TextureUnitState
{

macro_attr(IsAlpha,bool)

macro_attr(CurrentFrame,unsigned int)
macro_attr(NumMipmaps,int)

macro_attr(TextureUScroll,double)
macro_attr(TextureVScroll,double)
macro_attr(TextureUScale,double)
macro_attr(TextureVScale,double)

macro_attr(TextureRotate,Ogre::Radian)

macro_attr(Name,Ogre::String)
macro_attr(TextureNameAlias,Ogre::String)

macro_attr(BindingType,Ogre::TextureUnitState::BindingType)
macro_attr(ContentType,Ogre::TextureUnitState::ContentType)

macro_attr(DesiredFormat,Ogre::PixelFormat)

//macro_attr(TextureType,Ogre::TextureType)

macro_attr(TextureBorderColour,Ogre::ColourValue)

macro_attr(TextureCoordSet,unsigned int)

macro_attr(TextureTransform,Ogre::Matrix4)

macro_attr(TextureAnisotropy,unsigned int)
macro_attr(TextureMipmapBias,float)

/*
 *
 */
VALUE _getFrameTextureName(VALUE self, VALUE frame)
{
	if(_self->getNumFrames() <= NUM2UINT(frame))
		return wrap(_self->getFrameTextureName(NUM2UINT(frame)));
	return Qnil;
}
/*
 *
 */
VALUE _setFrameTextureName(VALUE self,VALUE frame,VALUE name)
{
	if(_self->getNumFrames() <= NUM2UINT(frame))
		_self->setFrameTextureName(wrap<Ogre::String>(name),NUM2UINT(frame));
	return self;
}


VALUE _getColorBlendMode(VALUE self)
{
	return wrap(_self->getColourBlendMode());
}

VALUE _setColorBlendMode(VALUE self,VALUE val)
{
	Ogre::LayerBlendModeEx* cval = wrap< Ogre::LayerBlendModeEx* >(val);
	_self->setColourOperationEx(cval->operation,
		cval->source1,cval->source2,
		cval->colourArg1,cval->colourArg2,
		cval->factor);
	return val;
}


VALUE _getAlphaBlendMode(VALUE self)
{
	return wrap(_self->getAlphaBlendMode());
}

VALUE _setAlphaBlendMode(VALUE self,VALUE val)
{
	Ogre::LayerBlendModeEx* cval = wrap< Ogre::LayerBlendModeEx* >(val);
	_self->setAlphaOperation(cval->operation,
		cval->source1,cval->source2,
		cval->alphaArg1,cval->alphaArg2,
		cval->factor);
	return val;
}


}}

void Init_OgreTextureUnitState(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_define_attr(rb_cOgreTextureUnitState,"name",1,1);

	rb_define_attr(rb_cOgreTextureUnitState,"name_alias",1,1);
	
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
	using namespace RubyOgre::TextureUnitState;

	rb_cOgreTextureUnitState = rb_define_class_under(rb_mOgre,"TextureUnitState",rb_cObject);
	rb_undef_alloc_func(rb_cOgreTextureUnitState);

	rb_define_attr_method(rb_cOgreTextureUnitState,"name",_getName,_setName);
	rb_define_attr_method(rb_cOgreTextureUnitState,"name_alias",_getTextureNameAlias,_setTextureNameAlias);


	rb_define_attr_method(rb_cOgreTextureUnitState,"alpha",_getIsAlpha,_setIsAlpha);
	rb_define_attr_method(rb_cOgreTextureUnitState,"currentFrame",_getCurrentFrame,_setCurrentFrame);

	
	rb_define_attr_method(rb_cOgreTextureUnitState,"textureUScroll",_getTextureUScroll,_setTextureUScroll);
	rb_define_attr_method(rb_cOgreTextureUnitState,"textureVScroll",_getTextureVScroll,_setTextureVScroll);

	rb_define_attr_method(rb_cOgreTextureUnitState,"textureUScale",_getTextureUScale,_setTextureUScale);
	rb_define_attr_method(rb_cOgreTextureUnitState,"textureVScale",_getTextureVScale,_setTextureVScale);

	rb_define_attr_method(rb_cOgreTextureUnitState,"textureRotate",_getTextureRotate,_setTextureRotate);

	rb_define_attr_method(rb_cOgreTextureUnitState,"colorBlendMode",_getColorBlendMode,_setColorBlendMode);
	rb_define_attr_method(rb_cOgreTextureUnitState,"alphaBlendMode",_getAlphaBlendMode,_setAlphaBlendMode);

	rb_define_method(rb_cOgreTextureUnitState,"[]",RUBY_METHOD_FUNC(_getFrameTextureName),1);
	rb_define_method(rb_cOgreTextureUnitState,"[]=",RUBY_METHOD_FUNC(_setFrameTextureName),2);

	registerklass<Ogre::TextureUnitState>(rb_cOgreTextureUnitState);
}
