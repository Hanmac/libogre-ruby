#include "ogredatastream.hpp"
#include "ogreexception.hpp"

#define _self wrap<Ogre::DataStreamPtr>(self)
VALUE rb_cOgreDataStream;


template <>
VALUE wrap< Ogre::DataStreamPtr >(Ogre::DataStreamPtr *datastream )
{
	return Data_Wrap_Struct(rb_cOgreDataStream, NULL, free, datastream);
}

template <>
VALUE wrap< Ogre::DataStreamListPtr >(const Ogre::DataStreamListPtr &vec )
{	return wrap<Ogre::DataStreamPtr>(vec);}

template <>
Ogre::DataStreamPtr wrap< Ogre::DataStreamPtr >(const VALUE &vdatastream)
{
	return *unwrapPtr<Ogre::DataStreamPtr>(vdatastream, rb_cOgreDataStream);
}


namespace RubyOgre {
namespace DataStream {


/*

*/
VALUE _name(VALUE self)
{
	const char *cstr = _self->getName().c_str();
	return cstr ? rb_str_new2(cstr) : Qnil;
}
/*

*/
VALUE _size(VALUE self)
{
	return ULONG2NUM(_self->size());
}
singlereturn(getName)
singlereturn(isReadable)
singlereturn(isWriteable)

singlefunc(close)

/*

*/
VALUE _eof(VALUE self)
{
	char buff[1];
	size_t read_bytes = _self->read(&buff,1);
	bool result = _self->eof();
	_self->skip(-read_bytes);
	return result ? Qtrue : Qfalse;
}
/*

*/
VALUE _tell(VALUE self)
{
	return ULONG2NUM(_self->tell());
}
/*

*/
VALUE _pos_set(VALUE self,VALUE pos)
{
	_self->seek(NUM2ULONG(pos));
	return pos;
}
/*

*/
VALUE _seek(int argc, VALUE* argv,VALUE self)
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
VALUE _skip(VALUE self,VALUE pos)
{
	_self->skip(NUM2LONG(pos));
	return Qnil;
}
/*

*/
VALUE _read(int argc,VALUE *argv,VALUE self)
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
VALUE _write(VALUE self,VALUE string)
{
	return ULONG2NUM(_self->write(RSTRING_PTR(string),RSTRING_LEN(string)));
}

}}

void Init_OgreDataStream(VALUE rb_mOgre)
{
	#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	#endif
	using namespace RubyOgre::DataStream;

	rb_cOgreDataStream = rb_define_class_under(rb_mOgre,"DataStream",rb_cObject);
	rb_undef_alloc_func(rb_cOgreDataStream);
	
	rb_define_method(rb_cOgreDataStream,"name",RUBY_METHOD_FUNC(_getName),0);
	rb_define_method(rb_cOgreDataStream,"size",RUBY_METHOD_FUNC(_size),0);
	
	rb_define_method(rb_cOgreDataStream,"readable?",RUBY_METHOD_FUNC(_isReadable),0);
	rb_define_method(rb_cOgreDataStream,"writeable?",RUBY_METHOD_FUNC(_isWriteable),0);
	rb_define_method(rb_cOgreDataStream,"eof?",RUBY_METHOD_FUNC(_eof),0);
	rb_define_method(rb_cOgreDataStream,"tell",RUBY_METHOD_FUNC(_tell),0);
	rb_define_method(rb_cOgreDataStream,"seek",RUBY_METHOD_FUNC(_seek),-1);
	rb_define_alias(rb_cOgreDataStream,"pos","tell");
	rb_define_method(rb_cOgreDataStream,"pos=",RUBY_METHOD_FUNC(_pos_set),1);
	
	rb_define_method(rb_cOgreDataStream,"skip",RUBY_METHOD_FUNC(_skip),1);
	rb_define_method(rb_cOgreDataStream,"read",RUBY_METHOD_FUNC(_read),-1);
	rb_define_method(rb_cOgreDataStream,"write",RUBY_METHOD_FUNC(_write),1);
	rb_define_method(rb_cOgreDataStream,"close",RUBY_METHOD_FUNC(_close),0);
	//rb_define_method(rb_cOgreDataStream,"readline",RUBY_METHOD_FUNC(_readLine),0);
}
