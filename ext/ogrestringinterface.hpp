#ifndef __RubyOgreStringInterface_H__
#define __RubyOgreStringInterface_H__

#include "main.hpp"
void Init_OgreStringInterface(VALUE rb_mOgre);
extern VALUE rb_mOgreStringInterface;

#include "ogreresource.hpp"
#include "ogreparticlesystem.hpp"
#include "ogreparticleemitter.hpp"
#include "ogreparticleaffector.hpp"

template <>
Ogre::StringInterface* wrap< Ogre::StringInterface* >(const VALUE &interface);

#endif /* __RubyOgreStringInterface_H__ */
