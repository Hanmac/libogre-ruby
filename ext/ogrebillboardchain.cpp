#include "ogrebillboardchain.hpp"
#include "ogrebillboardchainelement.hpp"
#include "ogrevector3.hpp"
#include "ogrecolor.hpp"
#include "ogremovableobject.hpp"
#define _self wrap<Ogre::BillboardChain*>(self)
VALUE rb_cOgreBillboardChain;

namespace RubyOgre {
namespace BillboardChain {

macro_attr(MaterialName,Ogre::String)

macro_attr(MaxChainElements,size_t)
macro_attr(NumberOfChains,size_t)

macro_attr(UseTextureCoords,bool)
macro_attr(UseVertexColours,bool)
macro_attr(Dynamic,bool)

/*
*/
VALUE _each(VALUE self,VALUE chain)
{
	RETURN_ENUMERATOR(self,1,&chain);
	for (unsigned int i = 0; i < _self->getNumChainElements(NUM2INT(chain)); ++i)
		rb_yield(wrap(_self->getChainElement(NUM2INT(chain),i)));
	return self;
}

/*
*/
VALUE _add(VALUE self,VALUE chain,VALUE element)
{
	_self->addChainElement(NUM2UINT(chain),wrap<Ogre::BillboardChain::Element>(element));
	return self;
}

/*
*/
VALUE _remove(VALUE self,VALUE chain)
{
	_self->removeChainElement(NUM2UINT(chain));
	return self;
}
/*
*/
VALUE _get(VALUE self,VALUE chain,VALUE index)
{
	if(_self->getNumberOfChains() >= NUM2UINT(chain) || _self->getNumChainElements(NUM2UINT(chain)) >= NUM2UINT(index))
		return Qnil;
	return wrap(_self->getChainElement(NUM2UINT(chain),NUM2UINT(index)));
}

/*
*/
VALUE _set(VALUE self,VALUE chain,VALUE index,VALUE element)
{
	_self->updateChainElement(NUM2UINT(chain),NUM2UINT(index),wrap<Ogre::BillboardChain::Element>(element));
	return element;
}

}}


/*
 * Document-class: Ogre::BillboardChain
 * 
 * This class represents an BillboardChain. 
*/
void Init_OgreBillboardChain(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_mOgreMovableObject = rb_define_module_under(rb_mOgre,"MovableObject");
	
	rb_define_attr(rb_cOgreBillboardChain,"materialname",1,1);
	
	rb_define_attr(rb_cOgreBillboardChain,"maxChainElements",1,1);
	rb_define_attr(rb_cOgreBillboardChain,"numberOfChains",1,1);
	
	rb_define_attr(rb_cOgreBillboardChain,"useTextureCoords",1,1);
	rb_define_attr(rb_cOgreBillboardChain,"useVertexColours",1,1);
	rb_define_attr(rb_cOgreBillboardChain,"dynamic",1,1);
	
#endif
	using namespace RubyOgre::BillboardChain;

	rb_cOgreBillboardChain = rb_define_class_under(rb_mOgre,"BillboardChain",rb_cObject);
	rb_undef_alloc_func(rb_cOgreBillboardChain);
	rb_include_module(rb_cOgreBillboardChain,rb_mOgreMovableObject);
	rb_define_method(rb_cOgreBillboardChain,"each",RUBY_METHOD_FUNC(_each),1);
	rb_include_module(rb_cOgreBillboardChain,rb_mEnumerable);

	rb_define_method(rb_cOgreBillboardChain,"[]",RUBY_METHOD_FUNC(_get),2);
	rb_define_method(rb_cOgreBillboardChain,"[]=",RUBY_METHOD_FUNC(_set),3);
	
	rb_define_method(rb_cOgreBillboardChain,"add",RUBY_METHOD_FUNC(_add),2);
	rb_define_method(rb_cOgreBillboardChain,"remove",RUBY_METHOD_FUNC(_remove),2);
	
	rb_define_attr_method(rb_cOgreBillboardChain,"materialname",_getMaterialName,_setMaterialName);
	
	rb_define_attr_method(rb_cOgreBillboardChain,"maxChainElements",_getMaxChainElements,_setMaxChainElements);
	rb_define_attr_method(rb_cOgreBillboardChain,"numberOfChains",_getNumberOfChains,_setNumberOfChains);
	rb_define_attr_method(rb_cOgreBillboardChain,"useTextureCoords",_getUseTextureCoords,_setUseTextureCoords);
	rb_define_attr_method(rb_cOgreBillboardChain,"useVertexColors",_getUseVertexColours,_setUseVertexColours);
	
	rb_define_attr_method(rb_cOgreBillboardChain,"dynamic",_getDynamic,_setDynamic);

	registerklass<Ogre::BillboardChain>(rb_cOgreBillboardChain);
}
