#include "ogreparticle.hpp"
#include "ogreparticleemitter.hpp"
#include "ogrestringinterface.hpp"
#include "ogreradian.hpp"
#include "ogrecolor.hpp"
#include "ogrevector3.hpp"
#define _self wrap<Ogre::ParticleEmitter*>(self)

VALUE rb_cOgreParticleEmitter;

namespace RubyOgre
{
namespace ParticleEmitter
{

macro_attr(Angle,Ogre::Radian)
macro_attr(Colour,Ogre::ColourValue)

macro_attr(Position,Ogre::Vector3)
macro_attr(Direction,Ogre::Vector3)

macro_attr(Name,Ogre::String)
macro_attr(EmittedEmitter,Ogre::String)

macro_attr(EmissionRate,double)

macro_attr(ColourRangeStart,Ogre::ColourValue)
macro_attr(ColourRangeEnd,Ogre::ColourValue)

singlereturn(getType)

VALUE _getParticleVelocity(VALUE self)
{
	if(_self->getMinParticleVelocity() == _self->getMaxParticleVelocity())
		return DBL2NUM(_self->getParticleVelocity());
	else
		return rb_range_new(DBL2NUM(_self->getMinParticleVelocity()),DBL2NUM(_self->getMaxParticleVelocity()),0);
}
VALUE _setParticleVelocity(VALUE self,VALUE other)
{
	if (!rb_obj_is_kind_of(other, rb_cRange))
		_self->setParticleVelocity(NUM2DBL(other));
	else{
		_self->setMinParticleVelocity(NUM2DBL(rb_funcall(other,rb_intern("begin"),0)));
		_self->setMaxParticleVelocity(NUM2DBL(rb_funcall(other,rb_intern("end"),0)));
	}
	return other;
}


VALUE _getDuration(VALUE self)
{
	if(_self->getMinDuration() == _self->getMaxDuration())
		return DBL2NUM(_self->getDuration());
	else
		return rb_range_new(DBL2NUM(_self->getMinDuration()),DBL2NUM(_self->getMaxDuration()),0);
}
VALUE _setDuration(VALUE self,VALUE other)
{
	if (!rb_obj_is_kind_of(other, rb_cRange))
		_self->setDuration(NUM2DBL(other));
	else{
		_self->setMinDuration(NUM2DBL(rb_funcall(other,rb_intern("begin"),0)));
		_self->setMaxDuration(NUM2DBL(rb_funcall(other,rb_intern("end"),0)));
	}
	return other;
}


VALUE _getTimeToLive(VALUE self)
{
	if(_self->getMinTimeToLive() == _self->getMaxTimeToLive())
		return DBL2NUM(_self->getTimeToLive());
	else
		return rb_range_new(DBL2NUM(_self->getMinTimeToLive()),DBL2NUM(_self->getMaxTimeToLive()),0);
}
VALUE _setTimeToLive(VALUE self,VALUE other)
{
	if (!rb_obj_is_kind_of(other, rb_cRange))
		_self->setTimeToLive(NUM2DBL(other));
	else{
		_self->setMinTimeToLive(NUM2DBL(rb_funcall(other,rb_intern("begin"),0)));
		_self->setMaxTimeToLive(NUM2DBL(rb_funcall(other,rb_intern("end"),0)));
	}
	return other;
}


VALUE _getRepeatDelay(VALUE self)
{
	if(_self->getMinRepeatDelay() == _self->getMaxRepeatDelay())
		return DBL2NUM(_self->getRepeatDelay());
	else
		return rb_range_new(DBL2NUM(_self->getMinRepeatDelay()),DBL2NUM(_self->getMaxRepeatDelay()),0);
}
VALUE _setRepeatDelay(VALUE self,VALUE other)
{
	if (!rb_obj_is_kind_of(other, rb_cRange))
		_self->setRepeatDelay(NUM2DBL(other));
	else{
		_self->setMinRepeatDelay(NUM2DBL(rb_funcall(other,rb_intern("begin"),0)));
		_self->setMaxRepeatDelay(NUM2DBL(rb_funcall(other,rb_intern("end"),0)));
	}
	return other;
}

}}

/*
ParticleVelocity
Duration
TimeToLive
RepeatDelay

*/
void Init_OgreParticleEmitter(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	rb_define_attr(rb_cOgreParticleEmitter,"angle",1,1);

	rb_define_attr(rb_cOgreParticleEmitter,"name",1,1);
	rb_define_attr(rb_cOgreParticleEmitter,"emittedEmitter",1,1);		

	rb_define_attr(rb_cOgreParticleEmitter,"emissionRate",1,1);

	rb_define_attr(rb_cOgreParticleEmitter,"particleVelocity",1,1);
	rb_define_attr(rb_cOgreParticleEmitter,"duration",1,1);
	rb_define_attr(rb_cOgreParticleEmitter,"timeToLive",1,1);
	rb_define_attr(rb_cOgreParticleEmitter,"repeatDelay",1,1);

//TODO min max als range zurück geben?
	rb_define_attr(rb_cOgreParticleEmitter,"colorRangeStart",1,1);
	rb_define_attr(rb_cOgreParticleEmitter,"colorRangeEnd",1,1);
#endif
	using namespace RubyOgre::ParticleEmitter;

	rb_cOgreParticleEmitter = rb_define_class_under(rb_mOgre,"ParticleEmitter",rb_cOgreParticle);
	rb_include_module(rb_cOgreParticleEmitter,rb_mOgreStringInterface);
	//überschreiben der funktion aus particle	
	rb_define_attr_method(rb_cOgreParticleEmitter,"color",_getColour,_setColour);
	rb_define_attr_method(rb_cOgreParticleEmitter,"position",_getPosition,_setPosition);
	rb_define_attr_method(rb_cOgreParticleEmitter,"direction",_getDirection,_setDirection);
	
	rb_define_attr_method(rb_cOgreParticleEmitter,"name",_getName,_setName);

	rb_define_method(rb_cOgreParticleEmitter,"type",RUBY_METHOD_FUNC(_getType),0);

	rb_define_attr_method(rb_cOgreParticleEmitter,"emittedEmitter",_getEmittedEmitter,_setEmittedEmitter);
	rb_define_attr_method(rb_cOgreParticleEmitter,"emissionRate",_getEmissionRate,_setEmissionRate);
	
	rb_define_attr_method(rb_cOgreParticleEmitter,"particleVelocity",_getParticleVelocity,_setParticleVelocity);
	rb_define_attr_method(rb_cOgreParticleEmitter,"duration",_getDuration,_setDuration);
	rb_define_attr_method(rb_cOgreParticleEmitter,"timeToLive",_getTimeToLive,_setTimeToLive);
	rb_define_attr_method(rb_cOgreParticleEmitter,"repeatDelay",_getRepeatDelay,_setRepeatDelay);

	rb_define_attr_method(rb_cOgreParticleEmitter,"angle",_getAngle,_setAngle);
	rb_define_attr_method(rb_cOgreParticleEmitter,"colorRangeStart",_getColourRangeStart,_setColourRangeStart);
	rb_define_attr_method(rb_cOgreParticleEmitter,"colorRangeEnd",_getColourRangeEnd,_setColourRangeEnd);

	registerklass<Ogre::ParticleEmitter>(rb_cOgreParticleEmitter);
}
