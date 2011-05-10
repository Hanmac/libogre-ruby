#include "ogrescenemanager.hpp"
#include "ogreexception.hpp"
#include "ogrelight.hpp"
#define _self wrap<Ogre::SceneManager*>(self)
#define _meta wrap<Ogre::SceneManagerMetaData*>(meta)
VALUE rb_cOgreSceneManager,rb_cOgreSceneManagerMetaData;



/*
*/
VALUE OgreSceneManagerMetaData_name(VALUE meta)
{
	return wrap(_meta->typeName);
}
/*
*/
VALUE OgreSceneManagerMetaData_description(VALUE meta)
{
	return wrap(_meta->description);
}


/*
*/
VALUE OgreSceneManager_createLight(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		return wrap(_self->createLight());
	else
		return wrap(_self->createLight(rb_string_value_cstr(&name)));
}
/*
*/
VALUE OgreSceneManager_getLight(VALUE self,VALUE name)
{
	Ogre::Light *light = _self->getLight(rb_string_value_cstr(&name));
	return light ? wrap(light) : Qnil;
}
/*
*/
VALUE OgreSceneManager_hasLight(VALUE self,VALUE name)
{
	return _self->hasLight(rb_string_value_cstr(&name)) ? Qtrue : Qfalse;
}

/*
*/
VALUE OgreSceneManager_destroyLight(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		_self->destroyAllLights();
	else if(rb_obj_is_kind_of(name,rb_cOgreLight))
		_self->destroyLight(wrap<Ogre::Light*>(name));
	else
		_self->destroyLight(rb_string_value_cstr(&name));
	return Qnil;
}

void Init_OgreSceneManager(VALUE rb_mOgre)
{
	#if 0
	rb_mOgre = rb_define_module("Ogre");
	#endif
	rb_cOgreSceneManager = rb_define_class_under(rb_mOgre,"SceneManager",rb_cObject);
	rb_undef_alloc_func(rb_cOgreSceneManager);
	
	rb_define_method(rb_cOgreSceneManager,"createLight",RUBY_METHOD_FUNC(OgreSceneManager_createLight),-1);
	rb_define_method(rb_cOgreSceneManager,"getLight",RUBY_METHOD_FUNC(OgreSceneManager_getLight),1);
	rb_define_method(rb_cOgreSceneManager,"hasLight?",RUBY_METHOD_FUNC(OgreSceneManager_hasLight),1);
	rb_define_method(rb_cOgreSceneManager,"destroyLight",RUBY_METHOD_FUNC(OgreSceneManager_destroyLight),-1);

	rb_cOgreSceneManagerMetaData = rb_define_class_under(rb_cOgreSceneManager,"SceneManagerMetaData",rb_cObject);
	
	rb_define_method(rb_cOgreSceneManagerMetaData,"name",RUBY_METHOD_FUNC(OgreSceneManagerMetaData_name),0);
	rb_define_method(rb_cOgreSceneManagerMetaData,"description",RUBY_METHOD_FUNC(OgreSceneManagerMetaData_description),0);
}
