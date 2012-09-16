#ifndef __RubyOgreParticleSystem_H__
#define __RubyOgreParticleSystem_H__

#include "main.hpp"
#include <OgreParticleSystem.h>
#include <OgreParticleSystemManager.h>
void Init_OgreParticleSystem(VALUE rb_mOgre);
extern VALUE rb_cOgreParticleSystem;

#include "ogreexception.hpp"

//template <>
//VALUE wrap< Ogre::ParticleSystem >(Ogre::ParticleSystem *ps );
#endif /* __RubyOgreParticleSystem_H__ */


