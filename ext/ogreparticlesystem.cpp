#include "ogreparticlesystem.hpp"
#include "ogremovableobject.hpp"
#include "ogrestringinterface.hpp"
#include "ogreparticle.hpp"
#include "ogreparticleemitter.hpp"
#define _self wrap<Ogre::ParticleSystem*>(self)
#define manager Ogre::ParticleSystemManager::getSingletonPtr()
VALUE rb_cOgreParticleSystem;

namespace RubyOgre {
namespace ParticleSystem {

macro_attr(SpeedFactor,double)
macro_attr(IterationInterval,double)
macro_attr(NonVisibleUpdateTimeout,double)
macro_attr(DefaultWidth,double)
macro_attr(DefaultHeight,double)


macro_attr(Emitting,bool)
macro_attr(CullIndividually,bool)
macro_attr(SortingEnabled,bool)
macro_attr(KeepParticlesInLocalSpace,bool)

singlefunc(clear)
/*
*/
VALUE _single_each_affector(VALUE self)
{
	Ogre::ParticleSystemManager::ParticleAffectorFactoryIterator it = manager->getAffectorFactoryIterator();
	wrap_each2a(it.begin(),it.end());
	return self;
}
/*
*/
VALUE _single_each_emitter(VALUE self)
{
	Ogre::ParticleSystemManager::ParticleEmitterFactoryIterator it = manager->getEmitterFactoryIterator();
	wrap_each2a(it.begin(),it.end());
	return self;
}
/*
*/
VALUE _single_each_renderer(VALUE self)
{
	Ogre::ParticleSystemManager::ParticleRendererFactoryIterator it = manager->getRendererFactoryIterator();
	wrap_each2a(it.begin(),it.end());
	return self;
}
/*
*/
VALUE _single_each_template(VALUE self)
{
	wrap< Ogre::String,Ogre::ParticleSystem * >(manager->getTemplateIterator());
	return self;
}

/*
*/
VALUE _addEmitter(VALUE self,VALUE name)
{
	return wrap(_self->addEmitter(wrap<Ogre::String>(name)));
}
/*
*/
VALUE _addAffector(VALUE self,VALUE name)
{
	return wrap(_self->addAffector(wrap<Ogre::String>(name)));
}

/*
*/
VALUE _getEmitter(VALUE self,VALUE id)
{
	return wrap(_self->getEmitter(NUM2UINT(id)));
}
/*
*/
VALUE _getAffector(VALUE self,VALUE id)
{
	return wrap(_self->getAffector(NUM2UINT(id)));
}

/*
*/
VALUE _each_particle(VALUE self)
{
	for (unsigned int i = 0; i < _self->getNumParticles(); ++i)
		rb_yield(wrap(_self->getParticle(i)));
	return self;
}

/*
*/
VALUE _each_emitter(VALUE self)
{
	for (unsigned int i = 0; i < _self->getNumEmitters(); ++i)
		rb_yield(wrap(_self->getEmitter(i)));
	return self;
}
/*
*/
VALUE _each_affector(VALUE self)
{
	for (unsigned int i = 0; i < _self->getNumAffectors(); ++i)
		rb_yield(wrap(_self->getAffector(i)));
	return self;
}


/*
getNumParticles (void) const
 	Gets the number of individual particles in the system right now.
Particle * 	createParticle (void)
 	Manually add a particle to the system.
Particle * 	createEmitterParticle (const String &emitterName)
 	Manually add an emitter particle to the system.
Particle * 	getParticle (size_t index)
*/


VALUE _getMaterialName(VALUE self)
{
	return wrap(_self->getMaterialName());
}
VALUE _setMaterialName(VALUE self,VALUE val)
{
	_self->setMaterialName(wrap<Ogre::String>(val),_self->getResourceGroupName());
	return val;
}

VALUE _getResourceGroupName(VALUE self)
{
	return wrap(_self->getResourceGroupName());
}
VALUE _setResourceGroupName(VALUE self,VALUE val)
{
	_self->setMaterialName(_self->getMaterialName(),wrap<Ogre::String>(val));
	return val;
}


VALUE _getRendererName(VALUE self)
{
	return wrap(_self->getRendererName());
}
VALUE _setRendererName(VALUE self,VALUE val)
{
	_self->setRenderer(wrap<Ogre::String>(val));
	return val;
}

VALUE _getOrigin(VALUE self)
{
	return wrap(_self->getOrigin());
}
VALUE _setOrigin(VALUE self,VALUE val)
{
	_self->_notifyOrigin(wrap<Ogre::String>(val));
	return val;
}

}
}

