#ifndef __RubyOgrePass_H__
#define __RubyOgrePass_H__

#include "main.hpp"
void Init_OgrePass(VALUE rb_mOgre);
extern VALUE rb_cOgrePass;


template <>
inline VALUE wrap< Ogre::Pass >(Ogre::Pass *pass )
{
	return Data_Wrap_Struct(rb_cOgrePass, NULL, NULL, pass);
}

template <>
inline Ogre::Pass* wrap< Ogre::Pass* >(const VALUE &vpass)
{
	if ( ! rb_obj_is_kind_of(vpass, rb_cOgrePass) )
		return NULL;
	Ogre::Pass *pass;
  Data_Get_Struct( vpass, Ogre::Pass, pass);
	return pass;
}
#endif /* __RubyOgrePass_H__ */
