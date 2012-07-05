/*
 * ogreviewportlistener.hpp
 *
 *  Created on: 04.07.2012
 *      Author: hanmac
 */

#ifndef __RubyOgreViewportListener_H__
#define __RubyOgreViewportListener_H__

#include "main.hpp"
void Init_OgreViewportListener(VALUE rb_mOgre);
extern VALUE rb_mOgreViewportListener;

class RubyViewportListener : public RubyAny,public Ogre::Viewport::Listener {
public:
	RubyViewportListener(VALUE obj);
	~RubyViewportListener();

	void viewportCameraChanged(Ogre::Viewport* viewport);
	void viewportDimensionsChanged(Ogre::Viewport* viewport);
	void viewportDestroyed(Ogre::Viewport* viewport);

};

template <>
Ogre::Viewport::Listener* wrap<Ogre::Viewport::Listener*>(const VALUE &listener);



#endif /* __RubyOgreViewportListener_H__ */
