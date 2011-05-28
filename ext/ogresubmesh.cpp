#include "ogresubmesh.hpp"
#include "ogremesh.hpp"
#define _self wrap<Ogre::SubMesh*>(self)
VALUE rb_cOgreSubMesh;

/*
*/
VALUE OgreSubMesh_get_material(VALUE self)
{
	return wrap(_self->getMaterialName());
}
/*
*/
VALUE OgreSubMesh_set_material(VALUE self,VALUE name)
{
	_self->setMaterialName(rb_string_value_cstr(&name));
	return name;
}

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
	array[2]=OgreSubMesh_get_material(self);
	return rb_f_sprintf(3,array);
}

void Init_OgreSubMesh(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);
	rb_cOgreMesh = rb_define_class_under(rb_mOgre,"Mesh",rb_cOgreResource);
#endif
	rb_cOgreSubMesh = rb_define_class_under(rb_cOgreMesh,"Sub",rb_cObject);

	rb_define_method(rb_cOgreSubMesh,"material",RUBY_METHOD_FUNC(OgreSubMesh_get_material),0);
	rb_define_method(rb_cOgreSubMesh,"material=",RUBY_METHOD_FUNC(OgreSubMesh_set_material),1);

	rb_define_method(rb_cOgreSubMesh,"inspect",RUBY_METHOD_FUNC(OgreSubMesh_inspect),0);
}
