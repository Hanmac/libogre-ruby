#include "ogremovableobjectlistener.hpp"
#include "ogremovableobject.hpp"

VALUE rb_mOgreMovableObjectListener;

std::map<VALUE,RubyMovableObjectListener*> movableObjectListenerHolder;


template <>
VALUE wrap< RubyMovableObjectListener >(RubyMovableObjectListener *obj )
{
	return obj->mRuby;
}
template <>
VALUE wrap< Ogre::MovableObject::Listener >(Ogre::MovableObject::Listener *obj )
{
	return wrap<RubyMovableObjectListener>(reinterpret_cast<RubyMovableObjectListener*>(obj));
}
//*/
template <>
Ogre::MovableObject::Listener* wrap< Ogre::MovableObject::Listener* >(const VALUE &vmovable)
{
	std::map<VALUE,RubyMovableObjectListener*>::iterator it = movableObjectListenerHolder.find(vmovable);
	if(it != movableObjectListenerHolder.end())
		return it->second;
	return new RubyMovableObjectListener(vmovable);
}


RubyMovableObjectListener::RubyMovableObjectListener(VALUE val) : mRuby(val)
{
	movableObjectListenerHolder.insert(std::make_pair(val,this));
}


void RubyMovableObjectListener::objectDestroyed(Ogre::MovableObject* obj)
{
	rb_funcall(this->mRuby,rb_intern("object_destroyed"),1,wrap(obj));
}
void RubyMovableObjectListener::objectAttached(Ogre::MovableObject* obj)
{
	rb_funcall(this->mRuby,rb_intern("object_attached"),1,wrap(obj));
}
void RubyMovableObjectListener::objectDetached(Ogre::MovableObject* obj)
{
	rb_funcall(this->mRuby,rb_intern("object_detached"),1,wrap(obj));
}
void RubyMovableObjectListener::objectMoved(Ogre::MovableObject* obj)
{
	rb_funcall(this->mRuby,rb_intern("object_moved"),1,wrap(obj));
}

void Init_OgreMovableObjectListener(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_mOgreMovableObject = rb_define_module_under(rb_mOgre,"MovableObject");
#endif
	rb_mOgreMovableObjectListener = rb_define_module_under(rb_mOgreMovableObject,"Listener");

	rb_define_method(rb_mOgreMovableObjectListener,"object_destroyed",RUBY_METHOD_FUNC(Ogre_dummy1),1);// in ogre.y
	rb_define_method(rb_mOgreMovableObjectListener,"object_attached",RUBY_METHOD_FUNC(Ogre_dummy1),1);// in ogre.y
	rb_define_method(rb_mOgreMovableObjectListener,"object_detached",RUBY_METHOD_FUNC(Ogre_dummy1),1);// in ogre.y
	rb_define_method(rb_mOgreMovableObjectListener,"object_moved",RUBY_METHOD_FUNC(Ogre_dummy1),1);// in ogre.y
}
