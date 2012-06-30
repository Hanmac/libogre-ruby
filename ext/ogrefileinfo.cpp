#include "ogrefileinfo.hpp"
#include "ogreexception.hpp"

#define _self wrap<Ogre::FileInfo*>(self)
VALUE rb_cOgreFileInfo;

template <>
VALUE wrap< Ogre::FileInfo >(Ogre::FileInfo *fileinfo )
{
	return Data_Wrap_Struct(rb_cOgreFileInfo, NULL, free, fileinfo);
}


namespace RubyOgre
{
namespace FileInfo
{

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::FileInfo);
}

macro_attr_prop(filename,Ogre::String)
macro_attr_prop(path,Ogre::String)
macro_attr_prop(basename,Ogre::String)
macro_attr_prop(compressedSize,uint)
macro_attr_prop(uncompressedSize,uint)

/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[5];
	array[0]=rb_str_new2("#<%s:%s(%d;%d)>");
	array[1]=rb_class_of(self);
	array[2]=_get_filename(self);
	array[3]=_get_compressedSize(self);
	array[4]=_get_uncompressedSize(self);
	return rb_f_sprintf(5,array);
}

}
}

void Init_OgreFileInfo(VALUE rb_mOgre)
{
	#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	rb_define_attr(rb_cOgreFileInfo,"filename",1,1);
	rb_define_attr(rb_cOgreFileInfo,"path",1,1);
	rb_define_attr(rb_cOgreFileInfo,"basename",1,1);
	
	rb_define_attr(rb_cOgreFileInfo,"compressedSize",1,1);
	rb_define_attr(rb_cOgreFileInfo,"uncompressedSize",1,1);
	#endif
	using namespace RubyOgre::FileInfo;

	rb_cOgreFileInfo = rb_define_class_under(rb_mOgre,"FileInfo",rb_cObject);
	rb_define_alloc_func(rb_cOgreFileInfo,_alloc);
	rb_define_attr_method(rb_cOgreFileInfo,"filename",_get_filename,_set_filename);
	rb_define_attr_method(rb_cOgreFileInfo,"path",_get_path,_set_path);
	rb_define_attr_method(rb_cOgreFileInfo,"basename",_get_basename,_set_basename);
	rb_define_attr_method(rb_cOgreFileInfo,"compressedSize",_get_compressedSize,_set_compressedSize);
	rb_define_attr_method(rb_cOgreFileInfo,"uncompressedSize",_get_uncompressedSize,_set_uncompressedSize);
	
	rb_define_method(rb_cOgreFileInfo,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	registerklass<Ogre::FileInfo>(rb_cOgreFileInfo);
}
