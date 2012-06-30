#include "ogrebillboard.hpp"
#include "ogrecolor.hpp"
#include "ogreradian.hpp"
#include "ogrevector3.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::Billboard*>(self)
VALUE rb_cOgreBillboard;

namespace RubyOgre {
namespace Billboard {

macro_attr(Rotation,Ogre::Radian)
macro_attr(Position,Ogre::Vector3)
macro_attr(Colour,Ogre::ColourValue)

}
}
/*
 * Document-class: Ogre::Billboard
 * 
 * This class represents an Billboard.
*/
void Init_OgreBillboard(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	rb_define_attr(rb_cOgreBillboard,"rotation",1,1);
	rb_define_attr(rb_cOgreBillboard,"position",1,1);
	rb_define_attr(rb_cOgreBillboard,"color",1,1);
#endif
	using namespace RubyOgre::Billboard;

	rb_cOgreBillboard = rb_define_class_under(rb_mOgre,"Billboard",rb_cObject);
	rb_undef_alloc_func(rb_cOgreBillboard);

	rb_define_attr_method(rb_cOgreBillboard,"rotation",_getRotation,_setRotation);
	rb_define_attr_method(rb_cOgreBillboard,"position",_getPosition,_setPosition);
	rb_define_attr_method(rb_cOgreBillboard,"color",_getColour,_setColour);

	registerklass<Ogre::Billboard>(rb_cOgreBillboard);
}
