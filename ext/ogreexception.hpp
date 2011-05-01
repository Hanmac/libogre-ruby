#ifndef __RubyOgreException_H__
#define __RubyOgreException_H__

#include "main.hpp"
void Init_OgreException(VALUE rb_mOgre);
extern VALUE rb_mOgreError;

extern VALUE rb_eOgreFileNotFoundError,	rb_eOgreIOError,
	rb_eOgreItemIdentityException, rb_eOgreInvalidParametersException, 
	rb_eOgreUnimplementedException;

extern VALUE rb_eErrnoENT;

inline void rb_raise(VALUE exception){
	rb_funcall(rb_mKernel,rb_intern("raise"),1,exception);
}

template <>
inline VALUE wrap< Ogre::IOException >(Ogre::IOException *exception )
{
	return Data_Wrap_Struct(rb_eOgreIOError, NULL, free, exception);
}

template <>
inline VALUE wrap< Ogre::ItemIdentityException >(Ogre::ItemIdentityException *exception )
{
	return Data_Wrap_Struct(rb_eOgreItemIdentityException, NULL, free, exception);
}
template <>
inline VALUE wrap< Ogre::FileNotFoundException >(Ogre::FileNotFoundException *exception )
{
	return Data_Wrap_Struct(rb_eOgreFileNotFoundError, NULL, free, exception);
}
template <>
inline VALUE wrap< Ogre::InvalidParametersException >(Ogre::InvalidParametersException *exception )
{
	return Data_Wrap_Struct(rb_eOgreFileNotFoundError, NULL, free, exception);
}
template <>
inline VALUE wrap< Ogre::UnimplementedException >(Ogre::UnimplementedException *exception )
{
	return Data_Wrap_Struct(rb_eOgreUnimplementedException, NULL, free, exception);
}

template <>
inline VALUE wrap<Ogre::Exception >(const Ogre::Exception &e )
{
	switch((Ogre::Exception::ExceptionCodes)e.getNumber()){
	case Ogre::Exception::ERR_ITEM_NOT_FOUND:
	case Ogre::Exception::ERR_DUPLICATE_ITEM:
		return wrap(*reinterpret_cast<const Ogre::ItemIdentityException*>(&e));
	case Ogre::Exception::ERR_CANNOT_WRITE_TO_FILE:
		return wrap(*reinterpret_cast<const Ogre::IOException*>(&e));
	case Ogre::Exception::ERR_FILE_NOT_FOUND:
		return wrap(*reinterpret_cast<const Ogre::FileNotFoundException*>(&e));
	case Ogre::Exception::ERR_INVALIDPARAMS:
		return wrap(*reinterpret_cast<const Ogre::InvalidParametersException*>(&e));
	case Ogre::Exception::ERR_NOT_IMPLEMENTED:
		return wrap(*reinterpret_cast<const Ogre::UnimplementedException*>(&e));
	default:
		return Qnil;
	}
}


template <>
inline Ogre::Exception* wrap< Ogre::Exception* >(const VALUE &vexception)
{
	if ( ! rb_obj_is_kind_of(vexception, rb_mOgreError) )
		return NULL;
	Ogre::Exception *exception;
  Data_Get_Struct( vexception, Ogre::Exception, exception);
	return exception;
}

#endif /* __RubyOgreException_H__ */
