#ifndef __RubyOgreMovableObjectListener_H__
#define __RubyOgreMovableObjectListener_H__

#include "main.hpp"
void Init_OgreMovableObjectListener(VALUE rb_mOgre);
extern VALUE rb_mOgreMovableObjectListener;

class RubyMovableObjectListener : public Ogre::MovableObject::Listener {
	public:
	VALUE mRuby;
	RubyMovableObjectListener(VALUE val);

	void objectDestroyed(Ogre::MovableObject* obj);
	void objectAttached(Ogre::MovableObject* obj);
	void objectDetached(Ogre::MovableObject* obj);
	void objectMoved(Ogre::MovableObject* obj);
};

//*
template <>
VALUE wrap< RubyMovableObjectListener >(RubyMovableObjectListener *obj );
template <>
VALUE wrap< Ogre::MovableObject::Listener >(Ogre::MovableObject::Listener *obj );
//*/
template <>
Ogre::MovableObject::Listener* wrap< Ogre::MovableObject::Listener* >(const VALUE &vmovable);
#endif /* __RubyOgreMovableObject_H__ */
