#ifndef __RubyOgreMaterial_H__
#define __RubyOgreMaterial_H__

#include "main.hpp"
void Init_OgreMaterial(VALUE rb_mOgre);
extern VALUE rb_cOgreMaterial;

template <>
VALUE wrap< Ogre::MaterialPtr >(Ogre::MaterialPtr *material );

template <>
Ogre::Material* wrap< Ogre::Material* >(const VALUE &vmaterial);
#endif /* __RubyOgreMaterial_H__ */