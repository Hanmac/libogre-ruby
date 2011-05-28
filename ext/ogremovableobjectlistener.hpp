#ifndef __RubyOgreMovableObjectListener_H__
#define __RubyOgreMovableObjectListener_H__

#include "main.hpp"
void Init_OgreMovableObjectListener(VALUE rb_mOgre);
extern VALUE rb_cOgreMovableObjectListener;

class RubyMovableObjectListener : public Ogre::MovableObject::Listener {
	public:
	VALUE mRuby;
	void objectDestroyed(Ogre::MovableObject* obj);
	void objectAttached(Ogre::MovableObject* obj);
	void objectDetached(Ogre::MovableObject* obj);
	void objectMoved(Ogre::MovableObject* obj);
};

//*
template <>
inline VALUE wrap< RubyMovableObjectListener >(RubyMovableObjectListener *obj )
{
	if(obj->mRuby==Qnil)
		obj->mRuby = Data_Wrap_Struct(rb_cOgreMovableObjectListener, NULL, NULL, obj);
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
	if ( ! rb_obj_is_kind_of(vmovable, rb_cOgreMovableObjectListener) )
		return NULL;
	Ogre::MovableObject::Listener *movable;
  Data_Get_Struct( vmovable, Ogre::MovableObject::Listener, movable);
	return movable;
}
#endif /* __RubyOgreMovableObject_H__ */
