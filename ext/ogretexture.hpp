#ifndef __RubyOgreTexture_H__
#define __RubyOgreTexture_H__

#include "main.hpp"
void Init_OgreTexture(VALUE rb_mOgre);
extern VALUE rb_cOgreTexture;


template <>
VALUE wrap< Ogre::TexturePtr >(const Ogre::TexturePtr &texture );

template <>
Ogre::TexturePtr wrap< Ogre::TexturePtr >(const VALUE &vtexture);

#endif /* __RubyOgreTexture_H__ */
