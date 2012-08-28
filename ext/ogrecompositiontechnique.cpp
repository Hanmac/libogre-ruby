#include "ogrecompositiontechnique.hpp"
#include "ogretexturedefinition.hpp"
#include "ogrecompositor.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::CompositionTechnique*>(self)
VALUE rb_cOgreCompositionTechnique;

namespace RubyOgre {
namespace CompositionTechnique {

macro_attr(SchemeName,Ogre::String)
macro_attr(CompositorLogicName,Ogre::String)

singlereturn(createTargetPass)
singlereturn(getParent)

/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::CompositionTargetPass*>(_self->getTargetPassIterator());
	return self;
}

/*
*/
VALUE _each_texturedefinition(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::CompositionTechnique::TextureDefinition*>(_self->getTextureDefinitionIterator());
	return self;
}

/*
*/
VALUE _createTextureDefinition(VALUE self,VALUE name)
{
	return wrap(_self->createTextureDefinition(wrap<Ogre::String>(name)));
}

}}

void Init_OgreCompositionTechnique(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_define_attr(rb_cOgreCompositionTechnique,"schemename",1,1);
	rb_define_attr(rb_cOgreCompositionTechnique,"compositorlogicname",1,1);
#endif
	using namespace RubyOgre::CompositionTechnique;;

	rb_cOgreCompositionTechnique = rb_define_class_under(rb_mOgre,"CompositionTechnique",rb_cObject);

	rb_define_method(rb_cOgreCompositionTechnique,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cOgreCompositionTechnique,rb_mEnumerable);

	rb_define_method(rb_cOgreCompositionTechnique,"each_texturedefinition",RUBY_METHOD_FUNC(_each_texturedefinition),0);

	rb_define_method(rb_cOgreCompositionTechnique,"create_target_pass",RUBY_METHOD_FUNC(_createTargetPass),0);

	rb_define_method(rb_cOgreCompositionTechnique,"create_texture_definition",RUBY_METHOD_FUNC(_createTextureDefinition),1);

	rb_define_method(rb_cOgreCompositionTechnique,"parent",RUBY_METHOD_FUNC(_getParent),0);

	rb_define_attr_method(rb_cOgreCompositionTechnique,"scheme_name",_getSchemeName,_setSchemeName);
	
	rb_define_attr_method(rb_cOgreCompositionTechnique,"compositor_logicname",_getCompositorLogicName,_setCompositorLogicName);
	
	registerklass<Ogre::CompositionTechnique>(rb_cOgreCompositionTechnique);
}
