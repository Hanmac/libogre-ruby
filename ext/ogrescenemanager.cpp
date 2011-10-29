#include "ogrescenemanager.hpp"
#include "ogreexception.hpp"
#include "ogrelight.hpp"
#include "ogrecamera.hpp"
#include "ogrescenenode.hpp"
#define _self wrap<Ogre::SceneManager*>(self)
#define _meta wrap<Ogre::SceneManagerMetaData*>(meta)
VALUE rb_cOgreSceneManager,rb_cOgreSceneManagerMetaData;

macro_attr(SceneManager,ShadowColour,Ogre::ColourValue)
macro_attr(SceneManager,AmbientLight,Ogre::ColourValue)

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
 * call-seq:
 *   createLight([name]) -> Light
 * 
 * creates a Light.
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
 * call-seq:
 *   getLight(name) -> Light or nil
 * 
 * get a Light or nil
*/
VALUE OgreSceneManager_getLight(VALUE self,VALUE name)
{
	Ogre::Light *light = _self->getLight(rb_string_value_cstr(&name));
	return light ? wrap(light) : Qnil;
}
/*
 * call-seq:
 *   hasLight?(name) -> bool
 * 
 * return true if light with that name not exist
*/
VALUE OgreSceneManager_hasLight(VALUE self,VALUE name)
{
	return _self->hasLight(rb_string_value_cstr(&name)) ? Qtrue : Qfalse;
}

/*
 * call-seq:
 *   destroyLight([name]) -> nil
 * 
 * destroy a Light.
 * if not name is given, destroy all lights
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


/*
 * call-seq:
 *   createCamera([name]) -> Camera
 * 
 * creates a Camera.
*/
VALUE OgreSceneManager_createCamera(VALUE self,VALUE name)
{
	return wrap(_self->createCamera(rb_string_value_cstr(&name)));
}
/*
 * call-seq:
 *   getCamera(name) -> Camera or nil
 * 
 * get a Camera or nil
*/
VALUE OgreSceneManager_getCamera(VALUE self,VALUE name)
{
	Ogre::Camera *light = _self->getCamera(rb_string_value_cstr(&name));
	return light ? wrap(light) : Qnil;
}
/*
 * call-seq:
 *   hasCamera?(name) -> bool
 * 
 * return true if light with that name not exist
*/
VALUE OgreSceneManager_hasCamera(VALUE self,VALUE name)
{
	return _self->hasCamera(rb_string_value_cstr(&name)) ? Qtrue : Qfalse;
}

/*
 * call-seq:
 *   destroyCamera([name]) -> nil
 * 
 * destroy a Camera.
 * if not name is given, destroy all lights
*/
VALUE OgreSceneManager_destroyCamera(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		_self->destroyAllCameras();
	else if(rb_obj_is_kind_of(name,rb_cOgreCamera))
		_self->destroyCamera(wrap<Ogre::Camera*>(name));
	else
		_self->destroyCamera(rb_string_value_cstr(&name));
	return Qnil;
}



/*
 * call-seq:
 *   createSceneNode([name]) -> Light
 * 
 * creates a Light.
*/
VALUE OgreSceneManager_createSceneNode(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		return wrap(_self->createSceneNode());
	else
		return wrap(_self->createSceneNode(rb_string_value_cstr(&name)));
}
/*
 * call-seq:
 *   getSceneNode(name) -> SceneNode or nil
 * 
 * get a SceneNode or nil
*/
VALUE OgreSceneManager_getSceneNode(VALUE self,VALUE name)
{
	Ogre::SceneNode *node = _self->getSceneNode(rb_string_value_cstr(&name));
	return node ? wrap(node) : Qnil;
}
/*
 * call-seq:
 *   hasSceneNode?(name) -> bool
 * 
 * return true if SceneNode with that name not exist
*/
VALUE OgreSceneManager_hasSceneNode(VALUE self,VALUE name)
{
	return _self->hasSceneNode(rb_string_value_cstr(&name)) ? Qtrue : Qfalse;
}

/*
 * call-seq:
 *   destroyLight([name]) -> nil
 * 
 * destroy a Light.
 * if not name is given, destroy all lights
*/
VALUE OgreSceneManager_destroySceneNode(VALUE self,VALUE name)
{
	if(rb_obj_is_kind_of(name,rb_cOgreSceneNode))
		_self->destroySceneNode(wrap<Ogre::SceneNode*>(name));
	else
		_self->destroySceneNode(rb_string_value_cstr(&name));
	return Qnil;
}

