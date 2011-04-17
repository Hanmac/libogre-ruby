#include "ogreexception.hpp"
VALUE rb_eOgreException, rb_eOgreFileNotFoundException, rb_eOgreItemIdentityException;


void Init_OgreException(VALUE rb_mOgre)
{
	#if 0
	rb_mOgre = rb_define_module("Ogre");
	#endif
	rb_eOgreException = rb_define_class_under(rb_mOgre,"Exception",rb_eException);
	rb_eOgreFileNotFoundException = rb_define_class_under(rb_mOgre,"FileNotFoundException",rb_eOgreException);
	rb_eOgreItemIdentityException = rb_define_class_under(rb_mOgre,"ItemIdentityException",rb_eOgreException);
}
