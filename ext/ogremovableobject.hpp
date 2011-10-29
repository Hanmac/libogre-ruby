#ifndef __RubyOgreMovableObject_H__
#define __RubyOgreMovableObject_H__

#include "main.hpp"
void Init_OgreMovableObject(VALUE rb_mOgre);
extern VALUE rb_mOgreMovableObject;

#include "ogrelight.hpp"
#include "ogreentity.hpp"
#include "ogreparticlesystem.hpp"
#include "ogrebillboardset.hpp"
#include "ogrebillboardchain.hpp"
#include "ogremovableplane.hpp"
#include "ogrefrustum.hpp"
template <>
inline VALUE wrap< Ogre::MovableObject >(Ogre::MovableObject *obj )
{
	if(typeid( *obj ) == typeid(Ogre::MovableObject))
		return rb_str_new2(obj->getName().c_str());
	Ogre::Light* light = dynamic_cast<Ogre::Light*>(obj);
	if(light != NULL)
		return wrap(light);
	Ogre::Entity* entity = dynamic_cast<Ogre::Entity*>(obj);
	if(entity != NULL)
		return wrap(entity);
	Ogre::ParticleSystem* particlesystem = dynamic_cast<Ogre::ParticleSystem*>(obj);
	if(particlesystem != NULL)
		return wrap(particlesystem);
	Ogre::BillboardSet* billboardset = dynamic_cast<Ogre::BillboardSet*>(obj);
	if(billboardset != NULL)
		return wrap(billboardset);
	Ogre::MovablePlane* movableplane = dynamic_cast<Ogre::MovablePlane*>(obj);
	if(movableplane != NULL)
		return wrap(movableplane);
	Ogre::Frustum* frustum = dynamic_cast<Ogre::Frustum*>(obj);
	if(frustum != NULL)
		return wrap(frustum);
	Ogre::BillboardChain* billboardchain = dynamic_cast<Ogre::BillboardChain*>(obj);
	if(billboardchain != NULL)
		return wrap(billboardchain);
	return Qnil;
}

template <>
inline Ogre::MovableObject* wrap< Ogre::MovableObject* >(const VALUE &vmovable)
{
	if ( ! rb_obj_is_kind_of(vmovable, rb_mOgreMovableObject) )
		return NULL;
	RubyMovableObject *movable;
  Data_Get_Struct( vmovable, RubyMovableObject, movable);
  try{
		return Ogre::Root::getSingletonPtr()->getSceneManager(movable->man)->getMovableObject(movable->name,movable->type);
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
		return NULL;
	}
}
#endif /* __RubyOgreMovableObject_H__ */
