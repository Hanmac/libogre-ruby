#include "ogreresource.hpp"
#include "ogrefont.hpp"
#define _self wrap<Ogre::Font*>(self)
VALUE rb_cOgreFont;

/*:nodoc:
*/
VALUE OgreFont_getSource(VALUE self)
{
	return wrap(_self->getSource());
}
/*:nodoc:
*/
VALUE OgreFont_setSource(VALUE self,VALUE val)
{
	_self->setSource(rb_string_value_cstr(&val));
	return val;
}

/*
setSource (const String &source)
 	Sets the source of the font.
const String & 	getSource (void) const 

void 	setTrueTypeSize (Real ttfSize)
 	Sets the size of a truetype font (only required for FT_TRUETYPE).
void 	setTrueTypeResolution (uint ttfResolution)
 	Gets the resolution (dpi) of the font used to generate the texture (only required for FT_TRUETYPE).
Real 	getTrueTypeSize (void) const
 	Gets the point size of the font used to generate the texture.
uint 	getTrueTypeResolution (void) const

void 	setAntialiasColour (bool enabled)
 	Sets whether or not the colour of this font is antialiased as it is generated from a true type font.
bool 	getAntialiasColour (void) const 
*/
void Init_OgreFont(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);
	rb_define_attr(rb_cOgreFont,"source",1,1);
	rb_define_attr(rb_cOgreFont,"trueTypeSize",1,1);
	rb_define_attr(rb_cOgreFont,"antialiasColour",1,1);
#endif
	rb_cOgreFont = rb_define_class_under(rb_mOgre,"Font",rb_cOgreResource);
	rb_define_method(rb_cOgreFont,"source",RUBY_METHOD_FUNC(OgreFont_getSource),0);
	rb_define_method(rb_cOgreFont,"source=",RUBY_METHOD_FUNC(OgreFont_setSource),1);
}
