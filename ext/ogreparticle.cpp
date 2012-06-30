#include "ogreparticle.hpp"
#include "ogreradian.hpp"
#include "ogrecolor.hpp"
#include "ogrevector3.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::Particle*>(self)

VALUE rb_cOgreParticle;

namespace RubyOgre {
namespace Particle {

macro_attr_prop(colour,Ogre::ColourValue)

macro_attr_prop(position,Ogre::Vector3)
macro_attr_prop(direction,Ogre::Vector3)

macro_attr(Rotation,Ogre::Radian)
macro_attr_prop(rotationSpeed,Ogre::Radian)

}}

void Init_OgreParticle(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	rb_define_attr(rb_cOgreParticle,"rotation",1,1);
	rb_define_attr(rb_cOgreParticle,"rotationSpeed",1,1);
	rb_define_attr(rb_cOgreParticle,"color",1,1);

	rb_define_attr(rb_cOgreParticle,"position",1,1);
	rb_define_attr(rb_cOgreParticle,"direction",1,1);

#endif
	using namespace RubyOgre::Particle;

	rb_cOgreParticle = rb_define_class_under(rb_mOgre,"Particle",rb_cObject);
	rb_undef_alloc_func(rb_cOgreParticle);

	rb_define_attr_method(rb_cOgreParticle,"rotation",_getRotation,_setRotation);
	rb_define_attr_method(rb_cOgreParticle,"rotationSpeed",_get_rotationSpeed,_set_rotationSpeed);
	
	rb_define_attr_method(rb_cOgreParticle,"color",_get_colour,_set_colour);

	rb_define_attr_method(rb_cOgreParticle,"position",_get_position,_set_position);
	rb_define_attr_method(rb_cOgreParticle,"direction",_get_direction,_set_direction);
}
