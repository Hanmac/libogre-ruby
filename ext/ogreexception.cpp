#include "ogreexception.hpp"
#define _self wrap<Ogre::Exception*>(self)
VALUE rb_mOgreError;
VALUE rb_eOgreIOError;
VALUE rb_eOgreItemIdentityException;
VALUE rb_eOgreInvalidParametersException;
VALUE rb_eOgreFileNotFoundError;
VALUE rb_eOgreUnimplementedException;
VALUE rb_eOgreInvalidStateException;
VALUE rb_eOgreInternalErrorException;
VALUE rb_eErrnoENT;

namespace RubyOgre {
namespace Exception {

singlereturn(getFullDescription)
singlereturn(getDescription)

singlereturn(getNumber)
singlereturn(getSource)
singlereturn(getFile)
singlereturn(getLine)

}}

void Init_OgreException(VALUE rb_mOgre)
{
	#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_mErrno = rb_define_module("Errno");
	rb_eErrnoENT = rb_define_class_under(rb_mErrno,"ENOENT",rb_eException);
	#endif
	using namespace RubyOgre::Exception;

	rb_mOgreError = rb_define_module_under(rb_mOgre,"Error");
	rb_define_method(rb_mOgreError,"to_s",RUBY_METHOD_FUNC(_getDescription),0);
	rb_define_method(rb_mOgreError,"fulldescription",RUBY_METHOD_FUNC(_getFullDescription),0);

	rb_define_method(rb_mOgreError,"to_i",RUBY_METHOD_FUNC(_getNumber),0);
	rb_define_method(rb_mOgreError,"source",RUBY_METHOD_FUNC(_getSource),0);
	rb_define_method(rb_mOgreError,"file",RUBY_METHOD_FUNC(_getFile),0);
	rb_define_method(rb_mOgreError,"line",RUBY_METHOD_FUNC(_getLine),0);
	
	rb_eErrnoENT = rb_const_get(rb_mErrno,rb_intern("ENOENT"));
	rb_eOgreIOError = rb_define_class_under(rb_mOgreError,"IOError",rb_eIOError);
	rb_eOgreFileNotFoundError = rb_define_class_under(rb_mOgreError,"FileNotFound",rb_eErrnoENT);
	rb_eOgreItemIdentityException = rb_define_class_under(rb_mOgreError,"ItemIdentityException",rb_eKeyError);
	rb_eOgreUnimplementedException = rb_define_class_under(rb_mOgreError,"UnimplementedException",rb_eNotImpError);
	rb_eOgreInvalidStateException = rb_define_class_under(rb_mOgreError,"InvalidStateException",rb_eException);
	rb_eOgreInvalidParametersException = rb_define_class_under(rb_mOgreError,"InvalidParameterException",rb_eException);
	rb_eOgreInternalErrorException = rb_define_class_under(rb_mOgreError,"InternalErrorException",rb_eSyntaxError);
	
	
	
	rb_include_module(rb_eOgreIOError,rb_mOgreError);
	rb_include_module(rb_eOgreFileNotFoundError,rb_mOgreError);
	rb_include_module(rb_eOgreItemIdentityException,rb_mOgreError);
	rb_include_module(rb_eOgreUnimplementedException,rb_mOgreError);
	rb_include_module(rb_eOgreInvalidStateException,rb_mOgreError);
	rb_include_module(rb_eOgreInternalErrorException,rb_mOgreError);

}
