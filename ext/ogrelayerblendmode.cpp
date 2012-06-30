#include "ogrelayerblendmode.hpp"
#include "ogrecolor.hpp"
#include "ogreexception.hpp"

#define _self wrap<Ogre::LayerBlendModeEx*>(self)
VALUE rb_cOgreLayerBlendMode;

template <>
VALUE wrap< Ogre::LayerBlendModeEx >(Ogre::LayerBlendModeEx *layer )
{
	return Data_Wrap_Struct(rb_cOgreLayerBlendMode, NULL, free, layer);
}


namespace RubyOgre {
namespace LayerBlendMode {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::LayerBlendModeEx);
}

macro_attr_prop_enum(blendType,Ogre::LayerBlendType)
macro_attr_prop(factor,double)


VALUE _get_arg1(VALUE self)
{
	VALUE result = Qnil;
	switch(_self->blendType){
	case Ogre::LBT_COLOUR:
		result=wrap(_self->colourArg1);
		break;
	case Ogre::LBT_ALPHA:
		result=DBL2NUM(_self->alphaArg1);
		break;
	}
	return result;
}
VALUE _get_arg2(VALUE self)
{
	VALUE result = Qnil;
	switch(_self->blendType){
	case Ogre::LBT_COLOUR:
		result=wrap(_self->colourArg2);
		break;
	case Ogre::LBT_ALPHA:
		result=DBL2NUM(_self->alphaArg2);
		break;
	}
	return result;
}

VALUE _set_arg1(VALUE self,VALUE val)
{
	switch(_self->blendType){
	case Ogre::LBT_COLOUR:
		_self->colourArg1 = wrap<Ogre::ColourValue>(val);
		break;
	case Ogre::LBT_ALPHA:
		_self->alphaArg1 = NUM2DBL(val);
		break;
	}
	return val;
}
VALUE _set_arg2(VALUE self,VALUE val)
{
	switch(_self->blendType){
	case Ogre::LBT_COLOUR:
		_self->colourArg2 = wrap<Ogre::ColourValue>(val);
		break;
	case Ogre::LBT_ALPHA:
		_self->alphaArg2 = NUM2DBL(val);
		break;
	}
	return val;
}

}}

void Init_OgreLayerBlendMode(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_define_attr(rb_cOgreLayerBlendMode,"blendType",1,1);
	rb_define_attr(rb_cOgreLayerBlendMode,"arg1",1,1);
	rb_define_attr(rb_cOgreLayerBlendMode,"arg2",1,1);
	rb_define_attr(rb_cOgreLayerBlendMode,"factor",1,1);

#endif
	using namespace RubyOgre::LayerBlendMode;

	rb_cOgreLayerBlendMode = rb_define_class_under(rb_mOgre,"LayerBlendMode",rb_cObject);
	rb_define_alloc_func(rb_cOgreLayerBlendMode,_alloc);
	
	rb_define_attr_method(rb_cOgreLayerBlendMode,"blendType",_get_blendType,_set_blendType);
	
	rb_define_attr_method(rb_cOgreLayerBlendMode,"arg1",_get_arg1,_set_arg1);
	rb_define_attr_method(rb_cOgreLayerBlendMode,"arg2",_get_arg2,_set_arg2);
	rb_define_attr_method(rb_cOgreLayerBlendMode,"factor",_get_factor,_set_factor);

	registerklass<Ogre::LayerBlendModeEx>(rb_cOgreLayerBlendMode);

	registerenum<Ogre::LayerBlendType>("Ogre::LayerBlendType")
		.add(Ogre::LBT_COLOUR,"color")
		.add(Ogre::LBT_ALPHA,"alpha");
}
