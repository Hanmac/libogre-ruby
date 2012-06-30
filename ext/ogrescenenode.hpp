#ifndef __RubyOgreSceneNode_H__
#define __RubyOgreSceneNode_H__

#include "main.hpp"
void Init_OgreSceneNode(VALUE rb_mOgre);
extern VALUE rb_cOgreSceneNode;

template <>
inline Ogre::SceneNode* wrap< Ogre::SceneNode* >(const VALUE &vnode)
{
	return unwrapPtr<Ogre::SceneNode>(vnode, rb_cOgreSceneNode);
}
#endif /* __RubyOgreSceneNode_H__ */
