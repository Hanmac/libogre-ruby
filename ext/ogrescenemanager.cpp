#include "ogrescenemanager.hpp"
#include "ogreexception.hpp"
#include "ogrelight.hpp"
#include "ogrecamera.hpp"
#include "ogreentity.hpp"
#include "ogremesh.hpp"
#include "ogrecolor.hpp"
#include "ogrescenenode.hpp"
#define _self wrap<Ogre::SceneManager*>(self)
VALUE rb_cOgreSceneManager,rb_cOgreSceneManagerMetaData;

template <>
VALUE wrap< Ogre::SceneManagerMetaData >(Ogre::SceneManagerMetaData *manager )
{
	return Data_Wrap_Struct(rb_cOgreSceneManagerMetaData, NULL, free, manager);
}

template <>
VALUE wrap<const Ogre::SceneManagerMetaData >(const Ogre::SceneManagerMetaData *manager )
{
	return Data_Wrap_Struct(rb_cOgreSceneManagerMetaData, NULL, NULL, const_cast<Ogre::SceneManagerMetaData*>(manager));
}


template <>
Ogre::SceneManagerMetaData* wrap< Ogre::SceneManagerMetaData* >(const VALUE &vmanager)
{
	return unwrapPtr<Ogre::SceneManagerMetaData>(vmanager, rb_cOgreSceneManagerMetaData);
}


