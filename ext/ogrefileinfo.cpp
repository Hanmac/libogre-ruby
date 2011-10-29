#include "ogrefileinfo.hpp"

#define _self wrap<Ogre::FileInfo*>(self)
VALUE rb_cOgreFileInfo;


VALUE OgreFileInfo_alloc(VALUE self)
{
	return wrap(new Ogre::FileInfo);
}

macro_attr_prop(FileInfo,filename,Ogre::String)
macro_attr_prop(FileInfo,path,Ogre::String)
macro_attr_prop(FileInfo,basename,Ogre::String)
macro_attr_prop_with_func(FileInfo,compressedSize,UINT2NUM,NUM2UINT)
macro_attr_prop_with_func(FileInfo,uncompressedSize,UINT2NUM,NUM2UINT)

/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE OgreFileInfo_inspect(VALUE self)
{
	VALUE array[5];
	array[0]=rb_str_new2("#<%s:%s(%d;%d)>");
	array[1]=rb_class_of(self);
	array[2]=OgreFileInfo_get_filename(self);
	array[3]=OgreFileInfo_get_compressedSize(self);
	array[4]=OgreFileInfo_get_uncompressedSize(self);
	return rb_f_sprintf(5,array);
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
	rb_cOgreFileInfo = rb_define_class_under(rb_mOgre,"FileInfo",rb_cObject);
	rb_define_alloc_func(rb_cOgreFileInfo,OgreFileInfo_alloc);
	rb_define_attr_method(rb_cOgreFileInfo,"filename",OgreFileInfo_get_filename,OgreFileInfo_set_filename);
	rb_define_attr_method(rb_cOgreFileInfo,"path",OgreFileInfo_get_path,OgreFileInfo_set_path);
	rb_define_attr_method(rb_cOgreFileInfo,"basename",OgreFileInfo_get_basename,OgreFileInfo_set_basename);
	rb_define_attr_method(rb_cOgreFileInfo,"compressedSize",OgreFileInfo_get_compressedSize,OgreFileInfo_set_compressedSize);
	rb_define_attr_method(rb_cOgreFileInfo,"uncompressedSize",OgreFileInfo_get_uncompressedSize,OgreFileInfo_set_uncompressedSize);
	
	rb_define_method(rb_cOgreFileInfo,"inspect",RUBY_METHOD_FUNC(OgreFileInfo_inspect),0);
}
