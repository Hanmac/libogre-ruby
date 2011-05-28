#include "ogreloglistener.hpp"
#include "ogrelog.hpp"

VALUE rb_cOgreLogListener;

VALUE OgreLogListener_alloc(VALUE self)
{
	RubyLogListener *temp = new RubyLogListener;
	temp->mRuby=Qnil;
	return wrap(temp);
}

void RubyLogListener::messageLogged(const Ogre::String &message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName)
{
	rb_funcall(this->mRuby,rb_intern("messageLogged"),4,wrap(message),wrap(lml),maskDebug ? Qtrue : Qfalse,wrap(logName));
}
void Init_OgreLogListener(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreLog = rb_define_class_under(rb_mOgre,"Log");
#endif
	rb_cOgreLogListener = rb_define_class_under(rb_cOgreLog,"Listener",rb_cObject);
	rb_define_alloc_func(rb_cOgreLogListener,OgreLogListener_alloc);
	rb_define_method(rb_cOgreLogListener,"messageLogged",RUBY_METHOD_FUNC(Ogre_dummy4),4);// in ogre.y
}
