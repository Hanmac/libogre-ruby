#include "ogreentity.hpp"
#include "ogremesh.hpp"

#include "ogresubentity.hpp"
#include "ogrecolor.hpp"
#include "ogremovableobject.hpp"
#define _self wrap<Ogre::Entity*>(self)
VALUE rb_cOgreEntity;

namespace RubyOgre {
namespace Entity {

macro_attr(DisplaySkeleton,bool)

/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	unsigned int count = _self->getNumSubEntities();
	for (unsigned int i = 0; i < count; ++i)
		rb_yield(wrap(_self->getSubEntity(i)));
	return self;
}

singlereturn(getMesh)

/*
*/
VALUE _each_attached(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::String,Ogre::MovableObject*>(_self->getAttachedObjectIterator());
	return self;
}

}}

/*
 * Document-class: Ogre::Entity
 * 
 * This class represents an Entity. 
*/
void Init_OgreEntity(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_mOgreMovableObject = rb_define_module_under(rb_mOgre,"MovableObject");
#endif
	using namespace RubyOgre::Entity;

	rb_cOgreEntity = rb_define_class_under(rb_mOgre,"Entity",rb_cObject);
	rb_undef_alloc_func(rb_cOgreEntity);
	rb_include_module(rb_cOgreEntity,rb_mOgreMovableObject);
	rb_define_method(rb_cOgreEntity,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cOgreEntity,rb_mEnumerable);
	
	rb_define_method(rb_cOgreEntity,"each_attached",RUBY_METHOD_FUNC(_each_attached),0);

	rb_define_method(rb_cOgreEntity,"mesh",RUBY_METHOD_FUNC(_getMesh),0);

	registerklass<Ogre::Entity>(rb_cOgreEntity);
}
