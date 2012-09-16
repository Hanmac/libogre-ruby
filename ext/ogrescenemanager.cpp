
#include "ogrescenemanager.hpp"
#include "ogreexception.hpp"
#include "ogrelight.hpp"
#include "ogrecamera.hpp"
#include "ogreentity.hpp"
#include "ogremesh.hpp"
#include "ogrematerial.hpp"
#include "ogrecolor.hpp"
#include "ogrevector3.hpp"
#include "ogrescenenode.hpp"
#include "ogremovableobject.hpp"

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
 *   create_light([name]) -> Light
 * 
 * creates a Light.
*/
VALUE _createLight(int argc,VALUE *argv,VALUE self)
{
	VALUE name,opt;
	Ogre::Light *result;
	RUBYTRY(

	rb_scan_args(argc, argv, "02",&name,&opt);

	if(rb_obj_is_kind_of(name,rb_cHash))
		std::swap(name,opt);

	if(NIL_P(name))
		result = _self->createLight();
	else
		result = _self->createLight(wrap<Ogre::String>(name));

	if(rb_obj_is_kind_of(opt,rb_cHash))
	{
		VALUE temp;
		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("type")))))
			result->setType(wrapenum<Ogre::Light::LightTypes>(temp));

		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("position")))))
			result->setPosition(wrap<Ogre::Vector3>(temp));

		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("direction")))))
			result->setDirection(wrap<Ogre::Vector3>(temp));

		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("diffuse_color")))))
			result->setDiffuseColour(wrap<Ogre::ColourValue>(temp));

		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("specular_color")))))
			result->setSpecularColour(wrap<Ogre::ColourValue>(temp));

		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("visibility_flags")))))
			result->setVisibilityFlags(NUM2ULONG(temp));

	}

	return wrap(result);
	)
	return Qnil;
}
/*
 * call-seq:
 *   get_light(name) -> Light or nil
 * 
 * get a Light or nil
*/
VALUE _getLight(VALUE self,VALUE name)
{
	return wrap(_self->getLight(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   has_light?(name) -> bool
 * 
 * return true if light with that name exist
*/
VALUE _hasLight(VALUE self,VALUE name)
{
	return wrap(_self->hasLight(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroy_light([name]) -> nil
 * 
 * destroy a Light.
 * if not name is given, destroy all lights
*/
VALUE _destroyLight(int argc,VALUE *argv,VALUE self)
{
	RUBYTRY(
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	if(NIL_P(name))
		_self->destroyAllLights();
	else if(rb_obj_is_kind_of(name,rb_cOgreLight))
		_self->destroyLight(wrap<Ogre::Light*>(name));
	else
		_self->destroyLight(wrap<Ogre::String>(name));
	)
	return Qnil;
}

/*
 * call-seq:
 *   create_entity([name]) -> Entity
 *
 * creates a Entity.
*/
VALUE _createEntity(int argc,VALUE *argv,VALUE self)
{

	VALUE mesh,name,opt;
	rb_scan_args(argc, argv, "12",&mesh,&name,&opt);

	if(rb_obj_is_kind_of(name,rb_cHash))
		std::swap(name,opt);

	RUBYTRY(
		Ogre::Entity *result;
		if(SYMBOL_P(mesh))
		{
			if(NIL_P(name))
				result = _self->createEntity(wrapenum<Ogre::SceneManager::PrefabType>(mesh));
			else
				result = _self->createEntity(wrap<Ogre::String>(name),wrapenum<Ogre::SceneManager::PrefabType>(mesh));
		}else if(rb_obj_is_kind_of(mesh,rb_cOgreMesh))
		{
			if(NIL_P(name))
				result = _self->createEntity(wrap<Ogre::MeshPtr>(mesh));
			else
				result = _self->createEntity(wrap<Ogre::String>(name),wrap<Ogre::MeshPtr>(mesh));
		}else{
			if(NIL_P(name))
				result = _self->createEntity(wrap<Ogre::String>(mesh));
			else
				result = _self->createEntity(wrap<Ogre::String>(name),wrap<Ogre::String>(mesh));
		}

		if(!NIL_P(opt))
		{
			VALUE temp;
			if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("material")))))
				result->setMaterial(wrap<Ogre::MaterialPtr>(temp));

			if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("visibility_flags")))))
				result->setVisibilityFlags(NUM2ULONG(temp));


		}

		return wrap(result);
	)
	return Qnil;
}
/*
 * call-seq:
 *   get_entity(name) -> Entity or nil
 *
 * get a Entity or nil
*/
VALUE _getEntity(VALUE self,VALUE name)
{
	return wrap(_self->getEntity(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   has_entity?(name) -> bool
 *
 * return true if Entity with that name exist
*/
VALUE _hasEntity(VALUE self,VALUE name)
{
	return wrap(_self->hasEntity(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroy_entity([name]) -> nil
 *
 * destroy a Entity.
 * if not name is given, destroy all Entitys
*/
VALUE _destroyEntity(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	RUBYTRY(
	if(NIL_P(name))
		_self->destroyAllEntities();
	else if(rb_obj_is_kind_of(name,rb_cOgreEntity))
		_self->destroyEntity(wrap<Ogre::Entity*>(name));
	else
		_self->destroyEntity(wrap<Ogre::String>(name));
	)
	return Qnil;
}



/*
 * call-seq:
 *   create_camera(name) -> Camera
 * 
 * creates a Camera.
*/
VALUE _createCamera(int argc,VALUE *argv,VALUE self)
{
	VALUE name,opt;
	Ogre::Camera *result;

	rb_scan_args(argc, argv, "11",&name,&opt);

	RUBYTRY(
		result = _self->createCamera(wrap<Ogre::String>(name));

	if(rb_obj_is_kind_of(opt,rb_cHash))
	{
		VALUE temp;
		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("position")))))
			result->setPosition(wrap<Ogre::Vector3>(temp));
		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("look_at")))))
			result->lookAt(wrap<Ogre::Vector3>(temp));

		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("near_clip_distance")))))
			result->setNearClipDistance(NUM2DBL(temp));
	}
	return wrap(result);
	)

	return Qnil;
}
/*
 * call-seq:
 *   get_camera(name) -> Camera or nil
 * 
 * get a Camera or nil
*/
VALUE _getCamera(VALUE self,VALUE name)
{
	return wrap(_self->getCamera(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   has_camera?(name) -> bool
 * 
 * return true if light with that name exist
*/
VALUE _hasCamera(VALUE self,VALUE name)
{
	return wrap(_self->hasCamera(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroy_camera([name]) -> nil
 * 
 * destroy a Camera.
 * if not name is given, destroy all cameras
*/
VALUE _destroyCamera(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	RUBYTRY(
	if(NIL_P(name))
		_self->destroyAllCameras();
	else if(rb_obj_is_kind_of(name,rb_cOgreCamera))
		_self->destroyCamera(wrap<Ogre::Camera*>(name));
	else
		_self->destroyCamera(wrap<Ogre::String>(name));
	)
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
 *   create_billboard_chain([name]) -> BillboardChain
 *
 * creates a BillboardChain.
*/
VALUE _createBillboardChain(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	RUBYTRY(
	if(NIL_P(name))
		return wrap(_self->createBillboardChain());
	else
		return wrap(_self->createBillboardChain(wrap<Ogre::String>(name)));
	)
	return Qnil;
}
/*
 * call-seq:
 *   get_billboard_chain(name) -> BillboardChain or nil
 *
 * get a BillboardChain or nil
*/
VALUE _getBillboardChain(VALUE self,VALUE name)
{
	return wrap(_self->getBillboardChain(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   has_billboard_chain?(name) -> bool
 *
 * return true if BillboardChain with that name exist
*/
VALUE _hasBillboardChain(VALUE self,VALUE name)
{
	return wrap(_self->hasBillboardChain(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroy_billboard_chain([name]) -> nil
 *
 * destroy a BillboardChain.
 * if not name is given, destroy all billboardchains
*/
VALUE _destroyBillboardChain(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	RUBYTRY(
	if(NIL_P(name))
		_self->destroyAllBillboardChains();
	else if(rb_obj_is_kind_of(name,rb_cOgreBillboardChain))
		_self->destroyBillboardChain(wrap<Ogre::BillboardChain*>(name));
	else
		_self->destroyBillboardChain(wrap<Ogre::String>(name));
	)
	return Qnil;
}


/*
 * call-seq:
 *   create_ribbon_trail([name]) -> RibbonTrail
 *
 * creates a RibbonTrail.
*/
VALUE _createRibbonTrail(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	RUBYTRY(
	if(NIL_P(name))
		return wrap(_self->createRibbonTrail());
	else
		return wrap(_self->createRibbonTrail(wrap<Ogre::String>(name)));
	)
	return Qnil;
}
/*
 * call-seq:
 *   get_ribbon_trail(name) -> RibbonTrail or nil
 *
 * get a RibbonTrail or nil
*/
VALUE _getRibbonTrail(VALUE self,VALUE name)
{
	return wrap(_self->getRibbonTrail(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   has_ribbon_trail?(name) -> bool
 *
 * return true if RibbonTrail with that name exist
*/
VALUE _hasRibbonTrail(VALUE self,VALUE name)
{
	return wrap(_self->hasRibbonTrail(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroy_ribbon_trail([name]) -> nil
 *
 * destroy a RibbonTrail.
 * if not name is given, destroy all RibbonTrails
*/
VALUE _destroyRibbonTrail(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	RUBYTRY(
	if(NIL_P(name))
		_self->destroyAllRibbonTrails();
	else if(rb_obj_is_kind_of(name,rb_cOgreRibbonTrail))
		_self->destroyRibbonTrail(wrap<Ogre::RibbonTrail*>(name));
	else
		_self->destroyRibbonTrail(wrap<Ogre::String>(name));
	)
	return Qnil;
}



/*
 * call-seq:
 *   create_billboard_set([name]) -> BillboardSet
 *
 * creates a BillboardSet.
*/
VALUE _createBillboardSet(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	RUBYTRY(
	if(NIL_P(name))
		return wrap(_self->createBillboardSet());
	else
		return wrap(_self->createBillboardSet(wrap<Ogre::String>(name)));
	)
	return Qnil;
}
/*
 * call-seq:
 *   get_billboard_set(name) -> BillboardSet or nil
 *
 * get a BillboardSet or nil
*/
VALUE _getBillboardSet(VALUE self,VALUE name)
{
	return wrap(_self->getBillboardSet(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   has_billboard_set?(name) -> bool
 *
 * return true if BillboardSet with that name exist
*/
VALUE _hasBillboardSet(VALUE self,VALUE name)
{
	return wrap(_self->hasBillboardSet(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroy_billboard_set([name]) -> nil
 *
 * destroy a BillboardSet.
 * if not name is given, destroy all BillboardSets
*/
VALUE _destroyBillboardSet(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	RUBYTRY(
	if(NIL_P(name))
		_self->destroyAllBillboardSets();
	else if(rb_obj_is_kind_of(name,rb_cOgreBillboardSet))
		_self->destroyBillboardSet(wrap<Ogre::BillboardSet*>(name));
	else
		_self->destroyBillboardSet(wrap<Ogre::String>(name));
	)
	return Qnil;
}

/*
 * call-seq:
 *   create_manual_object([name]) -> ManualObject
 *
 * creates a ManualObject.
*/
VALUE _createManualObject(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	RUBYTRY(
	if(NIL_P(name))
		return wrap(_self->createManualObject());
	else
		return wrap(_self->createManualObject(wrap<Ogre::String>(name)));
	)
	return Qnil;
}
/*
 * call-seq:
 *   get_manual_object(name) -> ManualObject or nil
 *
 * get a ManualObject or nil
*/
VALUE _getManualObject(VALUE self,VALUE name)
{
	return wrap(_self->getManualObject(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   has_manual_object?(name) -> bool
 *
 * return true if ManualObject with that name exist
*/
VALUE _hasManualObject(VALUE self,VALUE name)
{
	return wrap(_self->hasManualObject(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroy_manual_object([name]) -> nil
 *
 * destroy a ManualObject.
 * if not name is given, destroy all manual_objects
*/
VALUE _destroyManualObject(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	RUBYTRY(
	if(NIL_P(name))
		_self->destroyAllManualObjects();
//	else if(rb_obj_is_kind_of(name,rb_cOgreManualObject))
//		_self->destroyManualObject(wrap<Ogre::ManualObject*>(name));
	else
		_self->destroyManualObject(wrap<Ogre::String>(name));
	)
	return Qnil;
}

/*
 * call-seq:
 *   create_particle_system(name,template) -> ParticleSystem
 *
 * creates a ManualObject.
*/
VALUE _createParticleSystem(int argc,VALUE *argv,VALUE self)
{
	VALUE name,temp;
	rb_scan_args(argc, argv, "20",&name,&temp);
	RUBYTRY(
		return wrap(_self->createParticleSystem(wrap<Ogre::String>(name),wrap<Ogre::String>(temp)));
	)
	return Qnil;
}
/*
 * call-seq:
 *   get_particle_system(name) -> ParticleSystem or nil
 *
 * get a ManualObject or nil
*/
VALUE _getParticleSystem(VALUE self,VALUE name)
{
	return wrap(_self->getParticleSystem(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   has_particle_system?(name) -> bool
 *
 * return true if ParticleSystem with that name exist
*/
VALUE _hasParticleSystem(VALUE self,VALUE name)
{
	return wrap(_self->hasParticleSystem(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroy_particle_system([name]) -> nil
 *
 * destroy a ParticleSystem.
 * if not name is given, destroy all ParticleSystems
*/
VALUE _destroyParticleSystem(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	RUBYTRY(
	if(NIL_P(name))
		_self->destroyAllParticleSystems();
	else if(rb_obj_is_kind_of(name,rb_cOgreParticleSystem))
		_self->destroyParticleSystem(wrap<Ogre::ParticleSystem*>(name));
	else
		_self->destroyParticleSystem(wrap<Ogre::String>(name));
	)
	return Qnil;
}


/*
 * call-seq:
 *   create_scene_node([name]) -> Light
 * 
 * creates a SceneNode.
*/
VALUE _createSceneNode(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	RUBYTRY(
	if(NIL_P(name))
		return wrap(_self->createSceneNode());
	else
		return wrap(_self->createSceneNode(wrap<Ogre::String>(name)));
	)
	return Qnil;
}
/*
 * call-seq:
 *   get_scene_node(name) -> SceneNode or nil
 * 
 * get a SceneNode or nil
*/
VALUE _getSceneNode(VALUE self,VALUE name)
{
	return wrap(_self->getSceneNode(wrap<Ogre::String>(name)));
}
/*
 * call-seq:
 *   has_scene_node?(name) -> bool
 * 
 * return true if SceneNode with that name not exist
*/
VALUE _hasSceneNode(VALUE self,VALUE name)
{
	return wrap(_self->hasSceneNode(wrap<Ogre::String>(name)));
}

/*
 * call-seq:
 *   destroy_scene_node(name) -> nil
 *
 * destroy a SceneNode.
 * 
*/
VALUE _destroySceneNode(VALUE self,VALUE name)
{
	RUBYTRY(
	if(rb_obj_is_kind_of(name,rb_cOgreSceneNode))
		_self->destroySceneNode(wrap<Ogre::SceneNode*>(name));
	else
		_self->destroySceneNode(wrap<Ogre::String>(name));
	)
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
	
	rb_define_method(rb_cOgreSceneManager,"create_light",RUBY_METHOD_FUNC(_createLight),-1);
	rb_define_method(rb_cOgreSceneManager,"get_light",RUBY_METHOD_FUNC(_getLight),1);
	rb_define_method(rb_cOgreSceneManager,"has_light?",RUBY_METHOD_FUNC(_hasLight),1);
	rb_define_method(rb_cOgreSceneManager,"destroy_light",RUBY_METHOD_FUNC(_destroyLight),-1);

	rb_define_method(rb_cOgreSceneManager,"create_entity",RUBY_METHOD_FUNC(_createEntity),-1);
	rb_define_method(rb_cOgreSceneManager,"get_entity",RUBY_METHOD_FUNC(_getEntity),1);
	rb_define_method(rb_cOgreSceneManager,"has_entity?",RUBY_METHOD_FUNC(_hasEntity),1);
	rb_define_method(rb_cOgreSceneManager,"destroy_entity",RUBY_METHOD_FUNC(_destroyEntity),-1);

	rb_define_method(rb_cOgreSceneManager,"create_billboard_chain",RUBY_METHOD_FUNC(_createBillboardChain),-1);
	rb_define_method(rb_cOgreSceneManager,"get_billboard_chain",RUBY_METHOD_FUNC(_getBillboardChain),1);
	rb_define_method(rb_cOgreSceneManager,"has_billboard_chain?",RUBY_METHOD_FUNC(_hasBillboardChain),1);
	rb_define_method(rb_cOgreSceneManager,"destroy_billboard_chain",RUBY_METHOD_FUNC(_destroyBillboardChain),-1);

	rb_define_method(rb_cOgreSceneManager,"create_billboard_set",RUBY_METHOD_FUNC(_createBillboardSet),-1);
	rb_define_method(rb_cOgreSceneManager,"get_billboard_set",RUBY_METHOD_FUNC(_getBillboardSet),1);
	rb_define_method(rb_cOgreSceneManager,"has_billboard_set?",RUBY_METHOD_FUNC(_hasBillboardSet),1);
	rb_define_method(rb_cOgreSceneManager,"destroy_billboard_set",RUBY_METHOD_FUNC(_destroyBillboardSet),-1);

	rb_define_method(rb_cOgreSceneManager,"create_ribbon_trail",RUBY_METHOD_FUNC(_createRibbonTrail),-1);
	rb_define_method(rb_cOgreSceneManager,"get_ribbon_trail",RUBY_METHOD_FUNC(_getRibbonTrail),1);
	rb_define_method(rb_cOgreSceneManager,"has_ribbon_trail?",RUBY_METHOD_FUNC(_hasRibbonTrail),1);
	rb_define_method(rb_cOgreSceneManager,"destroy_ribbon_trail",RUBY_METHOD_FUNC(_destroyRibbonTrail),-1);

	rb_define_method(rb_cOgreSceneManager,"create_manual_object",RUBY_METHOD_FUNC(_createManualObject),-1);
	rb_define_method(rb_cOgreSceneManager,"get_manual_object",RUBY_METHOD_FUNC(_getManualObject),1);
	rb_define_method(rb_cOgreSceneManager,"has_manual_object?",RUBY_METHOD_FUNC(_hasManualObject),1);
	rb_define_method(rb_cOgreSceneManager,"destroy_manual_object",RUBY_METHOD_FUNC(_destroyManualObject),-1);

	rb_define_method(rb_cOgreSceneManager,"create_particle_system",RUBY_METHOD_FUNC(_createParticleSystem),-1);
	rb_define_method(rb_cOgreSceneManager,"get_particle_system",RUBY_METHOD_FUNC(_getParticleSystem),1);
	rb_define_method(rb_cOgreSceneManager,"has_particle_system?",RUBY_METHOD_FUNC(_hasParticleSystem),1);
	rb_define_method(rb_cOgreSceneManager,"destroy_particle_system",RUBY_METHOD_FUNC(_destroyParticleSystem),-1);

	rb_define_method(rb_cOgreSceneManager,"create_camera",RUBY_METHOD_FUNC(_createCamera),-1);
	rb_define_method(rb_cOgreSceneManager,"get_camera",RUBY_METHOD_FUNC(_getCamera),1);
	rb_define_method(rb_cOgreSceneManager,"has_camera?",RUBY_METHOD_FUNC(_hasCamera),1);
	rb_define_method(rb_cOgreSceneManager,"destroy_camera",RUBY_METHOD_FUNC(_destroyCamera),-1);
	
	rb_define_method(rb_cOgreSceneManager,"each_camera",RUBY_METHOD_FUNC(_each_camera),0);

	rb_define_method(rb_cOgreSceneManager,"create_scene_node",RUBY_METHOD_FUNC(_createSceneNode),-1);
	rb_define_method(rb_cOgreSceneManager,"get_scene_node",RUBY_METHOD_FUNC(_getSceneNode),1);
	rb_define_method(rb_cOgreSceneManager,"has_scene_node?",RUBY_METHOD_FUNC(_hasSceneNode),1);
	rb_define_method(rb_cOgreSceneManager,"destroy_scene_node",RUBY_METHOD_FUNC(_destroySceneNode),1);

	rb_define_method(rb_cOgreSceneManager,"root_scene_node",RUBY_METHOD_FUNC(_getRootSceneNode),0);
	rb_define_method(rb_cOgreSceneManager,"current_viewport",RUBY_METHOD_FUNC(_getCurrentViewport),0);
	rb_define_method(rb_cOgreSceneManager,"sky_plane_node",RUBY_METHOD_FUNC(_getSkyPlaneNode),0);
	rb_define_method(rb_cOgreSceneManager,"sky_box_node",RUBY_METHOD_FUNC(_getSkyBoxNode),0);
	rb_define_method(rb_cOgreSceneManager,"sky_dome_node",RUBY_METHOD_FUNC(_getSkyDomeNode),0);
	
	rb_define_attr_method(rb_cOgreSceneManager,"shadow_color",_getShadowColour,_setShadowColour);
	rb_define_attr_method(rb_cOgreSceneManager,"ambient_light",_getAmbientLight,_setAmbientLight);

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

	registerenum<Ogre::SceneManager::PrefabType>("Ogre::SceneManager::PrefabType")
		.add(Ogre::SceneManager::PT_CUBE,"cube")
		.add(Ogre::SceneManager::PT_PLANE,"plane")
		.add(Ogre::SceneManager::PT_SPHERE,"sphere");
}
