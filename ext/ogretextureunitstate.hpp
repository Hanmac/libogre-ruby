#ifndef __RubyOgreTextureUnitState_H__
#define __RubyOgreTextureUnitState_H__

#include "main.hpp"
void Init_OgreTextureUnitState(VALUE rb_mOgre);
extern VALUE rb_cOgreTextureUnitState;


template <>
inline VALUE wrap< Ogre::TextureUnitState >(Ogre::TextureUnitState *textureunitstate )
{
	return Data_Wrap_Struct(rb_cOgreTextureUnitState, NULL, NULL, textureunitstate);
}

template <>
inline Ogre::TextureUnitState* wrap< Ogre::TextureUnitState* >(const VALUE &vtextureunitstate)
{
	if ( ! rb_obj_is_kind_of(vtextureunitstate, rb_cOgreTextureUnitState) )
		return NULL;
	Ogre::TextureUnitState *textureunitstate;
  Data_Get_Struct( vtextureunitstate, Ogre::TextureUnitState, textureunitstate);
	return textureunitstate;
}
#endif /* __RubyOgreTextureUnitState_H__ */
