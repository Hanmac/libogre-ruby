#ifndef __RubyOgreMaterial_H__
#define __RubyOgreMaterial_H__

#include "main.hpp"
void Init_OgreMaterial(VALUE rb_mOgre);
extern VALUE rb_cOgreMaterial;

template <>
VALUE wrap< Ogre::MaterialPtr >(const Ogre::MaterialPtr &material );

template <>
Ogre::MaterialPtr wrap< Ogre::MaterialPtr >(const VALUE &vmaterial);
#endif /* __RubyOgreMaterial_H__ */
