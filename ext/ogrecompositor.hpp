#ifndef __RubyOgreCompositor_H__
#define __RubyOgreCompositor_H__

#include "main.hpp"
void Init_OgreCompositor(VALUE rb_mOgre);
extern VALUE rb_cOgreCompositor;


template <>
VALUE wrap< Ogre::CompositorPtr >(Ogre::CompositorPtr *compositor );

template <>
Ogre::CompositorPtr wrap< Ogre::CompositorPtr >(const VALUE &vcompositor);

#endif /* __RubyOgreCompositor_H__ */
