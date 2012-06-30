#ifndef __RubyOgreFileInfo_H__
#define __RubyOgreFileInfo_H__

#include "main.hpp"
void Init_OgreFileInfo(VALUE rb_mOgre);
extern VALUE rb_cOgreFileInfo;


template <>
VALUE wrap< Ogre::FileInfo >(Ogre::FileInfo *fileinfo );
#endif /* __RubyOgreFileInfo_H__ */
