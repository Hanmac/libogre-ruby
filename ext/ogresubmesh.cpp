#include "ogresubmesh.hpp"
#include "ogremesh.hpp"
#define _self wrap<Ogre::SubMesh*>(self)
VALUE rb_cOgreSubMesh;

macro_attr(SubMesh,MaterialName,Ogre::String)
/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE OgreSubMesh_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:(%s)>");
	array[1]=rb_class_of(self);
	array[2]=OgreSubMesh_getMaterialName(self);
	return rb_f_sprintf(3,array);
}
/*
 * Document-class: Ogre::Mesh::Sub
 * 
 * This class represents an SubMesh.
*/ 
void Init_OgreSubMesh(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);
	rb_cOgreMesh = rb_define_class_under(rb_mOgre,"Mesh",rb_cOgreResource);
	rb_define_attr(rb_cOgreSubMesh,"material",1,1);
#endif
	rb_cOgreSubMesh = rb_define_class_under(rb_cOgreMesh,"Sub",rb_cObject);

	rb_define_attr_method(rb_cOgreSubMesh,"material",OgreSubMesh_getMaterialName,OgreSubMesh_setMaterialName);

	rb_define_method(rb_cOgreSubMesh,"inspect",RUBY_METHOD_FUNC(OgreSubMesh_inspect),0);
}
