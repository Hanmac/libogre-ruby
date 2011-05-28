#ifndef __RubyOgreLogListener_H__
#define __RubyOgreLogListener_H__

#include "main.hpp"
void Init_OgreLogListener(VALUE rb_mOgre);
extern VALUE rb_cOgreLogListener;

class RubyLogListener : public Ogre::LogListener {
	public:
	VALUE mRuby;
	void messageLogged(const Ogre::String &message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName);
};

//*
template <>
inline VALUE wrap< RubyLogListener >(RubyLogListener *obj )
{
	if(obj->mRuby==Qnil)
		obj->mRuby = Data_Wrap_Struct(rb_cOgreLogListener, NULL, NULL, obj);
	return obj->mRuby;
}
template <>
inline VALUE wrap< Ogre::LogListener >(Ogre::LogListener *obj )
{
	return wrap<RubyLogListener>(reinterpret_cast<RubyLogListener*>(obj));
}
//*/
template <>
inline Ogre::LogListener* wrap< Ogre::LogListener* >(const VALUE &vmovable)
{
	if ( ! rb_obj_is_kind_of(vmovable, rb_cOgreLogListener) )
		return NULL;
	Ogre::LogListener *movable;
  Data_Get_Struct( vmovable, Ogre::LogListener, movable);
	return movable;
}
#endif /* __RubyOgreLog_H__ */
