#ifndef __RubyOgreSceneNode_H__
#define __RubyOgreSceneNode_H__

#include "main.hpp"
void Init_OgreSceneNode(VALUE rb_mOgre);
extern VALUE rb_cOgreSceneNode;

#include "ogreexception.hpp"
struct RubySceneNode {

	Ogre::String man;
	Ogre::String name;
};


template <>
inline VALUE wrap< Ogre::SceneNode >(Ogre::SceneNode *obj )
{

	return Qnil;
}

template <>
inline Ogre::SceneNode* wrap< Ogre::SceneNode* >(const VALUE &vnode)
{
	if ( ! rb_obj_is_kind_of(vnode, rb_cOgreSceneNode) )
		return NULL;
	RubySceneNode *node;
  Data_Get_Struct( vnode, RubySceneNode, node);
  try{
	  Ogre::SceneManager *man = Ogre::Root::getSingletonPtr()->getSceneManager(node->man);
		return man->getSceneNode(node->name);
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
		return NULL;
	}

}
#endif /* __RubyOgreSceneNode_H__ */