namespace RubyOgre {
namespace SceneManager {

macro_attr(ShadowColour,Ogre::ColourValue)
macro_attr(AmbientLight,Ogre::ColourValue)


macro_attr(ShadowFarDistance,Ogre::Real)
macro_attr(ShadowIndexBufferSize,bool)
macro_attr(ShadowTextureSelfShadow,bool)
macro_attr(ShadowDirLightTextureOffset,bool)



macro_attr(FindVisibleObjects,bool)
macro_attr(NormaliseNormalsOnScale,bool)
macro_attr(FlipCullingOnNegativeScale,bool)
macro_attr(CameraRelativeRendering,bool)

singlereturn(getRootSceneNode)
singlereturn(getCurrentViewport)
singlereturn(getSkyPlaneNode)
singlereturn(getSkyBoxNode)
singlereturn(getSkyDomeNode)

singlereturn(getDestinationRenderSystem)


/*
 * call-seq:
 *   createLight([name]) -> Light
 * 
 * creates a Light.
*/
VALUE _createLight(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		return wrap(_self->createLight());
	else
		return wrap(_self->createLight(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   getLight(name) -> Light or nil
 * 
 * get a Light or nil
*/
VALUE _getLight(VALUE self,VALUE name)
{
	return wrap(_self->getLight(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   hasLight?(name) -> bool
 * 
 * return true if light with that name exist
*/
VALUE _hasLight(VALUE self,VALUE name)
{
	return wrap(_self->hasLight(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroyLight([name]) -> nil
 * 
 * destroy a Light.
 * if not name is given, destroy all lights
*/
VALUE _destroyLight(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		_self->destroyAllLights();
	else if(rb_obj_is_kind_of(name,rb_cOgreLight))
		_self->destroyLight(wrap<Ogre::Light*>(name));
	else
		_self->destroyLight(wrap<Ogre::String>(name));
	return Qnil;
}

/*
 * call-seq:
 *   createEntity([name]) -> Entity
 *
 * creates a Entity.
*/
VALUE _createEntity(int argc,VALUE *argv,VALUE self)
{
	VALUE mesh,name;
	rb_scan_args(argc, argv, "11",&mesh,&name);

	if(SYMBOL_P(mesh))
	{
		if(NIL_P(name))
			return wrap(_self->createEntity(wrapenum<Ogre::SceneManager::PrefabType>(mesh)));
		else
			return wrap(_self->createEntity(wrap<Ogre::String>(name),wrapenum<Ogre::SceneManager::PrefabType>(mesh)));
	}else if(rb_obj_is_kind_of(mesh,rb_cOgreMesh))
	{
		if(NIL_P(name))
			return wrap(_self->createEntity(wrap<Ogre::MeshPtr>(mesh)));
		else
			return wrap(_self->createEntity(wrap<Ogre::String>(name),wrap<Ogre::MeshPtr>(mesh)));
	}else{
		if(NIL_P(name))
			return wrap(_self->createEntity(wrap<Ogre::String>(mesh)));
		else
			return wrap(_self->createEntity(wrap<Ogre::String>(name),wrap<Ogre::String>(mesh)));
	}
}
/*
 * call-seq:
 *   getEntity(name) -> Entity or nil
 *
 * get a Entity or nil
*/
VALUE _getEntity(VALUE self,VALUE name)
{
	return wrap(_self->getEntity(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   hasEntity?(name) -> bool
 *
 * return true if Entity with that name exist
*/
VALUE _hasEntity(VALUE self,VALUE name)
{
	return wrap(_self->hasEntity(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroyEntity([name]) -> nil
 *
 * destroy a Entity.
 * if not name is given, destroy all Entitys
*/
VALUE _destroyEntity(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		_self->destroyAllEntities();
	else if(rb_obj_is_kind_of(name,rb_cOgreEntity))
		_self->destroyEntity(wrap<Ogre::Entity*>(name));
	else
		_self->destroyEntity(wrap<Ogre::String>(name));
	return Qnil;
}



/*
 * call-seq:
 *   createCamera(name) -> Camera
 * 
 * creates a Camera.
*/
VALUE _createCamera(VALUE self,VALUE name)
{
	return wrap(_self->createCamera(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   getCamera(name) -> Camera or nil
 * 
 * get a Camera or nil
*/
VALUE _getCamera(VALUE self,VALUE name)
{
	return wrap(_self->getCamera(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   hasCamera?(name) -> bool
 * 
 * return true if light with that name exist
*/
VALUE _hasCamera(VALUE self,VALUE name)
{
	return wrap(_self->hasCamera(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroyCamera([name]) -> nil
 * 
 * destroy a Camera.
 * if not name is given, destroy all lights
*/
VALUE _destroyCamera(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		_self->destroyAllCameras();
	else if(rb_obj_is_kind_of(name,rb_cOgreCamera))
		_self->destroyCamera(wrap<Ogre::Camera*>(name));
	else
		_self->destroyCamera(wrap<Ogre::String>(name));
	return Qnil;
}

/*
 * call-seq:
 *   each(type)
 *
*/
VALUE _each_camera(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::String, Ogre::Camera*>(_self->getCameraIterator());
	return self;
}

/*
 * call-seq:
 *   createBillboardChain([name]) -> BillboardChain
 *
 * creates a BillboardChain.
*/
VALUE _createBillboardChain(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		return wrap(_self->createBillboardChain());
	else
		return wrap(_self->createBillboardChain(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   getBillboardChain(name) -> BillboardChain or nil
 *
 * get a BillboardChain or nil
*/
VALUE _getBillboardChain(VALUE self,VALUE name)
{
	return wrap(_self->getBillboardChain(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   hasBillboardChain?(name) -> bool
 *
 * return true if BillboardChain with that name exist
*/
VALUE _hasBillboardChain(VALUE self,VALUE name)
{
	return wrap(_self->hasBillboardChain(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroyBillboardChain([name]) -> nil
 *
 * destroy a Light.
 * if not name is given, destroy all lights
*/
VALUE _destroyBillboardChain(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		_self->destroyAllBillboardChains();
	else if(rb_obj_is_kind_of(name,rb_cOgreLight))
		_self->destroyBillboardChain(wrap<Ogre::BillboardChain*>(name));
	else
		_self->destroyBillboardChain(wrap<Ogre::String>(name));
	return Qnil;
}


/*
 * call-seq:
 *   createRibbonTrail([name]) -> RibbonTrail
 *
 * creates a RibbonTrail.
*/
VALUE _createRibbonTrail(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		return wrap(_self->createRibbonTrail());
	else
		return wrap(_self->createRibbonTrail(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   getRibbonTrail(name) -> RibbonTrail or nil
 *
 * get a RibbonTrail or nil
*/
VALUE _getRibbonTrail(VALUE self,VALUE name)
{
	return wrap(_self->getRibbonTrail(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   hasRibbonTrail?(name) -> bool
 *
 * return true if RibbonTrail with that name exist
*/
VALUE _hasRibbonTrail(VALUE self,VALUE name)
{
	return wrap(_self->hasRibbonTrail(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroyRibbonTrail([name]) -> nil
 *
 * destroy a Light.
 * if not name is given, destroy all lights
*/
VALUE _destroyRibbonTrail(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		_self->destroyAllRibbonTrails();
	else if(rb_obj_is_kind_of(name,rb_cOgreLight))
		_self->destroyRibbonTrail(wrap<Ogre::RibbonTrail*>(name));
	else
		_self->destroyRibbonTrail(wrap<Ogre::String>(name));
	return Qnil;
}



/*
 * call-seq:
 *   createBillboardSet([name]) -> BillboardSet
 *
 * creates a BillboardSet.
*/
VALUE _createBillboardSet(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		return wrap(_self->createBillboardSet());
	else
		return wrap(_self->createBillboardSet(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   getBillboardSet(name) -> BillboardSet or nil
 *
 * get a BillboardSet or nil
*/
VALUE _getBillboardSet(VALUE self,VALUE name)
{
	return wrap(_self->getBillboardSet(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   hasBillboardSet?(name) -> bool
 *
 * return true if BillboardSet with that name exist
*/
VALUE _hasBillboardSet(VALUE self,VALUE name)
{
	return wrap(_self->hasBillboardSet(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroyBillboardSet([name]) -> nil
 *
 * destroy a Light.
 * if not name is given, destroy all lights
*/
VALUE _destroyBillboardSet(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		_self->destroyAllBillboardSets();
	else if(rb_obj_is_kind_of(name,rb_cOgreLight))
		_self->destroyBillboardSet(wrap<Ogre::BillboardSet*>(name));
	else
		_self->destroyBillboardSet(wrap<Ogre::String>(name));
	return Qnil;
}

/*
 * call-seq:
 *   createManualObject([name]) -> ManualObject
 *
 * creates a ManualObject.
*/
VALUE _createManualObject(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		return wrap(_self->createManualObject());
	else
		return wrap(_self->createManualObject(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   getManualObject(name) -> ManualObject or nil
 *
 * get a ManualObject or nil
*/
VALUE _getManualObject(VALUE self,VALUE name)
{
	return wrap(_self->getManualObject(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   hasManualObject?(name) -> bool
 *
 * return true if ManualObject with that name exist
*/
VALUE _hasManualObject(VALUE self,VALUE name)
{
	return wrap(_self->hasManualObject(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroyManualObject([name]) -> nil
 *
 * destroy a Light.
 * if not name is given, destroy all lights
*/
VALUE _destroyManualObject(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		_self->destroyAllManualObjects();
	else if(rb_obj_is_kind_of(name,rb_cOgreLight))
		_self->destroyManualObject(wrap<Ogre::ManualObject*>(name));
	else
		_self->destroyManualObject(wrap<Ogre::String>(name));
	return Qnil;
}


/*
 * call-seq:
 *   createSceneNode([name]) -> Light
 * 
 * creates a Light.
*/
VALUE _createSceneNode(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		return wrap(_self->createSceneNode());
	else
		return wrap(_self->createSceneNode(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   getSceneNode(name) -> SceneNode or nil
 * 
 * get a SceneNode or nil
*/
VALUE _getSceneNode(VALUE self,VALUE name)
{
	return wrap(_self->getSceneNode(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   hasSceneNode?(name) -> bool
 * 
 * return true if SceneNode with that name not exist
*/
VALUE _hasSceneNode(VALUE self,VALUE name)
{
	return wrap(_self->hasSceneNode(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroyLight(name) -> nil
 *
 * destroy a SceneNode.
 * 
*/
VALUE _destroySceneNode(VALUE self,VALUE name)
{
	if(rb_obj_is_kind_of(name,rb_cOgreSceneNode))
		_self->destroySceneNode(wrap<Ogre::SceneNode*>(name));
	else
		_self->destroySceneNode(wrap<Ogre::String>(name));
	return Qnil;
}

/*
 * call-seq:
 *   each(type) 
 * 
*/
VALUE _each(VALUE self,VALUE type)
{
	RETURN_ENUMERATOR(self,1,&type);
	wrap<Ogre::String, Ogre::MovableObject*>(_self->getMovableObjectIterator(wrap<Ogre::String>(type)));
	return self;
}



VALUE _getFogMode(VALUE self)
{
	return wrapenum(_self->getFogMode());
}

singlereturn(getFogColour)
singlereturn(getFogDensity)
singlereturn(getFogStart)
singlereturn(getFogEnd)

VALUE _setFogMode(VALUE self,VALUE val)
{
	_self->setFog(
		wrapenum<Ogre::FogMode>(val),
		_self->getFogColour(),
		_self->getFogDensity(),
		_self->getFogStart(),
		_self->getFogEnd()
	);
	return val;
}

VALUE _setFogColour(VALUE self,VALUE val)
{
	_self->setFog(
		_self->getFogMode(),
		wrap<Ogre::ColourValue>(val),
		_self->getFogDensity(),
		_self->getFogStart(),
		_self->getFogEnd()
	);
	return val;
}

VALUE _setFogDensity(VALUE self,VALUE val)
{
	_self->setFog(
		_self->getFogMode(),
		_self->getFogColour(),
		NUM2DBL(val),
		_self->getFogStart(),
		_self->getFogEnd()
	);
	return val;
}

VALUE _setFogStart(VALUE self,VALUE val)
{
	_self->setFog(
		_self->getFogMode(),
		_self->getFogColour(),
		_self->getFogDensity(),
		NUM2DBL(val),
		_self->getFogEnd()
	);
	return val;
}

VALUE _setFogEnd(VALUE self,VALUE val)
{
	_self->setFog(
		_self->getFogMode(),
		_self->getFogColour(),
		_self->getFogDensity(),
		_self->getFogStart(),
		NUM2DBL(val)
	);
	return val;
}

namespace MetaData {
#undef _self
#define _self wrap<Ogre::SceneManagerMetaData*>(self)

macro_attr_prop(typeName,Ogre::String)
macro_attr_prop(description,Ogre::String)

macro_attr_prop_with_func(sceneTypeMask,LONG2NUM,NUM2LONG)

}


}}


void Init_OgreSceneManager(VALUE rb_mOgre)
{
	#if 0
	rb_mOgre = rb_define_module("Ogre");
	#endif
	using namespace RubyOgre::SceneManager;

	rb_cOgreSceneManager = rb_define_class_under(rb_mOgre,"SceneManager",rb_cObject);
	rb_undef_alloc_func(rb_cOgreSceneManager);
	
	rb_define_method(rb_cOgreSceneManager,"createLight",RUBY_METHOD_FUNC(_createLight),-1);
	rb_define_method(rb_cOgreSceneManager,"getLight",RUBY_METHOD_FUNC(_getLight),1);
	rb_define_method(rb_cOgreSceneManager,"hasLight?",RUBY_METHOD_FUNC(_hasLight),1);
	rb_define_method(rb_cOgreSceneManager,"destroyLight",RUBY_METHOD_FUNC(_destroyLight),-1);

	rb_define_method(rb_cOgreSceneManager,"createEntity",RUBY_METHOD_FUNC(_createEntity),-1);
	rb_define_method(rb_cOgreSceneManager,"getEntity",RUBY_METHOD_FUNC(_getEntity),1);
	rb_define_method(rb_cOgreSceneManager,"hasEntity?",RUBY_METHOD_FUNC(_hasEntity),1);
	rb_define_method(rb_cOgreSceneManager,"destroyEntity",RUBY_METHOD_FUNC(_destroyEntity),-1);

	rb_define_method(rb_cOgreSceneManager,"createBillboardChain",RUBY_METHOD_FUNC(_createBillboardChain),-1);
	rb_define_method(rb_cOgreSceneManager,"getBillboardChain",RUBY_METHOD_FUNC(_getBillboardChain),1);
	rb_define_method(rb_cOgreSceneManager,"hasBillboardChain?",RUBY_METHOD_FUNC(_hasBillboardChain),1);
	rb_define_method(rb_cOgreSceneManager,"destroyBillboardChain",RUBY_METHOD_FUNC(_destroyBillboardChain),-1);

	rb_define_method(rb_cOgreSceneManager,"createBillboardSet",RUBY_METHOD_FUNC(_createBillboardSet),-1);
	rb_define_method(rb_cOgreSceneManager,"getBillboardSet",RUBY_METHOD_FUNC(_getBillboardSet),1);
	rb_define_method(rb_cOgreSceneManager,"hasBillboardSet?",RUBY_METHOD_FUNC(_hasBillboardSet),1);
	rb_define_method(rb_cOgreSceneManager,"destroyBillboardSet",RUBY_METHOD_FUNC(_destroyBillboardSet),-1);

	rb_define_method(rb_cOgreSceneManager,"createRibbonTrail",RUBY_METHOD_FUNC(_createRibbonTrail),-1);
	rb_define_method(rb_cOgreSceneManager,"getRibbonTrail",RUBY_METHOD_FUNC(_getRibbonTrail),1);
	rb_define_method(rb_cOgreSceneManager,"hasRibbonTrail?",RUBY_METHOD_FUNC(_hasRibbonTrail),1);
	rb_define_method(rb_cOgreSceneManager,"destroyRibbonTrail",RUBY_METHOD_FUNC(_destroyRibbonTrail),-1);

	rb_define_method(rb_cOgreSceneManager,"createCamera",RUBY_METHOD_FUNC(_createCamera),1);
	rb_define_method(rb_cOgreSceneManager,"getCamera",RUBY_METHOD_FUNC(_getCamera),1);
	rb_define_method(rb_cOgreSceneManager,"hasCamera?",RUBY_METHOD_FUNC(_hasCamera),1);
	rb_define_method(rb_cOgreSceneManager,"destroyCamera",RUBY_METHOD_FUNC(_destroyCamera),-1);
	
	rb_define_method(rb_cOgreSceneManager,"each_camera",RUBY_METHOD_FUNC(_each_camera),0);

	rb_define_method(rb_cOgreSceneManager,"createSceneNode",RUBY_METHOD_FUNC(_createSceneNode),-1);
	rb_define_method(rb_cOgreSceneManager,"getSceneNode",RUBY_METHOD_FUNC(_getSceneNode),1);
	rb_define_method(rb_cOgreSceneManager,"hasSceneNode?",RUBY_METHOD_FUNC(_hasSceneNode),1);
	rb_define_method(rb_cOgreSceneManager,"destroySceneNode",RUBY_METHOD_FUNC(_destroySceneNode),1);

	rb_define_method(rb_cOgreSceneManager,"rootSceneNode",RUBY_METHOD_FUNC(_getRootSceneNode),0);
	rb_define_method(rb_cOgreSceneManager,"currentViewport",RUBY_METHOD_FUNC(_getCurrentViewport),0);
	rb_define_method(rb_cOgreSceneManager,"skyPlaneNode",RUBY_METHOD_FUNC(_getSkyPlaneNode),0);
	rb_define_method(rb_cOgreSceneManager,"skyBoxNode",RUBY_METHOD_FUNC(_getSkyBoxNode),0);
	rb_define_method(rb_cOgreSceneManager,"skyDomeNode",RUBY_METHOD_FUNC(_getSkyDomeNode),0);
	
	rb_define_attr_method(rb_cOgreSceneManager,"shadowColour",_getShadowColour,_setShadowColour);
	rb_define_attr_method(rb_cOgreSceneManager,"ambientLight",_getAmbientLight,_setAmbientLight);

	rb_define_method(rb_cOgreSceneManager,"each",RUBY_METHOD_FUNC(_each),1);
	rb_include_module(rb_cOgreSceneManager,rb_mEnumerable);


	rb_define_attr_method(rb_cOgreSceneManager,"fog_mode",_getFogMode,_setFogMode);
	rb_define_attr_method(rb_cOgreSceneManager,"fog_color",_getFogColour,_setFogColour);
	rb_define_attr_method(rb_cOgreSceneManager,"fog_density",_getFogDensity,_setFogDensity);
	rb_define_attr_method(rb_cOgreSceneManager,"fog_start",_getFogStart,_setFogStart);
	rb_define_attr_method(rb_cOgreSceneManager,"fog_end",_getFogEnd,_setFogEnd);

	registerklass<Ogre::SceneManager>(rb_cOgreSceneManager);

	rb_cOgreSceneManagerMetaData = rb_define_class_under(rb_cOgreSceneManager,"MetaData",rb_cObject);
	rb_undef_alloc_func(rb_cOgreSceneManagerMetaData);

	rb_define_attr_method(rb_cOgreSceneManagerMetaData,"name",MetaData::_get_typeName,MetaData::_set_typeName);
	rb_define_attr_method(rb_cOgreSceneManagerMetaData,"description",MetaData::_get_description,MetaData::_set_description);
	rb_define_attr_method(rb_cOgreSceneManagerMetaData,"scenetype",MetaData::_get_sceneTypeMask,MetaData::_set_sceneTypeMask);
}
