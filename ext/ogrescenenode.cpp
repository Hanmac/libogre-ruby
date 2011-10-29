#include "ogrenode.hpp"
#include "ogrescenenode.hpp"
//#include "ogrenodelistener.hpp"
#define _self wrap<Ogre::SceneNode*>(self)

VALUE rb_cOgreSceneNode;


/*
*/

void Init_OgreSceneNode(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreSceneNode = rb_define_class_under(rb_mOgre,"SceneNode",rb_cOgreNode);


}