/*
*/
void Init_OgreParticleSystem(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_mOgreMovableObject = rb_define_module_under(rb_mOgre,"MovableObject");


	rb_define_attr(rb_cOgreParticleSystem,"origin",1,1);

	rb_define_attr(rb_cOgreParticleSystem,"rendererName",1,1);
	rb_define_attr(rb_cOgreParticleSystem,"materialName",1,1);
	rb_define_attr(rb_cOgreParticleSystem,"resourceGroupName",1,1);
	rb_define_attr(rb_cOgreParticleSystem,"speedFactor",1,1);

	rb_define_attr(rb_cOgreParticleSystem,"iterationIntervalr",1,1);
	rb_define_attr(rb_cOgreParticleSystem,"nonVisibleUpdateTimeout",1,1);
	
	rb_define_attr(rb_cOgreParticleSystem,"defaultWidth",1,1);
	rb_define_attr(rb_cOgreParticleSystem,"defaultHeight",1,1);

	rb_define_attr(rb_cOgreParticleSystem,"emitting",1,1);
	rb_define_attr(rb_cOgreParticleSystem,"cullIndividually",1,1);

	rb_define_attr(rb_cOgreParticleSystem,"sortingEnabled",1,1);
	rb_define_attr(rb_cOgreParticleSystem,"keepParticlesInLocalSpace",1,1);


#endif
	using namespace RubyOgre::ParticleSystem;

	rb_cOgreParticleSystem = rb_define_class_under(rb_mOgre,"ParticleSystem",rb_cObject);
	rb_undef_alloc_func(rb_cOgreParticleSystem);
	rb_include_module(rb_cOgreParticleSystem,rb_mOgreMovableObject);
	rb_include_module(rb_cOgreParticleSystem,rb_mOgreStringInterface);
	
	rb_define_method(rb_cOgreParticleSystem,"each_particle",RUBY_METHOD_FUNC(_each_particle),0);
	rb_define_method(rb_cOgreParticleSystem,"each_emitter",RUBY_METHOD_FUNC(_each_emitter),0);
	rb_define_method(rb_cOgreParticleSystem,"each_affector",RUBY_METHOD_FUNC(_each_affector),0);

	rb_define_method(rb_cOgreParticleSystem,"clear",RUBY_METHOD_FUNC(_clear),0);

	rb_define_method(rb_cOgreParticleSystem,"addAffector",RUBY_METHOD_FUNC(_addAffector),1);
	rb_define_method(rb_cOgreParticleSystem,"addEmitter",RUBY_METHOD_FUNC(_addEmitter),1);

	rb_define_method(rb_cOgreParticleSystem,"getAffector",RUBY_METHOD_FUNC(_getAffector),1);
	rb_define_method(rb_cOgreParticleSystem,"getEmitter",RUBY_METHOD_FUNC(_getEmitter),1);

	rb_define_attr_method(rb_cOgreParticleSystem,"origin",_getOrigin,_setOrigin);

	rb_define_attr_method(rb_cOgreParticleSystem,"rendererName",_getRendererName,_setRendererName);
	rb_define_attr_method(rb_cOgreParticleSystem,"materialName",_getMaterialName,_setMaterialName);
	rb_define_attr_method(rb_cOgreParticleSystem,"resourceGroupName",_getResourceGroupName,_setResourceGroupName);
	rb_define_attr_method(rb_cOgreParticleSystem,"speedFactor",_getSpeedFactor,_setSpeedFactor);
	
	rb_define_attr_method(rb_cOgreParticleSystem,"iterationInterval",_getIterationInterval,_setIterationInterval);
	rb_define_attr_method(rb_cOgreParticleSystem,"nonVisibleUpdateTimeout",_getNonVisibleUpdateTimeout,_setNonVisibleUpdateTimeout);
	
	rb_define_attr_method(rb_cOgreParticleSystem,"defaultWidth",_getDefaultWidth,_setDefaultWidth);
	rb_define_attr_method(rb_cOgreParticleSystem,"defaultHeight",_getDefaultHeight,_setDefaultHeight);

	rb_define_attr_method(rb_cOgreParticleSystem,"emitting",_getEmitting,_setEmitting);
	rb_define_attr_method(rb_cOgreParticleSystem,"cullIndividually",_getCullIndividually,_setCullIndividually);
	rb_define_attr_method(rb_cOgreParticleSystem,"sortingEnabled",_getSortingEnabled,_setSortingEnabled);
	rb_define_attr_method(rb_cOgreParticleSystem,"keepParticlesInLocalSpace",_getKeepParticlesInLocalSpace,_setKeepParticlesInLocalSpace);

	rb_define_singleton_method(rb_cOgreParticleSystem,"each_affector",RUBY_METHOD_FUNC(_single_each_affector),0);
	rb_define_singleton_method(rb_cOgreParticleSystem,"each_emitter",RUBY_METHOD_FUNC(_single_each_emitter),0);
	rb_define_singleton_method(rb_cOgreParticleSystem,"each_renderer",RUBY_METHOD_FUNC(_single_each_renderer),0);
	rb_define_singleton_method(rb_cOgreParticleSystem,"each_template",RUBY_METHOD_FUNC(_single_each_template),0);

	registerklass<Ogre::ParticleSystem*>(rb_cOgreParticleSystem);
}
