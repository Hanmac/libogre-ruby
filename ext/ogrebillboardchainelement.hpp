#ifndef __RubyOgreBillboardChainElement_H__
#define __RubyOgreBillboardChainElement_H__

#include "main.hpp"
void Init_OgreBillboardChainElement(VALUE rb_mOgre);
extern VALUE rb_cOgreBillboardChainElement;

template <>
VALUE wrap< Ogre::BillboardChain::Element >(Ogre::BillboardChain::Element *element );

template <>
Ogre::BillboardChain::Element* wrap< Ogre::BillboardChain::Element* >(const VALUE &velement);

template <>
Ogre::BillboardChain::Element wrap< Ogre::BillboardChain::Element >(const VALUE &velement);

#endif /* __RubyOgreBillboardChainElement_H__ */
