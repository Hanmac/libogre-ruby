#include "ogrenode.hpp"
#include "ogrescenenode.hpp"
//#include "ogrenodelistener.hpp"
#define _self wrap<Ogre::SceneNode*>(self)

VALUE rb_cOgreSceneNode;


void wrap(Ogre::SceneNode::ObjectIterator it )
{
	wrap_each2(it.begin(),it.end());
}


namespace RubyOgre {
namespace SceneNode {

/*
*/
VALUE _each_attached(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap(_self->getAttachedObjectIterator());
	return self;
}

VALUE _attach(VALUE self,VALUE obj)
{
	_self->attachObject(wrap<Ogre::MovableObject*>(obj));
	return self;
}

VALUE _getAttachedObject(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val,rb_cString))
		return wrap(_self->getAttachedObject(wrap<Ogre::String>(val)));
	else if(_self->numAttachedObjects()	< NUM2UINT(val))
		return wrap(_self->getAttachedObject(NUM2UINT(val)));
	else
		return Qnil;
}

}
}
/*
*/

void Init_OgreSceneNode(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	using namespace RubyOgre::SceneNode;

	rb_cOgreSceneNode = rb_define_class_under(rb_mOgre,"SceneNode",rb_cOgreNode);

	registerklass<Ogre::SceneNode>(rb_cOgreSceneNode);
	rb_define_method(rb_cOgreSceneNode,"attach",RUBY_METHOD_FUNC(_attach),1);
}
