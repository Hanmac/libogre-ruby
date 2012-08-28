#ifndef __RubyOgreDataStream_H__
#define __RubyOgreDataStream_H__

#include "main.hpp"
void Init_OgreDataStream(VALUE rb_mOgre);
extern VALUE rb_cOgreDataStream;

template <>
VALUE wrap< Ogre::DataStreamPtr >(Ogre::DataStreamPtr *datastream );

template <>
VALUE wrap< Ogre::DataStreamListPtr >(const Ogre::DataStreamListPtr &vec );

template <>
Ogre::DataStreamPtr wrap< Ogre::DataStreamPtr >(const VALUE &vdatastream);
#endif /* __RubyOgreDataStream_H__ */
