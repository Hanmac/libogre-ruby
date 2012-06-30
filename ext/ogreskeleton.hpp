#ifndef __RubyOgreSkeleton_H__
#define __RubyOgreSkeleton_H__

#include "main.hpp"
#include <OgreSkeleton.h>
#include <OgreSkeletonManager.h>
void Init_OgreSkeleton(VALUE rb_mOgre);
extern VALUE rb_cOgreSkeleton;


template <>
VALUE wrap< Ogre::SkeletonPtr >(Ogre::SkeletonPtr *skeleton );

template <>
Ogre::Skeleton* wrap< Ogre::Skeleton* >(const VALUE &vskeleton);

#endif /* __RubyOgreSkeleton_H__ */
