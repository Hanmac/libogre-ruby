#include "ogredatastream.hpp"
#define _self wrap<Ogre::DataStream*>(self)
VALUE rb_cOgreDataStream;


/*

*/
VALUE OgreDataStream_name(VALUE self)
{
	const char *cstr = _self->getName().c_str();
	return cstr ? rb_str_new2(cstr) : Qnil;
}
/*

*/
VALUE OgreDataStream_size(VALUE self)
{
	return ULONG2NUM(_self->size());
}
/*

*/
VALUE OgreDataStream_isReadable(VALUE self)
{
	return _self->isReadable() ? Qtrue : Qfalse;
}
/*

*/
VALUE OgreDataStream_isWriteable(VALUE self)
{
	return _self->isWriteable() ? Qtrue : Qfalse;
}
/*

*/
VALUE OgreDataStream_eof(VALUE self)
{
	char buff[1];
	size_t read_bytes = _self->read(&buff,1);
	bool result = _self->eof();
	_self->skip(-read_bytes);
	return result ? Qtrue : Qfalse;
}
/*

*/
VALUE OgreDataStream_tell(VALUE self)
{
	return ULONG2NUM(_self->tell());
}
/*

*/
VALUE OgreDataStream_pos_set(VALUE self,VALUE pos)
{
	_self->seek(NUM2ULONG(pos));
	return pos;
}
/*

*/
VALUE OgreDataStream_seek(int argc, VALUE* argv,VALUE self)
{
	VALUE pos,type;
	rb_scan_args(argc, argv, "11",&pos,&type);
	if(NIL_P(type))
		type = rb_const_get(rb_cIO,rb_intern("SEEK_SET"));
	switch(NUM2UINT(type)){
	case SEEK_SET:
		_self->seek(NUM2ULONG(pos));
		break;
	case SEEK_CUR:
		_self->skip(NUM2LONG(pos));
		break;
	case SEEK_END:
		if(_self->size() == (size_t)0)
			rb_raise(rb_eTypeError,"can not seek relative to the size of a %s if size is 0.",rb_class2name(rb_cOgreDataStream));
		_self->seek(_self->size() + NUM2LONG(pos));
		break;
	}
	return Qnil;
}
/*

*/
VALUE OgreDataStream_skip(VALUE self,VALUE pos)
{
	_self->skip(NUM2LONG(pos));
	return Qnil;
}
/*

*/
VALUE OgreDataStream_read(int argc,VALUE *argv,VALUE self)
{
	VALUE i, buffer;
	rb_scan_args(argc, argv, "02",&i,&buffer);
	if(NIL_P(i)){

		VALUE result = rb_str_new2("");
		while(!_self->eof()){
			char buff[10240];
			size_t bytesread = _self->read(&buff,10240);
			VALUE temp = rb_str_new(buff,bytesread);
			if(NIL_P(buffer))
				rb_funcall(result,rb_intern("<<"),1,temp);
			else if(rb_respond_to(buffer,rb_intern("write")))
				rb_funcall(buffer,rb_intern("write"),1,temp);
			else
				rb_funcall(buffer,rb_intern("<<"),1,temp);
		}
		return (NIL_P(buffer)) ? result : buffer;
	}else{
		char buff[NUM2UINT(i)];
		size_t bytesread = _self->read(&buff,NUM2UINT(i));
		VALUE result = rb_str_new(buff,bytesread);
		if(NIL_P(buffer))
			return result;
		else if(rb_respond_to(buffer,rb_intern("write")))
			rb_funcall(buffer,rb_intern("write"),1,result);
		else
			rb_funcall(buffer,rb_intern("<<"),1,result);
		return buffer;
	}
}
/*

*/
VALUE OgreDataStream_write(VALUE self,VALUE string)
{
	return ULONG2NUM(_self->write(RSTRING_PTR(string),RSTRING_LEN(string)));
}
/*

*/
VALUE OgreDataStream_close(VALUE self)
{
	_self->close();
	return Qnil;
}


void Init_OgreDataStream(VALUE rb_mOgre)
{
	#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	#endif
	rb_cOgreDataStream = rb_define_class_under(rb_mOgre,"DataStream",rb_cObject);
	rb_undef_alloc_func(rb_cOgreDataStream);
	
	rb_define_method(rb_cOgreDataStream,"name",RUBY_METHOD_FUNC(OgreDataStream_name),0);
	rb_define_method(rb_cOgreDataStream,"size",RUBY_METHOD_FUNC(OgreDataStream_size),0);
	
	rb_define_method(rb_cOgreDataStream,"readable?",RUBY_METHOD_FUNC(OgreDataStream_isReadable),0);
	rb_define_method(rb_cOgreDataStream,"writeable?",RUBY_METHOD_FUNC(OgreDataStream_isWriteable),0);
	rb_define_method(rb_cOgreDataStream,"eof?",RUBY_METHOD_FUNC(OgreDataStream_eof),0);
	rb_define_method(rb_cOgreDataStream,"tell",RUBY_METHOD_FUNC(OgreDataStream_tell),0);
	rb_define_method(rb_cOgreDataStream,"seek",RUBY_METHOD_FUNC(OgreDataStream_seek),-1);
	rb_define_alias(rb_cOgreDataStream,"pos","tell");
	rb_define_method(rb_cOgreDataStream,"pos=",RUBY_METHOD_FUNC(OgreDataStream_pos_set),1);
	
	rb_define_method(rb_cOgreDataStream,"skip",RUBY_METHOD_FUNC(OgreDataStream_skip),1);
	rb_define_method(rb_cOgreDataStream,"read",RUBY_METHOD_FUNC(OgreDataStream_read),-1);//TODO: more parameter
	rb_define_method(rb_cOgreDataStream,"write",RUBY_METHOD_FUNC(OgreDataStream_write),1);
	rb_define_method(rb_cOgreDataStream,"close",RUBY_METHOD_FUNC(OgreDataStream_close),0);
	//rb_define_method(rb_cOgreDataStream,"readline",RUBY_METHOD_FUNC(OgreDataStream_readLine),0);
}
