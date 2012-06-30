#ifndef __RubyOgreNode_H__
#define __RubyOgreNode_H__

#include "main.hpp"
void Init_OgreNode(VALUE rb_mOgre);
extern VALUE rb_cOgreNode;
void wrap(Ogre::Node::ChildNodeIterator it );
#endif /* __RubyOgreNode_H__ */
