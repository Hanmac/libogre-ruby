#include "ogrelight.hpp"
#include "ogrecolor.hpp"
#include "ogreradian.hpp"
#include "ogrevector3.hpp"
#include "ogrevector4.hpp"
#include "ogremovableobject.hpp"
#define _self wrap<Ogre::Light*>(self)
VALUE rb_cOgreLight;

macro_attr(Light,DiffuseColour,Ogre::ColourValue)
macro_attr(Light,SpecularColour,Ogre::ColourValue)

macro_attr(Light,Position,Ogre::Vector3)
macro_attr(Light,Direction,Ogre::Vector3)

macro_attr(Light,SpotlightInnerAngle,Ogre::Radian)
macro_attr(Light,SpotlightOuterAngle,Ogre::Radian)

macro_attr_with_func(Light,SpotlightFalloff,INT2NUM,NUM2INT)
macro_attr_with_func(Light,PowerScale,INT2NUM,NUM2INT)


macro_attr_with_func(Light,ShadowFarDistance,DBL2NUM,NUM2DBL)

macro_attr_with_func(Light,ShadowNearClipDistance,DBL2NUM,NUM2DBL)
macro_attr_with_func(Light,ShadowFarClipDistance,DBL2NUM,NUM2DBL)

VALUE OgreLight_getAttenuationRange(VALUE self)
{
	return DBL2NUM(_self->getAttenuationRange());
}
VALUE OgreLight_getAttenuationConstant(VALUE self)
{
	return DBL2NUM(_self->getAttenuationConstant());
}
VALUE OgreLight_getAttenuationLinear(VALUE self)
{
	return DBL2NUM(_self->getAttenuationLinear());
}
VALUE OgreLight_getAttenuationQuadric(VALUE self)
{
	return DBL2NUM(_self->getAttenuationQuadric());
}

VALUE OgreLight_setAttenuationRange(VALUE self,VALUE val)
{
	_self->setAttenuation(NUM2DBL(val),_self->getAttenuationConstant(),_self->getAttenuationLinear(),_self->getAttenuationQuadric());
	return val;
}

VALUE OgreLight_setAttenuationConstant(VALUE self,VALUE val)
{
	_self->setAttenuation(_self->getAttenuationRange(),NUM2DBL(val),_self->getAttenuationLinear(),_self->getAttenuationQuadric());
	return val;
}
VALUE OgreLight_setAttenuationLinear(VALUE self,VALUE val)
{
	_self->setAttenuation(_self->getAttenuationRange(),_self->getAttenuationConstant(),NUM2DBL(val),_self->getAttenuationQuadric());
	return val;
}
VALUE OgreLight_setAttenuationQuadric(VALUE self,VALUE val)
{
	_self->setAttenuation(_self->getAttenuationRange(),_self->getAttenuationConstant(),_self->getAttenuationLinear(),NUM2DBL(val));
	return val;
}

/*
*/
VALUE OgreLight_getCustomParameter(VALUE self,VALUE index)
{
	return wrap(_self->getCustomParameter(NUM2UINT(index)));
}
/*
*/
VALUE OgreLight_setCustomParameter(VALUE self,VALUE index,VALUE value)
{
	_self->setCustomParameter(NUM2UINT(index),wrap<Ogre::Vector4>(value));
	return self;
}
/*
 * Document-class: Ogre::Light
 * 
 * This class represents an Light Source. 
*/ 
/* Document-attr: diffuseColor
 * returns the DiffuseColor of the Light. */
/* Document-attr: specularColor
 * returns the SpecularColor of the Light. */
/* Document-attr: position
 * returns the Position Vector3 of the Light. */
/* Document-attr: direction
 * returns the Direction Vector3 of the Light. */
