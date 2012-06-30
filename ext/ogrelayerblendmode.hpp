#ifndef __RubyOgreLayerBlendMode_H__
#define __RubyOgreLayerBlendMode_H__

#include "main.hpp"
void Init_OgreLayerBlendMode(VALUE rb_mOgre);
extern VALUE rb_cOgreLayerBlendMode;


template <>
VALUE wrap< Ogre::LayerBlendModeEx >(Ogre::LayerBlendModeEx *layer );
#endif /* __RubyOgreLayerBlendMode_H__ */
