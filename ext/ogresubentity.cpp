#include "ogresubentity.hpp"
#include "ogrematerial.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::SubEntity*>(self)
VALUE rb_cOgreSubEntity;

namespace RubyOgre {
namespace SubEntity {

macro_attr(MaterialName,Ogre::String)
macro_attr(Material,Ogre::MaterialPtr)
macro_attr_bool(Visible)

singlereturn(getSubMesh)

}}

/*
 * Document-class: Ogre::SubEntity
 * 
 * This class represents an SubEntity.
*/ 

void Init_OgreSubEntity(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_define_attr(rb_cOgreSubEntity,"materialname",1,1);
	rb_define_attr(rb_cOgreSubEntity,"material",1,1);
	rb_define_attr(rb_cOgreSubEntity,"visible",1,1);
#endif
	using namespace RubyOgre::SubEntity;

	rb_cOgreSubEntity = rb_define_class_under(rb_mOgre,"SubEntity",rb_cObject);
	rb_undef_alloc_func(rb_cOgreSubEntity);
	
	rb_define_attr_method(rb_cOgreSubEntity,"materialname",_getMaterialName,_setMaterialName);
	rb_define_attr_method(rb_cOgreSubEntity,"material",_getMaterial,_setMaterial);
	rb_define_attr_method(rb_cOgreSubEntity,"visible",_getVisible,_setVisible);

	rb_define_method(rb_cOgreSubEntity,"mesh",RUBY_METHOD_FUNC(_getSubMesh),0);

	registerklass<Ogre::SubEntity>(rb_cOgreSubEntity);
}
