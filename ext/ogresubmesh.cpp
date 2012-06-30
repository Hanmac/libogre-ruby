#include "ogresubmesh.hpp"
#include "ogremesh.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::SubMesh*>(self)
VALUE rb_cOgreSubMesh;

namespace RubyOgre {
namespace SubMesh {


macro_attr(MaterialName,Ogre::String)
/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:(%s)>");
	array[1]=rb_class_of(self);
	array[2]=_getMaterialName(self);
	return rb_f_sprintf(3,array);
}

}}
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
	using namespace RubyOgre::SubMesh;

	rb_cOgreSubMesh = rb_define_class_under(rb_cOgreMesh,"Sub",rb_cObject);

	rb_define_attr_method(rb_cOgreSubMesh,"material",_getMaterialName,_setMaterialName);

	rb_define_method(rb_cOgreSubMesh,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	registerklass<Ogre::SubMesh>(rb_cOgreSubMesh);
}
