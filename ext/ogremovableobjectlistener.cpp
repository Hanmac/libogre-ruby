#include "ogremovableobjectlistener.hpp"
#include "ogremovableobject.hpp"

VALUE rb_cOgreMovableObjectListener;

VALUE OgreMovableObjectListener_alloc(VALUE self)
{
	RubyMovableObjectListener *temp = new RubyMovableObjectListener;
	temp->mRuby=Qnil;
	return wrap(temp);
}

void RubyMovableObjectListener::objectDestroyed(Ogre::MovableObject* obj)
{
	rb_warn("%s",typeid(obj).name());
	rb_funcall(this->mRuby,rb_intern("objectDestroyed"),1,wrap(obj));
}
void RubyMovableObjectListener::objectAttached(Ogre::MovableObject* obj)
{
	rb_funcall(this->mRuby,rb_intern("objectAttached"),1,wrap(obj));
}
void RubyMovableObjectListener::objectDetached(Ogre::MovableObject* obj)
{
	rb_funcall(this->mRuby,rb_intern("objectDetached"),1,wrap(obj));
}
void RubyMovableObjectListener::objectMoved(Ogre::MovableObject* obj)
{
	rb_funcall(this->mRuby,rb_intern("objectMoved"),1,wrap(obj));
}
/*
*/
VALUE Ogre_dummy(VALUE self,VALUE obj)
{
	return Qnil;
}
void Init_OgreMovableObjectListener(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_mOgreMovableObject = rb_define_module_under(rb_mOgre,"MovableObject");
#endif
	rb_cOgreMovableObjectListener = rb_define_class_under(rb_mOgreMovableObject,"Listener",rb_cObject);
	rb_define_alloc_func(rb_cOgreMovableObjectListener,OgreMovableObjectListener_alloc);
	rb_define_method(rb_cOgreMovableObjectListener,"objectDestroyed",RUBY_METHOD_FUNC(Ogre_dummy),1);
	rb_define_method(rb_cOgreMovableObjectListener,"objectAttached",RUBY_METHOD_FUNC(Ogre_dummy),1);
	rb_define_method(rb_cOgreMovableObjectListener,"objectDetached",RUBY_METHOD_FUNC(Ogre_dummy),1);
	rb_define_method(rb_cOgreMovableObjectListener,"objectMoved",RUBY_METHOD_FUNC(Ogre_dummy),1);
}
