#include "ogrecamera.hpp"
#include "ogreexception.hpp"
#include "ogrefrustum.hpp"
#include "ogremovableobject.hpp"
#include "ogrevector3.hpp"
#include "ogrequaternion.hpp"
#include "ogreradian.hpp"
#define _self wrap<Ogre::Camera*>(self)
VALUE rb_cOgreCamera;

VALUE wrap(const Ogre::Camera* camera )
{
	return wrap(const_cast<Ogre::Camera *>(camera));
}

namespace RubyOgre
{
namespace Camera
{

macro_attr(Position,Ogre::Vector3)
macro_attr(Direction,Ogre::Vector3)
macro_attr(Orientation,Ogre::Quaternion)
macro_attr(LodBias,Ogre::Real)
macro_attr(LodCamera,Ogre::Camera*)

macro_attr(CullingFrustum,Ogre::Frustum*)
macro_attr(AutoAspectRatio,bool)

macro_attr(UseRenderingDistance,bool)

singlereturn(getViewport)

singlereturn(getUp)
singlereturn(getRight)

singlereturn(getDerivedOrientation)
singlereturn(getDerivedPosition)
singlereturn(getDerivedDirection)
singlereturn(getDerivedUp)
singlereturn(getDerivedRight)

singlereturn(getRealOrientation)
singlereturn(getRealPosition)
singlereturn(getRealDirection)
singlereturn(getRealUp)
singlereturn(getRealRight)

/*
*/
VALUE _roll(VALUE self,VALUE angle)
{
	_self->roll(wrap<Ogre::Radian>(angle));
	return self;
}
/*
*/
VALUE _yaw(VALUE self,VALUE angle)
{
	_self->yaw(wrap<Ogre::Radian>(angle));
	return self;
}
/*
*/
VALUE _pitch(VALUE self,VALUE angle)
{
	_self->pitch(wrap<Ogre::Radian>(angle));
	return self;
}

VALUE _lookAt(int argc,VALUE *argv,VALUE self)
{
	VALUE x,y,z;
	rb_scan_args(argc, argv, "12",&x,&y,&z);
	if(argc == 3)
		_self->lookAt(NUM2DBL(x),NUM2DBL(y),NUM2DBL(z));
	else
		_self->lookAt(wrap<Ogre::Vector3>(x));
	return self;
}

}
}

/*
 * Document-class: Ogre::Camera
 * 
 * This class represents an Camera.
*/ 

void Init_OgreCamera(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_mOgreMovableObject = rb_define_module_under(rb_mOgre,"MovableObject");
	
	rb_define_attr(rb_cOgreCamera,"position",1,1);
	rb_define_attr(rb_cOgreCamera,"direction",1,1);
	rb_define_attr(rb_cOgreCamera,"orientation",1,1);
	
	rb_define_attr(rb_cOgreCamera,"lod_bias",1,1);
	rb_define_attr(rb_cOgreCamera,"lod_camera",1,1);
#endif
	using namespace RubyOgre::Camera;
	rb_cOgreCamera = rb_define_class_under(rb_mOgre,"Camera",rb_cOgreFrustum);
	rb_undef_alloc_func(rb_cOgreCamera);

	rb_define_method(rb_cOgreCamera,"viewport",RUBY_METHOD_FUNC(_getViewport),0);

	rb_define_method(rb_cOgreCamera,"roll",RUBY_METHOD_FUNC(_roll),1);
	rb_define_method(rb_cOgreCamera,"yaw",RUBY_METHOD_FUNC(_yaw),1);
	rb_define_method(rb_cOgreCamera,"pitch",RUBY_METHOD_FUNC(_pitch),1);
	
	rb_define_method(rb_cOgreCamera,"look_at",RUBY_METHOD_FUNC(_lookAt),-1);

	rb_define_attr_method(rb_cOgreCamera,"position",_getPosition,_setPosition);
	rb_define_attr_method(rb_cOgreCamera,"direction",_getDirection,_setDirection);
	rb_define_attr_method(rb_cOgreCamera,"orientation",_getOrientation,_setOrientation);
	
	rb_define_attr_method(rb_cOgreCamera,"lod_bias",_getLodBias,_setLodBias);
	rb_define_attr_method(rb_cOgreCamera,"lod_camera",_getLodCamera,_setLodCamera);

	registerklass<Ogre::Camera>(rb_cOgreCamera);
}
