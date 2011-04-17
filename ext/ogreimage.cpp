#include "ogreimage.hpp"
#include "ogreexception.hpp"
#include "ogrecolor.hpp"
#define _self wrap<Ogre::Image*>(self)
VALUE rb_cOgreImage;


VALUE OgreImage_alloc(VALUE self)
{
	Ogre::Image *temp = new Ogre::Image;
	return wrap(temp);
}
/*


*/
VALUE OgreImage_initialize(int argc,VALUE* argv,VALUE self)
{

	return self;
}
/*


*/
VALUE OgreImage_size(VALUE self)
{
	return INT2NUM(_self->getSize());
}
/*


*/
VALUE OgreImage_width(VALUE self)
{
	return INT2NUM(_self->getWidth());
}
/*


*/
VALUE OgreImage_height(VALUE self)
{
	return INT2NUM(_self->getHeight());
}
/*


*/
VALUE OgreImage_depth(VALUE self)
{
	return INT2NUM(_self->getDepth());
}
/*


*/
VALUE OgreImage_load(int argc,VALUE *argv,VALUE self)
{
	VALUE path,groupname;
	rb_scan_args(argc, argv, "11",&path,&groupname);
	Ogre::String result;
	if(NIL_P(groupname))
		result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	else
		result = rb_string_value_cstr(&groupname);
	try {
	_self->load(rb_string_value_cstr(&path),result);
	} catch (Ogre::FileNotFoundException& e){
		errno = e.getNumber();
		rb_sys_fail(e.getDescription().c_str());
	}
	return self;
}
/*


*/
VALUE OgreImage_get(VALUE self,VALUE x,VALUE y,VALUE z)
{
	if(_self->getFormat()==Ogre::PF_UNKNOWN)
		return Qnil;
	if((_self->getWidth() <= NUM2UINT(x)) || (_self->getHeight() <= NUM2UINT(y)) || (_self->getDepth() <= NUM2UINT(z)))
		return Qnil;
	Ogre::ColourValue temp = _self->getColourAt(NUM2INT(x),NUM2INT(y),NUM2INT(z));
	
	return wrap(temp);
}
/*


*/
VALUE OgreImage_flipAroundY(VALUE self)
{
	_self->flipAroundY();
	return self;
}
/*


*/
VALUE OgreImage_flipAroundX(VALUE self)
{
	_self->flipAroundY();
	return self;
}
/*


*/
VALUE OgreImage_hasAlpha(VALUE self)
{
	return _self->getHasAlpha() ? Qtrue : Qfalse;
}
void Init_OgreImage(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreImage = rb_define_class_under(rb_mOgre,"Image",rb_cObject);
	rb_define_alloc_func(rb_cOgreImage,OgreImage_alloc);
	rb_define_method(rb_cOgreImage,"initialize",RUBY_METHOD_FUNC(OgreImage_initialize),-1);
	rb_define_method(rb_cOgreImage,"size",RUBY_METHOD_FUNC(OgreImage_size),0);
	rb_define_method(rb_cOgreImage,"width",RUBY_METHOD_FUNC(OgreImage_width),0);
	rb_define_method(rb_cOgreImage,"height",RUBY_METHOD_FUNC(OgreImage_height),0);
	rb_define_method(rb_cOgreImage,"depth",RUBY_METHOD_FUNC(OgreImage_depth),0);
	rb_define_method(rb_cOgreImage,"load",RUBY_METHOD_FUNC(OgreImage_load),1);
	rb_define_method(rb_cOgreImage,"[]",RUBY_METHOD_FUNC(OgreImage_get),3);
	rb_define_method(rb_cOgreImage,"alpha?",RUBY_METHOD_FUNC(OgreImage_hasAlpha),0);
	rb_define_method(rb_cOgreImage,"flipAroundY",RUBY_METHOD_FUNC(OgreImage_flipAroundY),0);
	rb_define_method(rb_cOgreImage,"flipAroundX",RUBY_METHOD_FUNC(OgreImage_flipAroundX),0);
}
