#include "ogrecolor.hpp"
#include "ogrevector3.hpp"
#include "ogreradian.hpp"
#include "ogredegree.hpp"
#include "ogresphere.hpp"
#include "ogreroot.hpp"
#include "ogreplane.hpp"
#include "ogreresource.hpp"
#include "ogrerect.hpp"
#include "ogrebox.hpp"
#include "ogreimage.hpp"
#include "ogreresourcegroupmanager.hpp"
#include "ogreexception.hpp"
#include "ogrefileinfo.hpp"
#include "ogreresourcegroup.hpp"
#include "ogreresourcemanager.hpp"
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
VALUE rb_mOgre,rb_mSingleton;
Ogre::Root *root;


/*

*/
VALUE OgreSingleton_method_missing(int argc,VALUE *argv,VALUE self)
{
	VALUE temp = rb_funcall(self,rb_intern("instance"),0);
	return rb_funcall2(temp,rb_intern("send"),argc,argv);
}

extern "C" void Init_ogre(void)
{

	Ogre::LogManager *logManager = new Ogre::LogManager;
	logManager->createLog("", true, false);   // 3rd parameter = false = don't write to stderr
	
	root = new Ogre::Root();
	

	rb_mOgre = rb_define_module("Ogre");
	rb_require("singleton");
	rb_mSingleton = rb_const_get(rb_cObject,rb_intern("Singleton"));
	Init_OgreRoot(rb_mOgre);
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
	Init_OgreResourceManager(rb_mOgre);
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
	
	
/*TEST
	Ogre::SceneManager *sm = root->createSceneManager("DefaultSceneManager");
	VALUE v = wrap(sm->createLight());
	Ogre::Light* l = wrap<Ogre::Light*>(v);

	RubyMovableObjectListener *temp = new RubyMovableObjectListener;
	temp->mRuby=Qnil;
	wrap(temp);
	l->setListener((Ogre::MovableObject::Listener*)temp);
	sm->destroyLight(l);
//*/
	VALUE array[4];
	array[0]=rb_str_new2("%d.%d.%d");
	array[1]=INT2NUM(OGRE_VERSION_MAJOR);
	array[2]=INT2NUM(OGRE_VERSION_MINOR);
	array[3]=INT2NUM(OGRE_VERSION_PATCH);
	rb_const_set(rb_mOgre,rb_intern("Version"),rb_f_sprintf(4,array));
	rb_const_set(rb_mOgre,rb_intern("VersionName"),rb_str_new2(OGRE_VERSION_NAME));
}
