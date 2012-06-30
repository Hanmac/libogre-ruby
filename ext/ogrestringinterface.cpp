#include "ogrestringinterface.hpp"

#define _self wrap<Ogre::StringInterface*>(self)


template <>
Ogre::StringInterface* wrap< Ogre::StringInterface* >(const VALUE &interface)
{
	if(rb_obj_is_kind_of(interface, rb_cOgreResource))
		return wrap< Ogre::Resource* >(interface);
	if(rb_obj_is_kind_of(interface, rb_cOgreParticleSystem))
		return wrap< Ogre::ParticleSystem* >(interface);
	if(rb_obj_is_kind_of(interface, rb_cOgreParticleEmitter))
		return wrap< Ogre::ParticleEmitter* >(interface);
	return NULL;
}


VALUE rb_mOgreStringInterface;
namespace RubyOgre {
namespace StringInterface {

/*
*/
VALUE _getParameter(VALUE self,VALUE name)
{
	return wrap(_self->getParameter(wrap<Ogre::String>(name)));
}

/*
*/
VALUE _setParameter(VALUE self,VALUE name, VALUE val)
{
	_self->setParameter(wrap<Ogre::String>(name),wrap<Ogre::String>(val));
	return self;
}

}
}
/*
*/
void Init_OgreStringInterface(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	using namespace RubyOgre::StringInterface;

	rb_mOgreStringInterface = rb_define_module_under(rb_mOgre,"StringInterface");

	rb_define_method(rb_mOgreStringInterface,"getParameter",RUBY_METHOD_FUNC(_getParameter),1);
	rb_define_method(rb_mOgreStringInterface,"setParameter",RUBY_METHOD_FUNC(_setParameter),2);

}
