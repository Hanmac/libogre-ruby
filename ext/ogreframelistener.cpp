/*
 * ogreframelistener.cpp
 *
 *  Created on: 03.07.2012
 *      Author: hanmac
 */

#include "ogreframelistener.hpp"

typedef std::map<VALUE,RubyFrameListener*> FrameLMap;
FrameLMap framelistenerholder;

template <>
Ogre::FrameListener* wrap<Ogre::FrameListener*>(const VALUE &listener)
{
	FrameLMap::iterator it = framelistenerholder.find(listener);
	if(it != framelistenerholder.end())
		return it->second;
	else
		return new RubyFrameListener(listener);

}

RubyFrameListener::RubyFrameListener(VALUE obj) : RubyAny(obj),Ogre::FrameListener() {
	framelistenerholder.insert(std::make_pair(obj,this));
}

RubyFrameListener::~RubyFrameListener() {
	framelistenerholder.erase(value);
}


bool RubyFrameListener::frameStarted(const Ogre::FrameEvent& evt)
{
	return RTEST(rb_funcall(value,rb_intern("frame_started"),2,DBL2NUM(evt.timeSinceLastEvent),DBL2NUM(evt.timeSinceLastEvent)));
}

bool RubyFrameListener::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return RTEST(rb_funcall(value,rb_intern("frame_rendering_queued"),2,DBL2NUM(evt.timeSinceLastEvent),DBL2NUM(evt.timeSinceLastEvent)));
}

bool RubyFrameListener::frameEnded(const Ogre::FrameEvent& evt)
{
	return RTEST(rb_funcall(value,rb_intern("frame_ended"),2,DBL2NUM(evt.timeSinceLastEvent),DBL2NUM(evt.timeSinceLastEvent)));
}