void Init_OgreLight(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_mOgreMovableObject = rb_define_module_under(rb_mOgre,"MovableObject");
	
	rb_define_attr(rb_cOgreLight,"diffuseColor",1,1);
	rb_define_attr(rb_cOgreLight,"specularColor",1,1);
	rb_define_attr(rb_cOgreLight,"position",1,1);
	rb_define_attr(rb_cOgreLight,"direction",1,1);


	rb_define_attr(rb_cOgreLight,"spotlightInnerAngle",1,1);
	rb_define_attr(rb_cOgreLight,"spotlightOuterAngle",1,1);
	rb_define_attr(rb_cOgreLight,"spotlightFalloff",1,1);

	rb_define_attr(rb_cOgreLight,"powerscale",1,1);
	
	rb_define_attr(rb_cOgreLight,"attenuationRange",1,1);
	rb_define_attr(rb_cOgreLight,"attenuationConstant",1,1);
	rb_define_attr(rb_cOgreLight,"attenuationLinear",1,1);
	rb_define_attr(rb_cOgreLight,"attenuationQuadric",1,1);


	rb_define_attr(rb_cOgreLight,"shadowFarDistance",1,1);
	rb_define_attr(rb_cOgreLight,"shadowFarClipDistance",1,1);
	rb_define_attr(rb_cOgreLight,"shadowNearClipDistance",1,1);


#endif
	rb_cOgreLight = rb_define_class_under(rb_mOgre,"Light",rb_cObject);
	rb_undef_alloc_func(rb_cOgreLight);
	rb_include_module(rb_cOgreLight,rb_mOgreMovableObject);
	
	rb_define_attr_method(rb_cOgreLight,"diffuseColor",OgreLight_getDiffuseColour,OgreLight_setDiffuseColour);
	rb_define_attr_method(rb_cOgreLight,"specularColor",OgreLight_getSpecularColour,OgreLight_setSpecularColour);
	rb_define_attr_method(rb_cOgreLight,"position",OgreLight_getPosition,OgreLight_setPosition);
	rb_define_attr_method(rb_cOgreLight,"direction",OgreLight_getDirection,OgreLight_setDirection);

	rb_define_attr_method(rb_cOgreLight,"spotlightInnerAngle",OgreLight_getSpotlightInnerAngle,OgreLight_setSpotlightInnerAngle);
	rb_define_attr_method(rb_cOgreLight,"spotlightOuterAngle",OgreLight_getSpotlightOuterAngle,OgreLight_setSpotlightOuterAngle);
	
	rb_define_attr_method(rb_cOgreLight,"spotlightFalloff",OgreLight_getSpotlightFalloff,OgreLight_setSpotlightFalloff);
	
	rb_define_attr_method(rb_cOgreLight,"powerScale",OgreLight_getPowerScale,OgreLight_setPowerScale);
	
	rb_define_method(rb_cOgreLight,"getCustomParameter",RUBY_METHOD_FUNC(OgreLight_getCustomParameter),1);
	rb_define_method(rb_cOgreLight,"setCustomParameter",RUBY_METHOD_FUNC(OgreLight_setCustomParameter),2);
	
	rb_define_attr_method(rb_cOgreLight,"attenuationRange",OgreLight_getAttenuationRange,OgreLight_setAttenuationRange);
	rb_define_attr_method(rb_cOgreLight,"attenuationConstant",OgreLight_getAttenuationConstant,OgreLight_setAttenuationConstant);
	rb_define_attr_method(rb_cOgreLight,"attenuationLinear",OgreLight_getAttenuationLinear,OgreLight_setAttenuationLinear);
	rb_define_attr_method(rb_cOgreLight,"attenuationQuadric",OgreLight_getAttenuationQuadric,OgreLight_setAttenuationQuadric);

	rb_define_attr_method(rb_cOgreLight,"shadowFarDistance",OgreLight_getShadowFarDistance,OgreLight_setShadowFarDistance);
	rb_define_attr_method(rb_cOgreLight,"shadowFarClipDistance",OgreLight_getShadowFarClipDistance,OgreLight_setShadowFarClipDistance);
	rb_define_attr_method(rb_cOgreLight,"shadowNearClipDistance",OgreLight_getShadowNearClipDistance,OgreLight_setShadowNearClipDistance);

}
