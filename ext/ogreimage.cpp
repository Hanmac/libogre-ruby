#include "ogreimage.hpp"
#include "ogreresource.hpp"
#include "ogreexception.hpp"
#include "ogrecolor.hpp"
#include "ogredatastream.hpp"
#define _self wrap<Ogre::Image*>(self)
VALUE rb_cOgreImage;

void freeimage(Ogre::Image *image )
{
	image->freeMemory();
}
template <>
VALUE wrap< Ogre::Image >(Ogre::Image *image )
{
	return Data_Wrap_Struct(rb_cOgreImage, NULL, freeimage, image);
}


namespace RubyOgre {
namespace Image {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::Image);
}
/*
*/
VALUE _initialize(int argc,VALUE* argv,VALUE self)
{
	VALUE path,groupname;
	rb_scan_args(argc, argv, "11",&path,&groupname);
	Ogre::String result;
	RUBYTRY(
		if(rb_obj_is_kind_of(path,rb_cOgreDataStream)){
			Ogre::DataStreamPtr stream = wrap<Ogre::DataStreamPtr>(path);
			_self->load(stream, unwrapResourceGroup(groupname,Ogre::StringUtil::BLANK));
		}else{
			_self->load(wrap<Ogre::String>(path),
					unwrapResourceGroup(groupname,
						Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME)
					);
		}
	)
	return self;
}
/*
 * call-seq:
 *   size -> Integer
 * 
 * Returns the size of the data buffer.
*/
VALUE _size(VALUE self)
{
	return INT2NUM(_self->getSize());
}
/*
 * call-seq:
 *   width -> Integer
 * 
 * Gets the width of the image in pixels.
*/
VALUE _width(VALUE self)
{
	return INT2NUM(_self->getWidth());
}
/*
 * call-seq:
 *   height -> Integer
 * 
 * Gets the height of the image in pixels.
*/
VALUE _height(VALUE self)
{
	return INT2NUM(_self->getHeight());
}
/*
 * call-seq:
 *   depth -> Integer
 * 
 * Gets the depth of the image.
*/
VALUE _depth(VALUE self)
{
	return INT2NUM(_self->getDepth());
}
/*
 * call-seq:
 *   [x,y,z] -> Color or nil
 * 
 * returns an color
*/
VALUE _get(VALUE self,VALUE x,VALUE y,VALUE z)
{
	if(_self->getFormat() == Ogre::PF_UNKNOWN)
		return Qnil;
	if((_self->getWidth() <= NUM2UINT(x)) || (_self->getHeight() <= NUM2UINT(y)) || (_self->getDepth() <= NUM2UINT(z)))
		return Qnil;
	return wrap(_self->getColourAt(NUM2INT(x),NUM2INT(y),NUM2INT(z)));
}
/*
 *
 */
VALUE _set(VALUE self,VALUE x,VALUE y,VALUE z,VALUE col)
{
	if(_self->getFormat() != Ogre::PF_UNKNOWN)
		_self->setColourAt(wrap<Ogre::ColourValue>(col),NUM2INT(x),NUM2INT(y),NUM2INT(z));
	return col;
}

singlefunc(flipAroundX)
singlefunc(flipAroundY)

singlefunc(getHasAlpha)

/*
 * call-seq:
 *   each {|x,y,z,color| }
 *   each -> Enumerator
 * 
 * iterates the Image
*/
VALUE _each(VALUE self)
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
VALUE _encode(VALUE self,VALUE formatextension)
{
	return wrap(_self->encode(wrap<Ogre::String>(formatextension)));
}
/*
*/
VALUE _save(VALUE self,VALUE filename)
{
	_self->save(wrap<Ogre::String>(filename));
	return self;
}

}
}

void Init_OgreImage(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	using namespace RubyOgre::Image;

	rb_cOgreImage = rb_define_class_under(rb_mOgre,"Image",rb_cObject);
	rb_define_alloc_func(rb_cOgreImage,_alloc);
	rb_define_method(rb_cOgreImage,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_method(rb_cOgreImage,"size",RUBY_METHOD_FUNC(_size),0);
	rb_define_method(rb_cOgreImage,"width",RUBY_METHOD_FUNC(_width),0);
	rb_define_method(rb_cOgreImage,"height",RUBY_METHOD_FUNC(_height),0);
	rb_define_method(rb_cOgreImage,"depth",RUBY_METHOD_FUNC(_depth),0);

	rb_define_method(rb_cOgreImage,"[]",RUBY_METHOD_FUNC(_get),3);
	rb_define_method(rb_cOgreImage,"[]=",RUBY_METHOD_FUNC(_set),4);

	rb_define_method(rb_cOgreImage,"alpha?",RUBY_METHOD_FUNC(_getHasAlpha),0);
	rb_define_method(rb_cOgreImage,"flipAroundY",RUBY_METHOD_FUNC(_flipAroundY),0);
	rb_define_method(rb_cOgreImage,"flipAroundX",RUBY_METHOD_FUNC(_flipAroundX),0);
	
	rb_define_method(rb_cOgreImage,"encode",RUBY_METHOD_FUNC(_encode),1);
	rb_define_method(rb_cOgreImage,"save",RUBY_METHOD_FUNC(_save),1);
	
	rb_define_method(rb_cOgreImage,"each",RUBY_METHOD_FUNC(_each),0);

	rb_include_module(rb_cOgreImage,rb_mEnumerable);

	registerklass<Ogre::Image>(rb_cOgreImage);
}
