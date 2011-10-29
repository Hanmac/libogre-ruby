#include "ogrelayerblendmode.hpp"
#include "ogrecolor.hpp"
#define _self wrap<Ogre::LayerBlendModeEx*>(self)
VALUE rb_cOgreLayerBlendMode;

VALUE OgreLayerBlendMode_alloc(VALUE self)
{
	return wrap(new Ogre::LayerBlendModeEx);
}

macro_attr_prop(LayerBlendMode,blendType,Ogre::LayerBlendType)
macro_attr_prop_with_func(LayerBlendMode,factor,DBL2NUM,NUM2DBL)


VALUE OgreLayerBlendMode_get_arg1(VALUE self)
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
VALUE OgreLayerBlendMode_get_arg2(VALUE self)
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

VALUE OgreLayerBlendMode_set_arg1(VALUE self,VALUE val)
{
	switch(_self->blendType){
	case Ogre::LBT_COLOUR:
		_self->colourArg1 = *wrap<Ogre::ColourValue*>(val);
	case Ogre::LBT_ALPHA:
		_self->alphaArg1 = NUM2DBL(val);
		break;
	}
	return val;
}
VALUE OgreLayerBlendMode_set_arg2(VALUE self,VALUE val)
{
	switch(_self->blendType){
	case Ogre::LBT_COLOUR:
			_self->colourArg2 = *wrap<Ogre::ColourValue*>(val);
		break;
	case Ogre::LBT_ALPHA:
		_self->alphaArg2 = NUM2DBL(val);
		break;
	}
	return val;
}
void Init_OgreLayerBlendMode(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_define_attr(rb_cOgreLayerBlendMode,"blendType",1,1);
	rb_define_attr(rb_cOgreLayerBlendMode,"arg1",1,1);
	rb_define_attr(rb_cOgreLayerBlendMode,"arg2",1,1);
	rb_define_attr(rb_cOgreLayerBlendMode,"factor",1,1);

#endif
	rb_cOgreLayerBlendMode = rb_define_class_under(rb_mOgre,"LayerBlendMode",rb_cObject);
	rb_define_alloc_func(rb_cOgreLayerBlendMode,OgreLayerBlendMode_alloc);
	
	rb_define_attr_method(rb_cOgreLayerBlendMode,"blendType",OgreLayerBlendMode_get_blendType,OgreLayerBlendMode_set_blendType);
	
	rb_define_attr_method(rb_cOgreLayerBlendMode,"arg1",OgreLayerBlendMode_get_arg1,OgreLayerBlendMode_set_arg1);
	rb_define_attr_method(rb_cOgreLayerBlendMode,"arg2",OgreLayerBlendMode_get_arg2,OgreLayerBlendMode_set_arg2);
	rb_define_attr_method(rb_cOgreLayerBlendMode,"factor",OgreLayerBlendMode_get_factor,OgreLayerBlendMode_set_factor);
}
