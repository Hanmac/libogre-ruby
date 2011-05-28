#include "ogreresourcegrouplistener.hpp"
#include "ogreresourcegroup.hpp"
#include "ogreresource.hpp"

VALUE rb_cOgreResourceGroupListener;

VALUE OgreResourceGroupListener_alloc(VALUE self)
{
	RubyResourceGroupListener *temp = new RubyResourceGroupListener;
	temp->mRuby=Qnil;
	return wrap(temp);
}


void RubyResourceGroupListener::resourceGroupScriptingStarted(const Ogre::String &groupName, size_t scriptCount)
{
	rb_funcall(this->mRuby,rb_intern("resourceGroupScriptingStarted"),2,wrap(groupName),ULONG2NUM(scriptCount));
}
void RubyResourceGroupListener::scriptParseStarted (const Ogre::String &scriptName, bool &skipThisScript)
{
	skipThisScript=RTEST(rb_funcall(this->mRuby,rb_intern("scriptParseStarted"),1,wrap(scriptName)));
}
void RubyResourceGroupListener::scriptParseEnded (const Ogre::String &scriptName, bool skipped)
{
	rb_funcall(this->mRuby,rb_intern("scriptParseEnded"),2,wrap(scriptName),skipped ? Qtrue : Qfalse);
}
void RubyResourceGroupListener::resourceGroupScriptingEnded(const Ogre::String &groupName)
{
	rb_funcall(this->mRuby,rb_intern("resourceGroupScriptingEnded"),1,wrap(groupName));
}
void RubyResourceGroupListener::resourceGroupPrepareStarted(const Ogre::String &groupName, size_t resourceCount)
{
	rb_funcall(this->mRuby,rb_intern("resourceGroupPrepareStarted"),2,wrap(groupName),ULONG2NUM(resourceCount));
}
void RubyResourceGroupListener::resourcePrepareStarted(const Ogre::ResourcePtr &resource)
{
	rb_funcall(this->mRuby,rb_intern("resourcePrepareStarted"),1,wrap(resource));
}
void RubyResourceGroupListener::resourcePrepareEnded(void)
{
	rb_funcall(this->mRuby,rb_intern("resourcePrepareEnded"),0);
}
void RubyResourceGroupListener::worldGeometryPrepareStageStarted (const Ogre::String &description)
{
	rb_funcall(this->mRuby,rb_intern("worldGeometryPrepareStageStarted"),1,wrap(description));
}
void RubyResourceGroupListener::worldGeometryPrepareStageEnded (void)
{
	rb_funcall(this->mRuby,rb_intern("resourcePrepareEnded"),0);
}
void RubyResourceGroupListener::resourceGroupPrepareEnded (const Ogre::String &groupName)
{
	rb_funcall(this->mRuby,rb_intern("resourceGroupPrepareEnded"),1,wrap(groupName));
}
void RubyResourceGroupListener::resourceGroupLoadStarted (const Ogre::String &groupName, size_t resourceCount)
{
	rb_funcall(this->mRuby,rb_intern("resourceGroupLoadStarted"),2,wrap(groupName),ULONG2NUM(resourceCount));
}
void RubyResourceGroupListener::resourceLoadStarted(const Ogre::ResourcePtr &resource)
{
	rb_funcall(this->mRuby,rb_intern("resourceLoadStarted"),1,wrap(resource));
}
void RubyResourceGroupListener::resourceLoadEnded (void)
{
	rb_funcall(this->mRuby,rb_intern("resourceLoadEnded"),0);
}
void RubyResourceGroupListener::worldGeometryStageStarted(const Ogre::String &description)
{
	rb_funcall(this->mRuby,rb_intern("worldGeometryStageStarted"),1,wrap(description));
}
void RubyResourceGroupListener::worldGeometryStageEnded(void)
{
	rb_funcall(this->mRuby,rb_intern("worldGeometryStageEnded"),0);
}
void RubyResourceGroupListener::resourceGroupLoadEnded(const Ogre::String &groupName)
{
	rb_funcall(this->mRuby,rb_intern("resourceGroupLoadEnded"),1,wrap(groupName));
}
/*
*/
VALUE scriptParseStarted_dummy(VALUE self,VALUE scriptName)
{
	return Qtrue;
}

void Init_OgreResourceGroupListener(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreResourceGroup = rb_define_class_under(rb_mOgre,"ResourceGroup",rb_cObject);
#endif
	rb_cOgreResourceGroupListener = rb_define_class_under(rb_cOgreResourceGroup,"Listener",rb_cObject);
	rb_define_alloc_func(rb_cOgreResourceGroupListener,OgreResourceGroupListener_alloc);

	rb_define_method(rb_cOgreResourceGroupListener,"resourceGroupScriptingStarted",RUBY_METHOD_FUNC(Ogre_dummy2),2);// in ogre.y
	rb_define_method(rb_cOgreResourceGroupListener,"scriptParseStarted",RUBY_METHOD_FUNC(scriptParseStarted_dummy),1);
	rb_define_method(rb_cOgreResourceGroupListener,"scriptParseEnded",RUBY_METHOD_FUNC(Ogre_dummy2),2);// in ogre.y
	rb_define_method(rb_cOgreResourceGroupListener,"resourceGroupScriptingEnded",RUBY_METHOD_FUNC(Ogre_dummy1),1);// in ogre.y
	rb_define_method(rb_cOgreResourceGroupListener,"resourceGroupPrepareStarted",RUBY_METHOD_FUNC(Ogre_dummy2),2);// in ogre.y
	rb_define_method(rb_cOgreResourceGroupListener,"resourcePrepareStarted",RUBY_METHOD_FUNC(Ogre_dummy1),1);// in ogre.y
	rb_define_method(rb_cOgreResourceGroupListener,"resourcePrepareEnded",RUBY_METHOD_FUNC(Ogre_dummy0),0);// in ogre.y
	rb_define_method(rb_cOgreResourceGroupListener,"worldGeometryPrepareStageStarted",RUBY_METHOD_FUNC(Ogre_dummy1),1);// in ogre.y
	rb_define_method(rb_cOgreResourceGroupListener,"resourcePrepareEnded",RUBY_METHOD_FUNC(Ogre_dummy0),0);// in ogre.y
	rb_define_method(rb_cOgreResourceGroupListener,"resourceGroupPrepareEnded",RUBY_METHOD_FUNC(Ogre_dummy1),1);// in ogre.y
	rb_define_method(rb_cOgreResourceGroupListener,"resourceGroupLoadStarted",RUBY_METHOD_FUNC(Ogre_dummy2),2);// in ogre.y
	rb_define_method(rb_cOgreResourceGroupListener,"resourceLoadStarted",RUBY_METHOD_FUNC(Ogre_dummy1),1);// in ogre.y
	rb_define_method(rb_cOgreResourceGroupListener,"resourceLoadEnded",RUBY_METHOD_FUNC(Ogre_dummy0),0);// in ogre.y
	rb_define_method(rb_cOgreResourceGroupListener,"worldGeometryStageStarted",RUBY_METHOD_FUNC(Ogre_dummy1),1);// in ogre.y
	rb_define_method(rb_cOgreResourceGroupListener,"worldGeometryStageEnded",RUBY_METHOD_FUNC(Ogre_dummy0),0);// in ogre.y
	rb_define_method(rb_cOgreResourceGroupListener,"resourceGroupLoadEnded",RUBY_METHOD_FUNC(Ogre_dummy1),1);// in ogre.y

}