/*

*/
VALUE OgreSceneManager_getRootSceneNode(VALUE self)
{
	return wrap(_self->getRootSceneNode());
}
/*

*/
VALUE OgreSceneManager_getCurrentViewport(VALUE self)
{
	return wrap(_self->getCurrentViewport());
}
/*

*/
VALUE OgreSceneManager_getSkyPlaneNode(VALUE self)
{
	return wrap(_self->getSkyPlaneNode());
}
/*

*/
VALUE OgreSceneManager_getSkyBoxNode(VALUE self)
{
	return wrap(_self->getSkyBoxNode());
}
/*

*/
VALUE OgreSceneManager_getSkyDomeNode(VALUE self)
{
	return wrap(_self->getSkyDomeNode());
}
/*
 * call-seq:
 *   each(type) 
 * 
*/
VALUE OgreSceneManager_each(VALUE self,VALUE type)
{
	RETURN_ENUMERATOR(self,1,&type);
	wrap<Ogre::String, Ogre::MovableObject*>(_self->getMovableObjectIterator(rb_string_value_cstr(&type)));
	return self;
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

	
	rb_define_method(rb_cOgreSceneManager,"createCamera",RUBY_METHOD_FUNC(OgreSceneManager_createCamera),1);
	rb_define_method(rb_cOgreSceneManager,"getCamera",RUBY_METHOD_FUNC(OgreSceneManager_getCamera),1);
	rb_define_method(rb_cOgreSceneManager,"hasCamera?",RUBY_METHOD_FUNC(OgreSceneManager_hasCamera),1);
	rb_define_method(rb_cOgreSceneManager,"destroyCamera",RUBY_METHOD_FUNC(OgreSceneManager_destroyCamera),-1);
	
	rb_define_method(rb_cOgreSceneManager,"createSceneNode",RUBY_METHOD_FUNC(OgreSceneManager_createSceneNode),-1);
	rb_define_method(rb_cOgreSceneManager,"getSceneNode",RUBY_METHOD_FUNC(OgreSceneManager_getSceneNode),1);
	rb_define_method(rb_cOgreSceneManager,"hasSceneNode?",RUBY_METHOD_FUNC(OgreSceneManager_hasSceneNode),1);
	rb_define_method(rb_cOgreSceneManager,"destroySceneNode",RUBY_METHOD_FUNC(OgreSceneManager_destroySceneNode),-1);

	rb_define_method(rb_cOgreSceneManager,"rootSceneNode",RUBY_METHOD_FUNC(OgreSceneManager_getRootSceneNode),0);
	rb_define_method(rb_cOgreSceneManager,"currentViewport",RUBY_METHOD_FUNC(OgreSceneManager_getCurrentViewport),0);
	rb_define_method(rb_cOgreSceneManager,"skyPlaneNode",RUBY_METHOD_FUNC(OgreSceneManager_getSkyPlaneNode),0);
	rb_define_method(rb_cOgreSceneManager,"skyBoxNode",RUBY_METHOD_FUNC(OgreSceneManager_getSkyBoxNode),0);
	rb_define_method(rb_cOgreSceneManager,"skyDomeNode",RUBY_METHOD_FUNC(OgreSceneManager_getSkyDomeNode),0);
	
	rb_define_attr_method(rb_cOgreSceneManager,"shadowColour",OgreSceneManager_getShadowColour,OgreSceneManager_setShadowColour);
	rb_define_attr_method(rb_cOgreSceneManager,"ambientLight",OgreSceneManager_getAmbientLight,OgreSceneManager_setAmbientLight);

	rb_define_method(rb_cOgreSceneManager,"each",RUBY_METHOD_FUNC(OgreSceneManager_each),1);

	rb_cOgreSceneManagerMetaData = rb_define_class_under(rb_cOgreSceneManager,"MetaData",rb_cObject);
	
	rb_define_method(rb_cOgreSceneManagerMetaData,"name",RUBY_METHOD_FUNC(OgreSceneManagerMetaData_name),0);
	rb_define_method(rb_cOgreSceneManagerMetaData,"description",RUBY_METHOD_FUNC(OgreSceneManagerMetaData_description),0);
}
