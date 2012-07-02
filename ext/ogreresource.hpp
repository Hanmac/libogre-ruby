#ifndef __RubyOgreResource_H__
#define __RubyOgreResource_H__

#include "main.hpp"
void Init_OgreResource(VALUE rb_mOgre);
extern VALUE rb_cOgreResource;

#include "ogrematerial.hpp"
#include "ogremesh.hpp"
#include "ogretexture.hpp"
#include "ogrefont.hpp"
#include "ogreskeleton.hpp"
#include "ogrecompositor.hpp"
#include "ogregpuprogram.hpp"


template <>
VALUE wrap< Ogre::ResourcePtr >(const Ogre::ResourcePtr& resource );

template <>
Ogre::Resource* wrap< Ogre::Resource* >(const VALUE &vresource);

template <>
Ogre::ResourceManager* wrap< Ogre::ResourceManager* >(const VALUE &vclass);

Ogre::String unwrapResourceGroup(VALUE obj,const Ogre::String &defaultgroup);

#endif /* __RubyOgreResource_H__ */
