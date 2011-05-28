#include "ogrelayerblendmode.hpp"
#include "ogrecolor.hpp"
#define _self wrap<Ogre::LayerBlendModeEx*>(self)
VALUE rb_cOgreLayerBlendMode;

VALUE OgreLayerBlendMode_alloc(VALUE self)
{
	return wrap(new Ogre::LayerBlendModeEx);
}
/*:nodoc:
*/
VALUE OgreLayerBlendMode_get_blendType(VALUE self)
{
	return wrap(_self->blendType);
}
/*:nodoc:
*/
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
/*:nodoc:
*/
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
/*:nodoc:
*/
VALUE OgreLayerBlendMode_get_factor(VALUE self)
{
	return DBL2NUM(_self->factor);
}
/*:nodoc:
*/
VALUE OgreLayerBlendMode_set_blendType(VALUE self,VALUE type)
{
	_self->blendType = wrap<Ogre::LayerBlendType>(type);
	return type;
}
/*:nodoc:
*/
VALUE OgreLayerBlendMode_set_factor(VALUE self,VALUE fac)
{
	_self->factor = NUM2DBL(fac);
	return fac;
}

/*:nodoc:
*/
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
/*:nodoc:
*/
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
	
	rb_define_method(rb_cOgreLayerBlendMode,"blendType",RUBY_METHOD_FUNC(OgreLayerBlendMode_get_blendType),0);
	rb_define_method(rb_cOgreLayerBlendMode,"blendType=",RUBY_METHOD_FUNC(OgreLayerBlendMode_set_blendType),1);
	
	rb_define_method(rb_cOgreLayerBlendMode,"arg1",RUBY_METHOD_FUNC(OgreLayerBlendMode_get_arg1),0);
	rb_define_method(rb_cOgreLayerBlendMode,"arg2",RUBY_METHOD_FUNC(OgreLayerBlendMode_get_arg2),0);
	rb_define_method(rb_cOgreLayerBlendMode,"factor",RUBY_METHOD_FUNC(OgreLayerBlendMode_get_factor),0);
	
	rb_define_method(rb_cOgreLayerBlendMode,"arg1=",RUBY_METHOD_FUNC(OgreLayerBlendMode_set_arg1),1);
	rb_define_method(rb_cOgreLayerBlendMode,"arg2=",RUBY_METHOD_FUNC(OgreLayerBlendMode_set_arg2),1);
	rb_define_method(rb_cOgreLayerBlendMode,"factor=",RUBY_METHOD_FUNC(OgreLayerBlendMode_set_factor),1);
}
