#ifndef __RubyOgreLog_H__
#define __RubyOgreLog_H__

#include "main.hpp"
#include "ogreexception.hpp"
void Init_OgreLog(VALUE rb_mOgre);
extern VALUE rb_cOgreLog;

struct RubyLog{
	Ogre::String name;
};

template <>
inline VALUE wrap< Ogre::Log >(Ogre::Log *log )
{
	RubyLog *temp = new RubyLog;
	temp->name = log->getName();
	return Data_Wrap_Struct(rb_cOgreLog, NULL, NULL, log);
}

template <>
inline Ogre::Log* wrap< Ogre::Log* >(const VALUE &vlog)
{
	if ( ! rb_obj_is_kind_of(vlog, rb_cOgreLog) )
		return NULL;
	try{
		RubyLog *log;
		Data_Get_Struct( vlog, RubyLog, log);
		return Ogre::LogManager::getSingletonPtr()->getLog(log->name);
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
		return NULL;
	}
}
template <>
inline Ogre::LogManager* wrap< Ogre::LogManager* >(const VALUE &vlog)
{
	Ogre::LogManager *temp = Ogre::LogManager::getSingletonPtr();
	return temp != NULL ? temp : new Ogre::LogManager;
}
template <>
inline VALUE wrap< Ogre::LoggingLevel >(const Ogre::LoggingLevel &level )
{
	ID result;
	switch(level){
	case Ogre::LL_LOW:
		result = rb_intern("LL_LOW");
		break;
	case Ogre::LL_NORMAL:
		result = rb_intern("LL_NORMAL");
		break;
	case Ogre::LL_BOREME:
		result = rb_intern("LL_BOREME");
		break;
	default:
		result = rb_intern("LL_LOW");
	}
	return ID2SYM(result);
}

template <>
inline Ogre::LoggingLevel wrap< Ogre::LoggingLevel >(const VALUE &arg)
{
	ID id = rb_to_id(arg);
	if(id==rb_intern("LL_LOW"))
		return Ogre::LL_LOW;
	else if(id==rb_intern("LL_NORMAL"))
		return Ogre::LL_NORMAL;
	else if(id==rb_intern("LL_BOREME"))
		return Ogre::LL_BOREME;
	else
		return Ogre::LL_LOW;
}

#endif /* __RubyOgreLog_H__ */
