#ifndef __RubyOgreException_H__
#define __RubyOgreException_H__

#include "main.hpp"
void Init_OgreException(VALUE rb_mOgre);
extern VALUE rb_eOgreException;
extern VALUE rb_eOgreFileNotFoundException;
//extern VALUE rb_cOgreIOExeption;
extern VALUE rb_eOgreItemIdentityException;
#endif /* __RubyOgreException_H__ */
