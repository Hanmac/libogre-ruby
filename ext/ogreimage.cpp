#include "ogreimage.hpp"
#include "ogreexception.hpp"
#include "ogrecolor.hpp"
#include "ogredatastream.hpp"
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
	VALUE path,groupname;
	rb_scan_args(argc, argv, "11",&path,&groupname);
	Ogre::String result;
	try {
		if(rb_obj_is_kind_of(path,rb_cOgreDataStream)){
			if(NIL_P(groupname))
				result = Ogre::StringUtil::BLANK;
			else
				result = rb_string_value_cstr(&groupname);
				Ogre::DataStreamPtr stream = wrap<Ogre::DataStreamPtr>(path);
			_self->load(stream, result);
		}else{
			if(NIL_P(groupname))
				result = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
			else
				result = rb_string_value_cstr(&groupname);
			_self->load(rb_string_value_cstr(&path),result);
		}
	} catch (Ogre::Exception& e){
		rb_raise(wrap(e));
	}
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
VALUE OgreImage_get(VALUE self,VALUE x,VALUE y,VALUE z)
{
	if(_self->getFormat()==Ogre::PF_UNKNOWN)
		return Qnil;
	if((_self->getWidth() <= NUM2UINT(x)) || (_self->getHeight() <= NUM2UINT(y)) || (_self->getDepth() <= NUM2UINT(z)))
		return Qnil;
	return wrap(_self->getColourAt(NUM2INT(x),NUM2INT(y),NUM2INT(z)));
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
/*
*/
VALUE OgreImage_each(VALUE self)
{
	if(_self->getFormat()!=Ogre::PF_UNKNOWN)
		for (unsigned int x = 0; x < _self->getWidth(); ++x)
			for (unsigned int y = 0; y < _self->getHeight(); ++y)
				for (unsigned int z = 0; z < _self->getDepth(); ++z)
					rb_yield_values(4,UINT2NUM(x),UINT2NUM(y),UINT2NUM(z),wrap(_self->getColourAt(x,y,z)));
	return self;
}
/*
*/
VALUE OgreImage_encode(VALUE self,VALUE formatextension)
{
	return wrap(_self->encode(rb_string_value_cstr(&formatextension)));
}
/*
*/
VALUE OgreImage_save(VALUE self,VALUE filename)
{
	_self->save(rb_string_value_cstr(&filename));
	return self;
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
	rb_define_method(rb_cOgreImage,"[]",RUBY_METHOD_FUNC(OgreImage_get),3);
	rb_define_method(rb_cOgreImage,"alpha?",RUBY_METHOD_FUNC(OgreImage_hasAlpha),0);
	rb_define_method(rb_cOgreImage,"flipAroundY",RUBY_METHOD_FUNC(OgreImage_flipAroundY),0);
	rb_define_method(rb_cOgreImage,"flipAroundX",RUBY_METHOD_FUNC(OgreImage_flipAroundX),0);
	
	rb_define_method(rb_cOgreImage,"encode",RUBY_METHOD_FUNC(OgreImage_encode),1);
	rb_define_method(rb_cOgreImage,"save",RUBY_METHOD_FUNC(OgreImage_save),1);
	
	rb_define_method(rb_cOgreImage,"each",RUBY_METHOD_FUNC(OgreImage_each),0);

	rb_include_module(rb_cOgreImage,rb_mEnumerable);
}
