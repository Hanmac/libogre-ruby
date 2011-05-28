#ifndef __RubyOgreTexture_H__
#define __RubyOgreTexture_H__

#include "main.hpp"
void Init_OgreTexture(VALUE rb_mOgre);
extern VALUE rb_cOgreTexture;


template <>
inline VALUE wrap< Ogre::Texture >(Ogre::Texture *texture )
{
	return Data_Wrap_Struct(rb_cOgreTexture, NULL, NULL, texture);
}

template <>
inline Ogre::Texture* wrap< Ogre::Texture* >(const VALUE &vtexture)
{
	if ( ! rb_obj_is_kind_of(vtexture, rb_cOgreTexture) )
		return NULL;
	Ogre::Texture *texture;
  Data_Get_Struct( vtexture, Ogre::Texture, texture);
	return texture;
}
#endif /* __RubyOgreTexture_H__ */
