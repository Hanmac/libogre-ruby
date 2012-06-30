#include "ogrebillboardchain.hpp"
#include "ogrebillboardchainelement.hpp"
#include "ogrevector3.hpp"
#include "ogrecolor.hpp"
#include "ogrequaternion.hpp"
#define _self wrap<Ogre::BillboardChain::Element*>(self)
VALUE rb_cOgreBillboardChainElement;

template <>
VALUE wrap< Ogre::BillboardChain::Element >(Ogre::BillboardChain::Element *element )
{
	return Data_Wrap_Struct(rb_cOgreBillboardChainElement, NULL, free, element);
}

template <>
Ogre::BillboardChain::Element* wrap< Ogre::BillboardChain::Element* >(const VALUE &velement)
{
	return unwrapPtr<Ogre::BillboardChain::Element>(velement, rb_cOgreBillboardChainElement);
}

template <>
Ogre::BillboardChain::Element wrap< Ogre::BillboardChain::Element >(const VALUE &velement)
{
	return *wrap<Ogre::BillboardChain::Element*>(velement);
}

namespace RubyOgre {
namespace BillboardChainElement {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::BillboardChain::Element);
}


macro_attr_prop(position,Ogre::Vector3)
macro_attr_prop(colour,Ogre::ColourValue)

macro_attr_prop(width,double)
macro_attr_prop(texCoord,double)

macro_attr_prop(orientation,Ogre::Quaternion)


}}

/*
 * Document-class: Ogre::BillboardChain::Element
 * 
 * This class represents an BillboardChainElement.
*/
void Init_OgreBillboardChainElement(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");

	
	rb_define_attr(rb_cOgreBillboardChainElement,"position",1,1);
	rb_define_attr(rb_cOgreBillboardChainElement,"color",1,1);
	
	rb_define_attr(rb_cOgreBillboardChainElement,"width",1,1);
	rb_define_attr(rb_cOgreBillboardChainElement,"texCoord",1,1);
	
	rb_define_attr(rb_cOgreBillboardChainElement,"orientation",1,1);

	rb_cOgreBillboardChain = rb_define_class_under(rb_mOgre,"BillboardChain",rb_cObject);
#endif
	using namespace RubyOgre::BillboardChainElement;

	rb_cOgreBillboardChainElement = rb_define_class_under(rb_cOgreBillboardChain,"Element",rb_cObject);
	rb_define_alloc_func(rb_cOgreBillboardChainElement,_alloc);
	rb_define_attr_method(rb_cOgreBillboardChainElement,"position",_get_position,_set_position);
	rb_define_attr_method(rb_cOgreBillboardChainElement,"color",_get_colour,_set_colour);

	rb_define_attr_method(rb_cOgreBillboardChainElement,"width",_get_width,_set_width);
	rb_define_attr_method(rb_cOgreBillboardChainElement,"texCoord",_get_texCoord,_set_texCoord);

	rb_define_attr_method(rb_cOgreBillboardChainElement,"orientation",_get_orientation,_set_orientation);

}
