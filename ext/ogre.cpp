#include "ogrecolor.hpp"
#include "ogrevector3.hpp"
#include "ogreradian.hpp"
#include "ogredegree.hpp"
#include "ogresphere.hpp"
#include "ogreplane.hpp"
#include "ogreresource.hpp"
#include "ogrerect.hpp"
#include "ogrebox.hpp"
#include "ogreimage.hpp"
#include "ogreresourcegroupmanager.hpp"
#include "ogreexception.hpp"
#include "ogrefileinfo.hpp"
#include "ogreresourcegroup.hpp"
#include "ogrepolygon.hpp"
#include "ogredatastream.hpp"
#include "ogreconfigfile.hpp"
VALUE rb_mOgre,rb_mSingleton;
Ogre::Root *root;
extern "C" void Init_ogre(void)
{

	Ogre::LogManager *logManager = new Ogre::LogManager;
	logManager->createLog("", true, false);   // 3rd parameter = false = don't write to stderr
	
	root = new Ogre::Root;
	rb_mOgre = rb_define_module("Ogre");
	rb_require("singleton");
	rb_mSingleton = rb_const_get(rb_cObject,rb_intern("Singleton"));
	//	rb_mSingleton = rb_define_module("Singleton");
	Init_OgreColor(rb_mOgre);
	Init_OgreVector3(rb_mOgre);
	Init_OgreRadian(rb_mOgre);
	Init_OgreDegree(rb_mOgre);
	Init_OgreSphere(rb_mOgre);
	Init_OgrePlane(rb_mOgre);
	Init_OgreResource(rb_mOgre);
	Init_OgreRect(rb_mOgre);
	Init_OgreBox(rb_mOgre);
	Init_OgreImage(rb_mOgre);
	Init_OgreResourceGroupManager(rb_mOgre);
	Init_OgreException(rb_mOgre);
	Init_OgreFileInfo(rb_mOgre);
	Init_OgreResourceGroup(rb_mOgre);
	Init_OgrePolygon(rb_mOgre);
	Init_OgreDataStream(rb_mOgre);
	Init_OgreConfigFile(rb_mOgre);
	
	VALUE array[4];
	array[0]=rb_str_new2("%d.%d.%d");
	array[1]=INT2NUM(OGRE_VERSION_MAJOR);
	array[2]=INT2NUM(OGRE_VERSION_MINOR);
	array[3]=INT2NUM(OGRE_VERSION_PATCH);
	rb_const_set(rb_mOgre,rb_intern("Version"),rb_f_sprintf(4,array));
	rb_const_set(rb_mOgre,rb_intern("VersionName"),rb_str_new2(OGRE_VERSION_NAME));
}
