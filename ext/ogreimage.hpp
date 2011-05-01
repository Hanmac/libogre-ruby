#ifndef __RubyOgreImage_H__
#define __RubyOgreImage_H__

#include "main.hpp"
void Init_OgreImage(VALUE rb_mOgre);
extern VALUE rb_cOgreImage;

inline void freeimage(Ogre::Image *image )
{
	image->freeMemory();
}
template <>
inline VALUE wrap< Ogre::Image >(Ogre::Image *image )
{
	return Data_Wrap_Struct(rb_cOgreImage, NULL, freeimage, image);
}


template <>
inline Ogre::Image* wrap< Ogre::Image* >(const VALUE &vimage)
{
	if ( ! rb_obj_is_kind_of(vimage, rb_cOgreImage) )
		return NULL;
	Ogre::Image *image;
  Data_Get_Struct( vimage, Ogre::Image, image);
	return image;
}
#endif /* __RubyOgreImage_H__ */
