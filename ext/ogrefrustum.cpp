#include "ogrefrustum.hpp"
#include "ogreexception.hpp"
#include "ogremovableobject.hpp"
#include "ogrevector2.hpp"
#include "ogreradian.hpp"
#define _self wrap<Ogre::Frustum*>(self)
VALUE rb_cOgreFrustum;

namespace RubyOgre
{
namespace Frustum
{

macro_attr(FrustumOffset,Ogre::Vector2)
macro_attr(FOVy,Ogre::Radian)

macro_attr(NearClipDistance,double)
macro_attr(FarClipDistance,double)
macro_attr(AspectRatio,double)
macro_attr(FocalLength,double)

macro_attr(OrthoWindowHeight,double)
macro_attr(OrthoWindowWidth,double)


}
}

/*
 * Document-class: Ogre::Frustum
 * 
 * This class represents an Frustum.
*/ 

void Init_OgreFrustum(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_mOgreMovableObject = rb_define_module_under(rb_mOgre,"MovableObject");
	
	rb_define_attr(rb_cOgreFrustum,"frustumOffset",1,1);
	rb_define_attr(rb_cOgreFrustum,"fovy",1,1);
	rb_define_attr(rb_cOgreFrustum,"nearClipDistance",1,1);
	rb_define_attr(rb_cOgreFrustum,"farClipDistance",1,1);
	rb_define_attr(rb_cOgreFrustum,"aspectRatio",1,1);
	rb_define_attr(rb_cOgreFrustum,"focalLength",1,1);

	rb_define_attr(rb_cOgreFrustum,"orthoWindowHeight",1,1);
	rb_define_attr(rb_cOgreFrustum,"orthoWindowWidth",1,1);

#endif
	using namespace RubyOgre::Frustum;
	rb_cOgreFrustum = rb_define_class_under(rb_mOgre,"Frustum",rb_cObject);

	rb_include_module(rb_cOgreFrustum,rb_mOgreMovableObject);
	
	rb_define_attr_method(rb_cOgreFrustum,"frustumOffset",_getFrustumOffset,_setFrustumOffset);
	rb_define_attr_method(rb_cOgreFrustum,"fovy",_getFOVy,_setFOVy);
	
	rb_define_attr_method(rb_cOgreFrustum,"nearClipDistance",_getNearClipDistance,_setNearClipDistance);
	rb_define_attr_method(rb_cOgreFrustum,"farClipDistance",_getFarClipDistance,_setFarClipDistance);
	rb_define_attr_method(rb_cOgreFrustum,"aspectRatio",_getAspectRatio,_setAspectRatio);
	rb_define_attr_method(rb_cOgreFrustum,"focalLength",_getFocalLength,_setFocalLength);
	
	rb_define_attr_method(rb_cOgreFrustum,"orthoWindowHeight",_getOrthoWindowHeight,_setOrthoWindowHeight);
	rb_define_attr_method(rb_cOgreFrustum,"orthoWindowWidth",_getOrthoWindowWidth,_setOrthoWindowWidth);

	registerklass<Ogre::Frustum>(rb_cOgreFrustum);
}
