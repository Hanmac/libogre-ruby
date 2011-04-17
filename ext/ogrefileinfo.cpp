#include "ogrefileinfo.hpp"

#define _self wrap<Ogre::FileInfo*>(self)
VALUE rb_cOgreFileInfo;


VALUE OgreFileInfo_alloc(VALUE self)
{
	Ogre::FileInfo *temp = new Ogre::FileInfo;
	return wrap(temp);
}
/*
/// multi-Archive searches, note you should still open through ResourceGroupManager)
		Archive* archive;
        /// The file's fully qualified name
        String filename;
        /// Path name; separated by '/' and ending with '/'
        String path;
        /// Base filename
        String basename;
        /// Compressed size
        size_t compressedSize;
        /// Uncompressed size
        size_t uncompressedSize;
*/

/*:nodoc:


*/
VALUE OgreFileInfo_get_filename(VALUE self)
{
	return wrap(_self->filename);
}
/*:nodoc:


*/
VALUE OgreFileInfo_get_path(VALUE self)
{
	return wrap(_self->path);
}
/*:nodoc:


*/
VALUE OgreFileInfo_get_basename(VALUE self)
{
	return wrap(_self->basename);
}
/*:nodoc:


*/
VALUE OgreFileInfo_get_compressedSize(VALUE self)
{
	return INT2NUM(_self->compressedSize);
}
/*:nodoc:


*/
VALUE OgreFileInfo_get_uncompressedSize(VALUE self)
{
	return INT2NUM(_self->uncompressedSize);
}
/*:nodoc:


*/
VALUE OgreFileInfo_set_filename(VALUE self,VALUE val)
{
	_self->filename = rb_string_value_cstr(&val);
	return val;
}
/*:nodoc:


*/
VALUE OgreFileInfo_set_path(VALUE self,VALUE val)
{
	_self->path = rb_string_value_cstr(&val);
	return val;

}
/*:nodoc:


*/
VALUE OgreFileInfo_set_basename(VALUE self,VALUE val)
{
	_self->basename = rb_string_value_cstr(&val);
	return val;

}
/*


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
	rb_define_method(rb_cOgreFileInfo,"filename",RUBY_METHOD_FUNC(OgreFileInfo_get_filename),0);
	rb_define_method(rb_cOgreFileInfo,"path",RUBY_METHOD_FUNC(OgreFileInfo_get_path),0);
	rb_define_method(rb_cOgreFileInfo,"basename",RUBY_METHOD_FUNC(OgreFileInfo_get_basename),0);
	rb_define_method(rb_cOgreFileInfo,"compressedSize",RUBY_METHOD_FUNC(OgreFileInfo_get_compressedSize),0);
	rb_define_method(rb_cOgreFileInfo,"uncompressedSize",RUBY_METHOD_FUNC(OgreFileInfo_get_uncompressedSize),0);
	
	
	rb_define_method(rb_cOgreFileInfo,"filename=",RUBY_METHOD_FUNC(OgreFileInfo_set_filename),1);
	rb_define_method(rb_cOgreFileInfo,"path=",RUBY_METHOD_FUNC(OgreFileInfo_set_path),1);
	rb_define_method(rb_cOgreFileInfo,"basename=",RUBY_METHOD_FUNC(OgreFileInfo_set_basename),1);
	
	rb_define_method(rb_cOgreFileInfo,"inspect",RUBY_METHOD_FUNC(OgreFileInfo_inspect),0);
}
