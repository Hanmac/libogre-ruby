#include "ogrenode.hpp"
//#include "ogrenodelistener.hpp"
#define _self wrap<Ogre::SceneNode*>(self)

VALUE rb_cOgreSceneNode;


/*
*/
VALUE OgreSceneNode_getPosition(VALUE self)
{
	return wrap(_self->getPosition());
}
/*
*/
VALUE OgreSceneNode_setPosition(VALUE self,VALUE other)
{
	_self->setPosition(*wrap<Ogre::Vector3*>(other));
	return other;
}
/*
*/
VALUE OgreSceneNode_getScale(VALUE self)
{
	return wrap(_self->getScale());
}
/*
*/
VALUE OgreSceneNode_setScale(VALUE self,VALUE other)
{
	_self->setScale(*wrap<Ogre::Vector3*>(other));
	return other;
}

void Init_OgreSceneNode(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreSceneNode = rb_define_class_under(rb_mOgre,"SceneNode",rb_cOgreNode);


	rb_define_method(rb_cOgreSceneNode,"position",RUBY_METHOD_FUNC(OgreSceneNode_getPosition),0);
	rb_define_method(rb_cOgreSceneNode,"position=",RUBY_METHOD_FUNC(OgreSceneNode_setPosition),1);
	rb_define_method(rb_cOgreSceneNode,"scale",RUBY_METHOD_FUNC(OgreSceneNode_getScale),0);
	rb_define_method(rb_cOgreSceneNode,"scale=",RUBY_METHOD_FUNC(OgreSceneNode_setScale),1);
}
