#include "ogremovableobjectlistener.hpp"
#include "ogremovableobject.hpp"

VALUE rb_mOgreMovableObjectListener;

std::map<VALUE,RubyMovableObjectListener*> movableObjectListenerHolder;

RubyMovableObjectListener::RubyMovableObjectListener(VALUE val) : mRuby(val)
{
	movableObjectListenerHolder.insert(std::make_pair(val,this));
}


void RubyMovableObjectListener::objectDestroyed(Ogre::MovableObject* obj)
{
	rb_funcall(this->mRuby,rb_intern("objectDestroyed"),1,wrap(obj));
}
void RubyMovableObjectListener::objectAttached(Ogre::MovableObject* obj)
{
	rb_funcall(this->mRuby,rb_intern("objectAttached"),1,wrap(obj));
}
void RubyMovableObjectListener::objectDetached(Ogre::MovableObject* obj)
{
	rb_funcall(this->mRuby,rb_intern("objectDetached"),1,wrap(obj));
}
void RubyMovableObjectListener::objectMoved(Ogre::MovableObject* obj)
{
	rb_funcall(this->mRuby,rb_intern("objectMoved"),1,wrap(obj));
}

void Init_OgreMovableObjectListener(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_mOgreMovableObject = rb_define_module_under(rb_mOgre,"MovableObject");
#endif
	rb_mOgreMovableObjectListener = rb_define_module_under(rb_mOgreMovableObject,"Listener");

	rb_define_method(rb_mOgreMovableObjectListener,"objectDestroyed",RUBY_METHOD_FUNC(Ogre_dummy1),1);// in ogre.y
	rb_define_method(rb_mOgreMovableObjectListener,"objectAttached",RUBY_METHOD_FUNC(Ogre_dummy1),1);// in ogre.y
	rb_define_method(rb_mOgreMovableObjectListener,"objectDetached",RUBY_METHOD_FUNC(Ogre_dummy1),1);// in ogre.y
	rb_define_method(rb_mOgreMovableObjectListener,"objectMoved",RUBY_METHOD_FUNC(Ogre_dummy1),1);// in ogre.y
}
