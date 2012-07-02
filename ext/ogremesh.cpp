#include "ogreresource.hpp"
#include "ogremesh.hpp"
#include "ogreplane.hpp"
#include "ogrevector3.hpp"
#include "ogresubmesh.hpp"
#define _self wrap<Ogre::Mesh*>(self)
#define _manager Ogre::MeshManager::getSingletonPtr()
VALUE rb_cOgreMesh;

template <>
VALUE wrap< Ogre::MeshPtr >(Ogre::MeshPtr *mesh )
{
	return Data_Wrap_Struct(rb_cOgreMesh, NULL, free, mesh);
}

template <>
Ogre::Mesh* wrap< Ogre::Mesh* >(const VALUE &vmesh)
{
	return unwrapPtr<Ogre::MeshPtr>(vmesh, rb_cOgreMesh)->get();
}


namespace RubyOgre
{
namespace Mesh
{

/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::SubMesh*>(_self->getSubMeshIterator());
	return self;
}


/*
 *         MeshPtr createPlane(
            const String& name, const String& groupName, const Plane& plane,
            Real width, Real height,
            int xsegments = 1, int ysegments = 1,
            bool normals = true, unsigned short numTexCoordSets = 1,
            Real uTile = 1.0f, Real vTile = 1.0f, const Vector3& upVector = Vector3::UNIT_Y,
			HardwareBuffer::Usage vertexBufferUsage = HardwareBuffer::HBU_STATIC_WRITE_ONLY,
			HardwareBuffer::Usage indexBufferUsage = HardwareBuffer::HBU_STATIC_WRITE_ONLY,
			bool vertexShadowBuffer = true, bool indexShadowBuffer = true);
 *
 */

VALUE _singleton_createPlane(int argc,VALUE *argv,VALUE self)
{
	VALUE name, groupName, plane, width, height, opt;
	rb_scan_args(argc, argv, "03",&name,&groupName,&plane,&width,&height,&opt);

	int xsegments = 1, ysegments = 1;
	bool normals = true;
	unsigned short numTexCoordSets = 1;
	Ogre::Real uTile = 1.0f, vTile = 1.0f;
	Ogre::Vector3 upVector = Ogre::Vector3::UNIT_Y;
	if(rb_obj_is_kind_of(opt, rb_cHash))
	{
		VALUE temp;
		if(NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("xsegments")))))
			xsegments = NUM2INT(temp);
		if(NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("ysegments")))))
			ysegments = NUM2INT(temp);
		if(NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("normals")))))
			normals = RTEST(temp);
		if(NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("text_coords")))))
			numTexCoordSets = NUM2UINT(temp);
		if(NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("utile")))))
			uTile = NUM2DBL(temp);
		if(NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("vtile")))))
			vTile = NUM2DBL(temp);
		if(NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("upVector")))))
			upVector = wrap<Ogre::Vector3>(temp);
    }

	return wrap(_manager->createPlane(wrap<Ogre::String>(name),
		unwrapResourceGroup(groupName,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME),
		wrap<Ogre::Plane>(plane),
		NUM2DBL(width),NUM2DBL(height),
		xsegments,ysegments,
		normals,
		numTexCoordSets,
		uTile,vTile,
		upVector
		));
}

}
}

void Init_OgreMesh(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);
#endif
	using namespace RubyOgre::Mesh;

	rb_cOgreMesh = rb_define_class_under(rb_mOgre,"Mesh",rb_cOgreResource);

	rb_define_method(rb_cOgreMesh,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cOgreMesh,rb_mEnumerable);

}