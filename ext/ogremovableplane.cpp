#include "ogreplane.hpp"
#include "ogremovableobject.hpp"
#define _self wrap<Ogre::Frustum*>(self)
VALUE rb_cOgreMovablePlane;

namespace RubyOgre {
namespace MovablePlane {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::MovablePlane(""));
}

}
}

/*
 * Document-class: Ogre::MovablePlane
 * 
 * This class represents an MovablePlane.
*/ 

void Init_OgreMovablePlane(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_mOgreMovableObject = rb_define_module_under(rb_mOgre,"MovableObject");
	rb_cOgrePlane = rb_define_class_under(rb_mOgre,"Plane",rb_cObject);
#endif
	using namespace RubyOgre::MovablePlane;

	rb_cOgreMovablePlane = rb_define_class_under(rb_mOgre,"MovablePlane",rb_cOgrePlane);
	rb_undef_alloc_func(rb_cOgreMovablePlane);
	rb_include_module(rb_cOgreMovablePlane,rb_mOgreMovableObject);
	

	registerklass<Ogre::MovablePlane>(rb_cOgreMovablePlane);
}
