#include "ogrenode.hpp"
#include "ogrebone.hpp"
//#include "ogrenodelistener.hpp"
#define _self wrap<Ogre::Bone*>(self)

VALUE rb_cOgreBone;

/*
*/

void Init_OgreBone(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreBone = rb_define_class_under(rb_mOgre,"Bone",rb_cOgreNode);

	registerklass<Ogre::Bone>(rb_cOgreBone);
}
