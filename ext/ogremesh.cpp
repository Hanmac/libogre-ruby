#include "ogreresource.hpp"
#include "ogremesh.hpp"
#include "ogresubmesh.hpp"
#define _self wrap<Ogre::Mesh*>(self)
VALUE rb_cOgreMesh;

/*
*/
VALUE OgreMesh_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::SubMesh*>(_self->getSubMeshIterator());
	return self;
}

void Init_OgreMesh(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);
#endif
	rb_cOgreMesh = rb_define_class_under(rb_mOgre,"Mesh",rb_cOgreResource);

	rb_define_method(rb_cOgreMesh,"each",RUBY_METHOD_FUNC(OgreMesh_each),0);
	rb_include_module(rb_cOgreMesh,rb_mEnumerable);

}
