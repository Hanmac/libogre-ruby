#include "ogrecolor.hpp"
#include "ogrevector2.hpp"
#include "ogrevector3.hpp"
#include "ogrevector4.hpp"
#include "ogreradian.hpp"
#include "ogredegree.hpp"
#include "ogresphere.hpp"
#include "ogreroot.hpp"
#include "ogreplane.hpp"
#include "ogreresource.hpp"
#include "ogrerect.hpp"
#include "ogrebox.hpp"
#include "ogreimage.hpp"
#include "ogreexception.hpp"
#include "ogrefileinfo.hpp"
#include "ogreresourcegroup.hpp"
#include "ogrepolygon.hpp"
#include "ogredatastream.hpp"
#include "ogreconfigfile.hpp"
#include "ogrerendertarget.hpp"
#include "ogrerenderwindow.hpp"
#include "ogrerendersystem.hpp"
#include "ogrescenemanager.hpp"
#include "ogremovableobject.hpp"
#include "ogremovableobjectlistener.hpp"
#include "ogrelight.hpp"
#include "ogrenode.hpp"
#include "ogreray.hpp"
#include "ogrelog.hpp"
#include "ogreloglistener.hpp"
#include "ogreaxisalignedbox.hpp"
#include "ogreplaneboundedvolume.hpp"
#include "ogrematrix3.hpp"
#include "ogrematrix4.hpp"
#include "ogrequaternion.hpp"
#include "ogretexture.hpp"
#include "ogremesh.hpp"
#include "ogresubmesh.hpp"
#include "ogrematerial.hpp"
#include "ogretechnique.hpp"
#include "ogrepass.hpp"
#include "ogretextureunitstate.hpp"
#include "ogrelayerblendmode.hpp"
VALUE rb_mOgre,rb_mSingleton;





VALUE Ogre_dummy0(VALUE self)
{
	return Qnil;
}
VALUE Ogre_dummy1(VALUE self,VALUE obj1)
{
	return Qnil;
}
VALUE Ogre_dummy2(VALUE self,VALUE obj1,VALUE obj2)
{
	return Qnil;
}
VALUE Ogre_dummy3(VALUE self,VALUE obj1,VALUE obj2,VALUE obj3)
{
	return Qnil;
}
VALUE Ogre_dummy4(VALUE self,VALUE obj1,VALUE obj2,VALUE obj3,VALUE obj4)
{
	return Qnil;
}

extern "C" void Init_ogre(void)
{
	rb_mOgre = rb_define_module("Ogre");
	Init_OgreRoot(rb_mOgre);
	Init_OgreColor(rb_mOgre);
	Init_OgreVector2(rb_mOgre);
	Init_OgreVector3(rb_mOgre);
	Init_OgreVector4(rb_mOgre);
	Init_OgreRadian(rb_mOgre);
	Init_OgreDegree(rb_mOgre);
	Init_OgreSphere(rb_mOgre);
	Init_OgreRay(rb_mOgre);
	Init_OgrePlane(rb_mOgre);
	Init_OgreResource(rb_mOgre);
	Init_OgreRect(rb_mOgre);
	Init_OgreBox(rb_mOgre);
	Init_OgreImage(rb_mOgre);
	Init_OgreException(rb_mOgre);
	Init_OgreFileInfo(rb_mOgre);
	Init_OgreResourceGroup(rb_mOgre);


	Init_OgrePolygon(rb_mOgre);
	Init_OgreDataStream(rb_mOgre);
	Init_OgreConfigFile(rb_mOgre);
	Init_OgreRenderTarget(rb_mOgre);
	Init_OgreRenderWindow(rb_mOgre);
	Init_OgreRenderSystem(rb_mOgre);
	Init_OgreSceneManager(rb_mOgre);

	Init_OgreMovableObject(rb_mOgre);
	Init_OgreMovableObjectListener(rb_mOgre);
	Init_OgreLight(rb_mOgre);

	Init_OgreNode(rb_mOgre);
	Init_OgreSceneNode(rb_mOgre);

	Init_OgreLog(rb_mOgre);
	Init_OgreLogListener(rb_mOgre);
	Init_OgreAxisAlignedBox(rb_mOgre);
	Init_OgrePlaneBoundedVolume(rb_mOgre);

	Init_OgreMatrix3(rb_mOgre);
	Init_OgreMatrix4(rb_mOgre);
	Init_OgreQuaternion(rb_mOgre);

	Init_OgreTexture(rb_mOgre);
	Init_OgreMaterial(rb_mOgre);
	Init_OgreMesh(rb_mOgre);
	Init_OgreSubMesh(rb_mOgre);
	
	Init_OgreTechnique(rb_mOgre);
	Init_OgrePass(rb_mOgre);
	Init_OgreTextureUnitState(rb_mOgre);
	Init_OgreLayerBlendMode(rb_mOgre);
	VALUE array[4];
	array[0]=rb_str_new2("%d.%d.%d");
	array[1]=INT2NUM(OGRE_VERSION_MAJOR);
	array[2]=INT2NUM(OGRE_VERSION_MINOR);
	array[3]=INT2NUM(OGRE_VERSION_PATCH);
	rb_const_set(rb_mOgre,rb_intern("Version"),rb_f_sprintf(4,array));
	rb_const_set(rb_mOgre,rb_intern("VersionName"),rb_str_new2(OGRE_VERSION_NAME));
}
