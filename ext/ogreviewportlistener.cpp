/*
 * ogreviewportlistener.cpp
 *
 *  Created on: 04.07.2012
 *      Author: hanmac
 */

#include "ogreviewportlistener.hpp"


typedef std::map<VALUE,RubyViewportListener*> ViewportLMap;
ViewportLMap Viewportlistenerholder;

template <>
Ogre::Viewport::Listener* wrap<Ogre::Viewport::Listener*>(const VALUE &listener)
{
	ViewportLMap::iterator it = Viewportlistenerholder.find(listener);
	if(it != Viewportlistenerholder.end())
		return it->second;
	else
		return new RubyViewportListener(listener);

}

RubyViewportListener::RubyViewportListener(VALUE obj) : RubyAny(obj),Ogre::Viewport::Listener() {
	Viewportlistenerholder.insert(std::make_pair(obj,this));
}

RubyViewportListener::~RubyViewportListener() {
	Viewportlistenerholder.erase(value);
}


void RubyViewportListener::viewportCameraChanged(Ogre::Viewport *viewport)
{
	rb_funcall(value,rb_intern("viewport_camera_changed"),1,wrap(viewport));
}

void RubyViewportListener::viewportDimensionsChanged(Ogre::Viewport *viewport)
{
	rb_funcall(value,rb_intern("viewport_dimensions_changed"),1,wrap(viewport));
}

void RubyViewportListener::viewportDestroyed(Ogre::Viewport *viewport)
{
	rb_funcall(value,rb_intern("viewport_destroyed"),1,wrap(viewport));
}

