#ifndef __RubyOgreSubMesh_H__
#define __RubyOgreSubMesh_H__

#include "main.hpp"
void Init_OgreSubMesh(VALUE rb_mOgre);
extern VALUE rb_cOgreSubMesh;


template <>
inline VALUE wrap< Ogre::SubMesh >(Ogre::SubMesh *submesh )
{
	return Data_Wrap_Struct(rb_cOgreSubMesh, NULL, NULL, submesh);
}

template <>
inline Ogre::SubMesh* wrap< Ogre::SubMesh* >(const VALUE &vsubmesh)
{
	if ( ! rb_obj_is_kind_of(vsubmesh, rb_cOgreSubMesh) )
		return NULL;
	Ogre::SubMesh *submesh;
  Data_Get_Struct( vsubmesh, Ogre::SubMesh, submesh);
	return submesh;
}
#endif /* __RubyOgreSubMesh_H__ */
