#ifndef __RubyOgreParticle_H__
#define __RubyOgreParticle_H__

#include "main.hpp"
void Init_OgreParticle(VALUE rb_mOgre);
extern VALUE rb_cOgreParticle;


template <>
inline VALUE wrap< Ogre::Particle >(Ogre::Particle *particle )
{
	return Data_Wrap_Struct(rb_cOgreParticle, NULL, NULL, particle);
}

template <>
inline Ogre::Particle* wrap< Ogre::Particle* >(const VALUE &vparticle)
{
	if (!rb_obj_is_kind_of(vparticle, rb_cOgreParticle))
		return NULL;
	Ogre::Particle *particle;
  Data_Get_Struct( vparticle, Ogre::Particle, particle);
	return particle;
}
#endif /* __RubyOgreParticle_H__ */
