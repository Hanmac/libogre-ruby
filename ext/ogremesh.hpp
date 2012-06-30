#ifndef __RubyOgreMesh_H__
#define __RubyOgreMesh_H__

#include "main.hpp"
void Init_OgreMesh(VALUE rb_mOgre);
extern VALUE rb_cOgreMesh;


template <>
VALUE wrap< Ogre::MeshPtr >(Ogre::MeshPtr *mesh );

template <>
Ogre::Mesh* wrap< Ogre::Mesh* >(const VALUE &vmesh);

#endif /* __RubyOgreMesh_H__ */
