#include "ogrelight.hpp"
#include "ogrecolor.hpp"
#include "ogreradian.hpp"
#include "ogrevector3.hpp"
#include "ogrevector4.hpp"
#include "ogremovableobject.hpp"
#define _self wrap<Ogre::Light*>(self)
VALUE rb_cOgreLight;
namespace RubyOgre
{
namespace Light
{
macro_attr(DiffuseColour,Ogre::ColourValue)
macro_attr(SpecularColour,Ogre::ColourValue)

macro_attr(Position,Ogre::Vector3)
macro_attr(Direction,Ogre::Vector3)

macro_attr(SpotlightInnerAngle,Ogre::Radian)
macro_attr(SpotlightOuterAngle,Ogre::Radian)

macro_attr(SpotlightFalloff,Ogre::Real)
macro_attr(PowerScale,Ogre::Real)


macro_attr(ShadowFarDistance,double)

macro_attr(ShadowNearClipDistance,double)
macro_attr(ShadowFarClipDistance,double)

VALUE _getAttenuationRange(VALUE self)
{
	return DBL2NUM(_self->getAttenuationRange());
}
VALUE _getAttenuationConstant(VALUE self)
{
	return DBL2NUM(_self->getAttenuationConstant());
}
VALUE _getAttenuationLinear(VALUE self)
{
	return DBL2NUM(_self->getAttenuationLinear());
}
VALUE _getAttenuationQuadric(VALUE self)
{
	return DBL2NUM(_self->getAttenuationQuadric());
}

VALUE _setAttenuationRange(VALUE self,VALUE val)
{
	_self->setAttenuation(NUM2DBL(val),_self->getAttenuationConstant(),_self->getAttenuationLinear(),_self->getAttenuationQuadric());
	return val;
}

VALUE _setAttenuationConstant(VALUE self,VALUE val)
{
	_self->setAttenuation(_self->getAttenuationRange(),NUM2DBL(val),_self->getAttenuationLinear(),_self->getAttenuationQuadric());
	return val;
}
VALUE _setAttenuationLinear(VALUE self,VALUE val)
{
	_self->setAttenuation(_self->getAttenuationRange(),_self->getAttenuationConstant(),NUM2DBL(val),_self->getAttenuationQuadric());
	return val;
}
VALUE _setAttenuationQuadric(VALUE self,VALUE val)
{
	_self->setAttenuation(_self->getAttenuationRange(),_self->getAttenuationConstant(),_self->getAttenuationLinear(),NUM2DBL(val));
	return val;
}

/*
*/
VALUE _getCustomParameter(VALUE self,VALUE index)
{
	return wrap(_self->getCustomParameter(NUM2UINT(index)));
}
/*
*/
VALUE _setCustomParameter(VALUE self,VALUE index,VALUE value)
{
	_self->setCustomParameter(NUM2UINT(index),wrap<Ogre::Vector4>(value));
	return self;
}

}}

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
	using namespace RubyOgre::Light;

	rb_cOgreLight = rb_define_class_under(rb_mOgre,"Light",rb_cObject);
	rb_undef_alloc_func(rb_cOgreLight);
	rb_include_module(rb_cOgreLight,rb_mOgreMovableObject);
	
	rb_define_attr_method(rb_cOgreLight,"diffuseColor",_getDiffuseColour,_setDiffuseColour);
	rb_define_attr_method(rb_cOgreLight,"specularColor",_getSpecularColour,_setSpecularColour);
	rb_define_attr_method(rb_cOgreLight,"position",_getPosition,_setPosition);
	rb_define_attr_method(rb_cOgreLight,"direction",_getDirection,_setDirection);

	rb_define_attr_method(rb_cOgreLight,"spotlightInnerAngle",_getSpotlightInnerAngle,_setSpotlightInnerAngle);
	rb_define_attr_method(rb_cOgreLight,"spotlightOuterAngle",_getSpotlightOuterAngle,_setSpotlightOuterAngle);
	
	rb_define_attr_method(rb_cOgreLight,"spotlightFalloff",_getSpotlightFalloff,_setSpotlightFalloff);
	
	rb_define_attr_method(rb_cOgreLight,"powerScale",_getPowerScale,_setPowerScale);
	
	rb_define_method(rb_cOgreLight,"getCustomParameter",RUBY_METHOD_FUNC(_getCustomParameter),1);
	rb_define_method(rb_cOgreLight,"setCustomParameter",RUBY_METHOD_FUNC(_setCustomParameter),2);
	
	rb_define_attr_method(rb_cOgreLight,"attenuationRange",_getAttenuationRange,_setAttenuationRange);
	rb_define_attr_method(rb_cOgreLight,"attenuationConstant",_getAttenuationConstant,_setAttenuationConstant);
	rb_define_attr_method(rb_cOgreLight,"attenuationLinear",_getAttenuationLinear,_setAttenuationLinear);
	rb_define_attr_method(rb_cOgreLight,"attenuationQuadric",_getAttenuationQuadric,_setAttenuationQuadric);

	rb_define_attr_method(rb_cOgreLight,"shadowFarDistance",_getShadowFarDistance,_setShadowFarDistance);
	rb_define_attr_method(rb_cOgreLight,"shadowFarClipDistance",_getShadowFarClipDistance,_setShadowFarClipDistance);
	rb_define_attr_method(rb_cOgreLight,"shadowNearClipDistance",_getShadowNearClipDistance,_setShadowNearClipDistance);

	registerklass<Ogre::Light>(rb_cOgreLight);
}
