#ifndef __RubyOgreLayerBlendMode_H__
#define __RubyOgreLayerBlendMode_H__

#include "main.hpp"
void Init_OgreLayerBlendMode(VALUE rb_mOgre);
extern VALUE rb_cOgreLayerBlendMode;


template <>
inline VALUE wrap< Ogre::LayerBlendModeEx >(Ogre::LayerBlendModeEx *layer )
{
	return Data_Wrap_Struct(rb_cOgreLayerBlendMode, NULL, free, layer);
}
template <>
inline VALUE wrap< Ogre::LayerBlendType >(const Ogre::LayerBlendType &type )
{
	ID id;
	if(type ==Ogre::LBT_ALPHA)
		id = rb_intern("alpha");
	else
		id = rb_intern("color");
	return ID2SYM(id);
}

template <>
inline Ogre::LayerBlendType wrap< Ogre::LayerBlendType >(const VALUE &vtype)
{
	ID id = rb_to_id(vtype);
	if(id==rb_intern("color"))
		return Ogre::LBT_COLOUR;
	else if(id==rb_intern("alpha"))
		return Ogre::LBT_ALPHA;
	else
		return Ogre::LBT_COLOUR;
}

template <>
inline Ogre::LayerBlendModeEx* wrap< Ogre::LayerBlendModeEx* >(const VALUE &vlayer)
{
	if ( ! rb_obj_is_kind_of(vlayer, rb_cOgreLayerBlendMode) )
		return NULL;
	Ogre::LayerBlendModeEx *layer;
  Data_Get_Struct( vlayer, Ogre::LayerBlendModeEx, layer);
	return layer;
}
#endif /* __RubyOgreLayerBlendMode_H__ */
