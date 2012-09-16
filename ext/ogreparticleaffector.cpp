#include "ogreparticle.hpp"
#include "ogreparticleaffector.hpp"
#include "ogrestringinterface.hpp"

#define _self wrap<Ogre::ParticleAffector*>(self)

VALUE rb_cOgreParticleAffector;

namespace RubyOgre
{
namespace ParticleAffector
{

singlereturn(getType)

}}

/*

*/
void Init_OgreParticleAffector(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");

#endif
	using namespace RubyOgre::ParticleAffector;

	rb_cOgreParticleAffector = rb_define_class_under(rb_mOgre,"ParticleAffector",rb_cObject);
	rb_include_module(rb_cOgreParticleAffector,rb_mOgreStringInterface);

	rb_define_method(rb_cOgreParticleAffector,"type",RUBY_METHOD_FUNC(_getType),0);
	registerklass<Ogre::ParticleAffector>(rb_cOgreParticleAffector);
}
