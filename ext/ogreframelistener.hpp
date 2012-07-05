/*
 * ogreframelistener.hpp
 *
 *  Created on: 03.07.2012
 *      Author: hanmac
 */

#ifndef __RubyOgreFrameListener_H__
#define __RubyOgreFrameListener_H__

#include "main.hpp"
void Init_OgreMovableObjectListener(VALUE rb_mOgre);
extern VALUE rb_mOgreMovableObjectListener;

class RubyFrameListener : public RubyAny,public Ogre::FrameListener {
public:
	RubyFrameListener(VALUE obj);
	~RubyFrameListener();
	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);
};

template <>
Ogre::FrameListener* wrap<Ogre::FrameListener*>(const VALUE &listener);

#endif /* __RubyOgreFrameListener_H__ */
