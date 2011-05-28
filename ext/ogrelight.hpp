#ifndef __RubyOgreLight_H__
#define __RubyOgreLight_H__

#include "main.hpp"
void Init_OgreLight(VALUE rb_mOgre);
extern VALUE rb_cOgreLight;
#include "ogreexception.hpp"
#include "ogremovableobject_impl.hpp"
template <>
inline VALUE wrap< Ogre::Light >(Ogre::Light *light )
{
	RubyMovableObject *temp = new RubyMovableObject;
	temp->man = light->_getManager()->getName();
	temp->type = light->getMovableType();
	temp->name = light->getName();
	return Data_Wrap_Struct(rb_cOgreLight, NULL, free, temp);
}

template <>
inline Ogre::Light* wrap< Ogre::Light* >(const VALUE &vlight)
{
	if ( ! rb_obj_is_kind_of(vlight, rb_cOgreLight) )
		return NULL;
	RubyMovableObject *light;
  Data_Get_Struct( vlight, RubyMovableObject, light);
  try{
    return Ogre::Root::getSingletonPtr()->getSceneManager(light->man)->getLight(light->name);
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
		return NULL;
	}
}
#endif /* __RubyOgreLight_H__ */
