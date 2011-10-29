#ifndef __RubyOgreNode_H__
#define __RubyOgreNode_H__

#include "main.hpp"
void Init_OgreNode(VALUE rb_mOgre);
extern VALUE rb_cOgreNode;

#include "ogrescenenode.hpp"
#include "ogrebone.hpp"
template <>
inline VALUE wrap< Ogre::Node >(Ogre::Node *obj )
{
	if(obj == NULL)
		return Qnil;
	if(typeid( *obj ) == typeid(Ogre::Node))
		return rb_str_new2(obj->getName().c_str());
	Ogre::SceneNode* scenenode = dynamic_cast<Ogre::SceneNode*>(obj);
	if(scenenode != NULL)
		return wrap(scenenode);
	Ogre::Bone* bone = dynamic_cast<Ogre::Bone*>(obj);
	if(bone != NULL)
		return wrap(bone);

	return Qnil;
}

inline void wrap(Ogre::Node::ChildNodeIterator it )
{
	wrap_each2(it.begin(),it.end());
}


template <>
inline Ogre::Node* wrap< Ogre::Node* >(const VALUE &vnode)
{
	if(!rb_obj_is_kind_of(vnode, rb_cOgreNode))
		return NULL;
	if(rb_obj_is_kind_of(vnode, rb_cOgreSceneNode))
		return wrap<Ogre::SceneNode*>(vnode);	
	if(rb_obj_is_kind_of(vnode, rb_cOgreBone))
		return wrap<Ogre::Bone*>(vnode);	
	return NULL;
}
#endif /* __RubyOgreNode_H__ */
