#ifndef __RubyOgreLog_H__
#define __RubyOgreLog_H__

#include "main.hpp"
#include "ogreexception.hpp"
void Init_OgreLog(VALUE rb_mOgre);
extern VALUE rb_cOgreLog;

template <>
VALUE wrap< Ogre::Log >(Ogre::Log *log );

template <>
Ogre::Log* wrap< Ogre::Log* >(const VALUE &vlog);

template <>
Ogre::LogManager* wrap< Ogre::LogManager* >(const VALUE &vlog);

#endif /* __RubyOgreLog_H__ */
