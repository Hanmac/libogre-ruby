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

extern std::map<VALUE,RubyMovableObjectListener*> movableObjectListenerHolder;

//*
template <>
inline VALUE wrap< RubyMovableObjectListener >(RubyMovableObjectListener *obj )
{
	return obj->mRuby;
}
template <>
inline VALUE wrap< Ogre::MovableObject::Listener >(Ogre::MovableObject::Listener *obj )
{
	return wrap<RubyMovableObjectListener>(reinterpret_cast<RubyMovableObjectListener*>(obj));
}
//*/
template <>
inline Ogre::MovableObject::Listener* wrap< Ogre::MovableObject::Listener* >(const VALUE &vmovable)
{
	std::map<VALUE,RubyMovableObjectListener*>::iterator it = movableObjectListenerHolder.find(vmovable);
	if(it != movableObjectListenerHolder.end())
		return it->second;
	return new RubyMovableObjectListener(vmovable);
}
#endif /* __RubyOgreMovableObject_H__ */
