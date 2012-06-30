#ifndef __RubyOgreParticleEmitter_H__
#define __RubyOgreParticleEmitter_H__

#include "main.hpp"
void Init_OgreParticleEmitter(VALUE rb_mOgre);
extern VALUE rb_cOgreParticleEmitter;


template <>
inline VALUE wrap< Ogre::ParticleEmitter >(Ogre::ParticleEmitter *particle )
{
	return Data_Wrap_Struct(rb_cOgreParticleEmitter, NULL, NULL, particle);
}

template <>
inline Ogre::ParticleEmitter* wrap< Ogre::ParticleEmitter* >(const VALUE &vparticle)
{
	if (!rb_obj_is_kind_of(vparticle, rb_cOgreParticleEmitter))
		return NULL;
	Ogre::ParticleEmitter *particle;
  Data_Get_Struct( vparticle, Ogre::ParticleEmitter, particle);
	return particle;
}
#endif /* __RubyOgreParticle_H__ */
