#ifndef __RubyOgreMesh_H__
#define __RubyOgreMesh_H__

#include "main.hpp"
void Init_OgreMesh(VALUE rb_mOgre);
extern VALUE rb_cOgreMesh;


template <>
inline VALUE wrap< Ogre::Mesh >(Ogre::Mesh *mesh )
{
	return Data_Wrap_Struct(rb_cOgreMesh, NULL, NULL, mesh);
}

template <>
inline Ogre::Mesh* wrap< Ogre::Mesh* >(const VALUE &vmesh)
{
	if ( ! rb_obj_is_kind_of(vmesh, rb_cOgreMesh) )
		return NULL;
	Ogre::Mesh *mesh;
  Data_Get_Struct( vmesh, Ogre::Mesh, mesh);
	return mesh;
}
#endif /* __RubyOgreMesh_H__ */
