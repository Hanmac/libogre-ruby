#include "ogreresource.hpp"
#include "ogretexture.hpp"
#define _self wrap<Ogre::Texture*>(self)
VALUE rb_cOgreTexture;
/*:nodoc:
*/
VALUE OgreTexture_getHeight(VALUE self)
{
	return DBL2NUM(_self->getHeight());
}
/*:nodoc:
*/
VALUE OgreTexture_getWidth(VALUE self)
{
	return DBL2NUM(_self->getWidth());
}
/*:nodoc:
*/
VALUE OgreTexture_getDepth(VALUE self)
{
	return DBL2NUM(_self->getDepth());
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
	rb_define_attr(rb_cOgreTexture,"height",1,1);
	rb_define_attr(rb_cOgreTexture,"width",1,1);
	rb_define_attr(rb_cOgreTexture,"depth",1,1);
#endif
	rb_cOgreTexture = rb_define_class_under(rb_mOgre,"Texture",rb_cOgreResource);
	
}
