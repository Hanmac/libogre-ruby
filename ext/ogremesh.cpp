#include "ogreresource.hpp"
#include "ogremesh.hpp"
#include "ogreexception.hpp"
#include "ogreplane.hpp"
#include "ogrevector3.hpp"
#include "ogresubmesh.hpp"
#define _self wrap<Ogre::MeshPtr>(self)
#define _manager Ogre::MeshManager::getSingletonPtr()
VALUE rb_cOgreMesh;

template <>
VALUE wrap< Ogre::MeshPtr >(const Ogre::MeshPtr &mesh )
{
	if(mesh.isNull())
		return Qnil;
	return Data_Wrap_Struct(rb_cOgreMesh, NULL, free, new Ogre::MeshPtr(mesh));
}

template <>
Ogre::MeshPtr wrap< Ogre::MeshPtr >(const VALUE &vmesh)
{
	if(rb_obj_is_kind_of(vmesh,rb_cString))
		return _manager->getByName(wrap<Ogre::String>(vmesh));

	return *unwrapPtr<Ogre::MeshPtr>(vmesh, rb_cOgreMesh);
}


namespace RubyOgre
{
namespace Mesh
{

singlereturn(getSkeleton)
singlereturn(getSkeletonName)
/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::SubMesh*>(_self->getSubMeshIterator());
	return self;
}

/*
*/
VALUE _each_pose(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::Pose*>(_self->getPoseIterator());
	return self;
}



/*
 *
 */
VALUE _export(int argc,VALUE *argv,VALUE self)
{
	VALUE filename,opt,endian = Qnil,version = Qnil;
	rb_scan_args(argc, argv, "11",&filename,&opt);

	if(rb_obj_is_kind_of(opt,rb_cHash))
	{
		endian = rb_hash_aref(opt,ID2SYM(rb_intern("endian")));
		version = rb_hash_aref(opt,ID2SYM(rb_intern("version")));
	}

	Ogre::MeshSerializer serial;
	serial.exportMesh(_self.get(),
		wrap<Ogre::String>(filename),
		wrapenum<Ogre::MeshVersion>(version),
		wrapenum<Ogre::MeshSerializer::Endian>(endian)
	);

	return self;

}

/*
 *
 */
VALUE _singleton_createManual(int argc,VALUE *argv,VALUE self)
{
	VALUE name, groupName;
	rb_scan_args(argc, argv, "11",&name,&groupName);
	RUBYTRY(
		_manager->createManual(wrap<Ogre::String>(name),
			unwrapResourceGroup(groupName,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME)
		);
	);

	return Qnil;
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
	rb_scan_args(argc, argv, "51",&name,&groupName,&plane,&width,&height,&opt);

	int xsegments = 1, ysegments = 1;
	bool normals = true;
	unsigned short numTexCoordSets = 1;
	Ogre::Real uTile = 1.0f, vTile = 1.0f;
	Ogre::Vector3 upVector = Ogre::Vector3::UNIT_Y;
	if(rb_obj_is_kind_of(opt, rb_cHash))
	{
		VALUE temp;
		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("xsegments")))))
			xsegments = NUM2INT(temp);
		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("ysegments")))))
			ysegments = NUM2INT(temp);
		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("normals")))))
			normals = RTEST(temp);
		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("text_coords")))))
			numTexCoordSets = NUM2UINT(temp);
		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("utile")))))
			uTile = NUM2DBL(temp);
		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("vtile")))))
			vTile = NUM2DBL(temp);
		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("upVector")))))
			upVector = wrap<Ogre::Vector3>(temp);
    }
	RUBYTRY(
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
	)
	return Qnil;

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

	rb_define_method(rb_cOgreMesh,"each_pose",RUBY_METHOD_FUNC(_each_pose),0);

	rb_define_method(rb_cOgreMesh,"export",RUBY_METHOD_FUNC(_export),-1);

	rb_define_method(rb_cOgreMesh,"skeleton",RUBY_METHOD_FUNC(_getSkeleton),0);
	rb_define_method(rb_cOgreMesh,"skeleton_name",RUBY_METHOD_FUNC(_getSkeletonName),0);

	rb_define_singleton_method(rb_cOgreMesh,"create_manual",RUBY_METHOD_FUNC(_singleton_createManual),-1);
	rb_define_singleton_method(rb_cOgreMesh,"create_plane",RUBY_METHOD_FUNC(_singleton_createPlane),-1);

	registerenum<Ogre::MeshVersion>("Ogre::MeshVersion")
		.add(Ogre::MESH_VERSION_LATEST,"latest")
		.add(Ogre::MESH_VERSION_1_8,"v1_8")
		.add(Ogre::MESH_VERSION_1_7,"v1_7")
		.add(Ogre::MESH_VERSION_1_4,"v1_4")
		.add(Ogre::MESH_VERSION_1_0,"v1_0");

	registerenum<Ogre::Serializer::Endian>("Ogre::Serializer::Endian")
		.add(Ogre::Serializer::ENDIAN_NATIVE,"native")
		.add(Ogre::Serializer::ENDIAN_BIG,"big")
		.add(Ogre::Serializer::ENDIAN_LITTLE,"little");
}
