#ifndef __RubyOgreLogListener_H__
#define __RubyOgreLogListener_H__

#include "main.hpp"
void Init_OgreLogListener(VALUE rb_mOgre);
extern VALUE rb_cOgreLogListener;

class RubyLogListener : public Ogre::LogListener {
	public:
	VALUE mRuby;
	RubyLogListener(VALUE val);
	void messageLogged(const Ogre::String &message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName,bool &skipThisMessage);
};

extern std::map<VALUE,RubyLogListener*> loglistenerholder;

//*
template <>
inline VALUE wrap< RubyLogListener >(RubyLogListener *obj )
{
	return obj->mRuby;
}
template <>
inline VALUE wrap< Ogre::LogListener >(Ogre::LogListener *obj )
{
	return wrap<RubyLogListener>(reinterpret_cast<RubyLogListener*>(obj));
}
//*/
template <>
inline Ogre::LogListener* wrap< Ogre::LogListener* >(const VALUE &vlog)
{
	std::map<VALUE,RubyLogListener*>::iterator it = loglistenerholder.find(vlog);
	if(it != loglistenerholder.end())
		return it->second;
	return new RubyLogListener(vlog);
}
#endif /* __RubyOgreLog_H__ */
