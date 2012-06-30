#include "ogreresource.hpp"
#include "ogretexture.hpp"

#include "ogreexception.hpp"


template <>
VALUE wrap< Ogre::TexturePtr >(Ogre::TexturePtr *texture )
{
	return Data_Wrap_Struct(rb_cOgreTexture, NULL, free, texture);
}

template <>
Ogre::Texture* wrap< Ogre::Texture* >(const VALUE &vtexture)
{
	return unwrapPtr<Ogre::TexturePtr>(vtexture, rb_cOgreTexture)->get();
}


#define _self wrap<Ogre::Texture*>(self)
VALUE rb_cOgreTexture;

macro_attr_enum(TextureType,Ogre::TextureType)

macro_attr(Gamma,float)

macro_attr(Height,size_t)
macro_attr(Width,size_t)
macro_attr(Depth,size_t)
macro_attr(NumMipmaps,size_t)

macro_attr(Usage,int)

macro_attr_bool(HardwareGammaEnabled)

macro_attr_enum(Format,Ogre::PixelFormat)

macro_attr(DesiredIntegerBitDepth,ushort)
macro_attr(DesiredFloatBitDepth,ushort)

macro_attr(TreatLuminanceAsAlpha,bool)


singlefunc(createInternalResources)
singlefunc(freeInternalResources)


VALUE _getSrcHeight(VALUE self)
{
	return ULONG2NUM(_self->getSrcHeight());
}
VALUE _getSrcWidth(VALUE self)
{
	return ULONG2NUM(_self->getSrcWidth());
}
VALUE _getSrcDepth(VALUE self)
{
	return ULONG2NUM(_self->getSrcDepth());
}


/*
virtual size_t 	getHeight (void) const
 	Returns the height of the texture.
virtual size_t 	getWidth (void) const
 	Returns the width of the texture.
virtual size_t 	getDepth (void) const
 	Returns the depth of the texture (only applicable for 3D textures).
virtual size_t 	getSrcHeight (void) const
 	Returns the height of the original input texture (may differ due to hardware requirements).
virtual size_t 	getSrcWidth (void) const
 	Returns the width of the original input texture (may differ due to hardware requirements).
virtual size_t 	getSrcDepth (void) const
 	Returns the original depth of the input texture (only applicable for 3D textures).
virtual void 	setHeight (size_t h)
 	Set the height of the texture; can only do this before load();.
virtual void 	setWidth (size_t w)
 	Set the width of the texture; can only do this before load();.
virtual void 	setDepth (size_t d)
 	Set the depth of the texture (only applicable for 3D textures); ; can only do this before load();.
virtual int 	getUsage () const
 	Returns the TextureUsage indentifier for this Texture.
virtual void 	setUsage (int u)
*/
void Init_OgreTexture(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);

	rb_define_attr(rb_cOgreTexture,"gamma",1,1);

	rb_define_attr(rb_cOgreTexture,"height",1,1);
	rb_define_attr(rb_cOgreTexture,"width",1,1);
	rb_define_attr(rb_cOgreTexture,"depth",1,1);
	
	rb_define_attr(rb_cOgreTexture,"usage",1,1);
#endif
	rb_cOgreTexture = rb_define_class_under(rb_mOgre,"Texture",rb_cOgreResource);

	rb_define_attr_method(rb_cOgreTexture,"gamma",_getGamma,_setGamma);

	rb_define_attr_method(rb_cOgreTexture,"height",_getHeight,_setHeight);
	rb_define_attr_method(rb_cOgreTexture,"width",_getWidth,_setWidth);
	rb_define_attr_method(rb_cOgreTexture,"depth",_getDepth,_setDepth);
	rb_define_attr_method(rb_cOgreTexture,"usage",_getUsage,_setUsage);

	rb_define_method(rb_cOgreTexture,"src_height",RUBY_METHOD_FUNC(_getSrcHeight),0);
	rb_define_method(rb_cOgreTexture,"src_width",RUBY_METHOD_FUNC(_getSrcWidth),0);
	rb_define_method(rb_cOgreTexture,"src_depth",RUBY_METHOD_FUNC(_getSrcDepth),0);


	registerklass<Ogre::Texture>(rb_cOgreTexture);
}
