#include "ogreloglistener.hpp"
#include "ogrelog.hpp"

VALUE rb_mOgreLogListener;

std::map<VALUE,RubyLogListener*> loglistenerholder;

RubyLogListener::RubyLogListener(VALUE val) : mRuby(val) {
	loglistenerholder.insert(std::make_pair(val,this));
};

void RubyLogListener::messageLogged(const Ogre::String &message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName,bool &skipThisMessage)
{
skipThisMessage = !RTEST(rb_funcall(this->mRuby,rb_intern("messageLogged"),4,wrap(message),wrapenum(lml),maskDebug ? Qtrue : Qfalse,wrap(logName)));
}
void Init_OgreLogListener(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreLog = rb_define_class_under(rb_mOgre,"Log");
#endif
	rb_mOgreLogListener = rb_define_module_under(rb_cOgreLog,"Listener");
	rb_define_method(rb_mOgreLogListener,"messageLogged",RUBY_METHOD_FUNC(Ogre_dummy4),4);// in ogre.y
}
