#include "ogrepass.hpp"
#include "ogrecolor.hpp"
#include "ogretextureunitstate.hpp"
#include "ogreexception.hpp"

#define _self wrap<Ogre::Pass*>(self)
VALUE rb_cOgrePass;
namespace RubyOgre {
namespace Pass {

macro_attr(Name,Ogre::String)

macro_attr(Ambient,Ogre::ColourValue)
macro_attr(Diffuse,Ogre::ColourValue)
macro_attr(Specular,Ogre::ColourValue)
macro_attr(SelfIllumination,Ogre::ColourValue)

macro_attr(DepthCheckEnabled,bool)
macro_attr(DepthWriteEnabled,bool)
macro_attr(ColourWriteEnabled,bool)
macro_attr(LightingEnabled,bool)

macro_attr_with_func(PassIterationCount,ULONG2NUM,NUM2ULONG)

macro_attr(StartLight,unsigned short)
macro_attr(LightCountPerIteration,unsigned short)

macro_attr_enum(IlluminationStage,Ogre::IlluminationStage)
macro_attr_enum(ShadingMode,Ogre::ShadeOptions)
macro_attr_enum(PolygonMode,Ogre::PolygonMode)

macro_attr(PolygonModeOverrideable,bool)
macro_attr(LightScissoringEnabled,bool)
macro_attr(LightClipPlanesEnabled,bool)

macro_attr(NormaliseNormals,bool)
macro_attr(TransparentSortingEnabled,bool)
macro_attr(TransparentSortingForced,bool)

singlereturn(createTextureUnitState)

singlereturn(getFogOverride)

VALUE _getFogMode(VALUE self)
{
	return wrapenum(_self->getFogMode());
}

singlereturn(getFogColour)
singlereturn(getFogDensity)
singlereturn(getFogStart)
singlereturn(getFogEnd)


singlereturn(getVertexProgramName)
singlereturn(getShadowCasterVertexProgramName)
singlereturn(getShadowReceiverVertexProgramName)
singlereturn(getShadowReceiverFragmentProgramName)
singlereturn(getFragmentProgramName)
singlereturn(getGeometryProgramName)


singlereturn(getVertexProgram)
singlereturn(getShadowCasterVertexProgram)
singlereturn(getShadowReceiverVertexProgram)
singlereturn(getShadowReceiverFragmentProgram)
singlereturn(getFragmentProgram)
singlereturn(getGeometryProgram)

/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<Ogre::TextureUnitState*>( _self->getTextureUnitStateIterator());
	return self;
}

/*
 *
 */
VALUE _get(VALUE self,VALUE idx)
{
	if(rb_obj_is_kind_of(idx,rb_cString))
		return wrap(_self->getTextureUnitState(wrap<Ogre::String>(idx)));
	else{
		size_t i = NUM2UINT(idx);
		if(i < _self->getNumTextureUnitStates())
			return wrap(_self->getTextureUnitState(i));
		return Qnil;
	}
}



/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=_getName(self);
	return rb_f_sprintf(3,array);
}

VALUE _setFogOverride(VALUE self,VALUE val)
{
	_self->setFog(
		RTEST(val),
		_self->getFogMode(),
		_self->getFogColour(),
		_self->getFogDensity(),
		_self->getFogStart(),
		_self->getFogEnd()
	);
	return val;
}

VALUE _setFogMode(VALUE self,VALUE val)
{
	_self->setFog(
		_self->getFogOverride(),
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
		_self->getFogOverride(),
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
		_self->getFogOverride(),
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
		_self->getFogOverride(),
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
		_self->getFogOverride(),
		_self->getFogMode(),
		_self->getFogColour(),
		_self->getFogDensity(),
		_self->getFogStart(),
		NUM2DBL(val)
	);
	return val;
}


VALUE _setVertexProgram(VALUE self,VALUE name)
{
	_self->setVertexProgram(wrap<Ogre::String>(name),false);
	return name;
}

VALUE _setShadowCasterVertexProgram(VALUE self,VALUE name)
{
	_self->setShadowCasterVertexProgram(wrap<Ogre::String>(name));
	return name;
}

VALUE _setShadowReceiverVertexProgram(VALUE self,VALUE name)
{
	_self->setShadowReceiverVertexProgram(wrap<Ogre::String>(name));
	return name;
}

VALUE _setShadowReceiverFragmentProgram(VALUE self,VALUE name)
{
	_self->setShadowReceiverFragmentProgram(wrap<Ogre::String>(name));
	return name;
}

VALUE _setFragmentProgram(VALUE self,VALUE name)
{
	_self->setFragmentProgram(wrap<Ogre::String>(name),false);
	return name;
}

VALUE _setGeometryProgram(VALUE self,VALUE name)
{
	_self->setGeometryProgram(wrap<Ogre::String>(name),false);
	return name;
}


}}

void Init_OgrePass(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");

	rb_define_attr(rb_cOgrePass,"name",1,1);
	rb_define_attr(rb_cOgrePass,"index",1,0);

	rb_define_attr(rb_cOgrePass,"ambient",1,1);
	rb_define_attr(rb_cOgrePass,"diffuse",1,1);
	rb_define_attr(rb_cOgrePass,"specular",1,1);
	rb_define_attr(rb_cOgrePass,"self_illumination",1,1);

	rb_define_attr(rb_cOgrePass,"fog_override",1,1);
	rb_define_attr(rb_cOgrePass,"fog_mode",1,1);
	rb_define_attr(rb_cOgrePass,"fog_color",1,1);
	rb_define_attr(rb_cOgrePass,"fog_density",1,1);
	rb_define_attr(rb_cOgrePass,"fog_start",1,1);
	rb_define_attr(rb_cOgrePass,"fog_end",1,1);


	rb_define_attr(rb_cOgrePass,"vertex_program_name",1,1);
	rb_define_attr(rb_cOgrePass,"shadow_caster_vertex_program_name",1,1);
	rb_define_attr(rb_cOgrePass,"shadow_receiver_vertex_program_name",1,1);
	rb_define_attr(rb_cOgrePass,"shadow_receiver_fragment_program_name",1,1);
	rb_define_attr(rb_cOgrePass,"fragment_program_name",1,1);
	rb_define_attr(rb_cOgrePass,"geometry_program_name",1,1);

	rb_define_attr(rb_cOgrePass,"vertex_program",1,0);
	rb_define_attr(rb_cOgrePass,"shadow_caster_vertex_program",1,0);
	rb_define_attr(rb_cOgrePass,"shadow_receiver_vertex_program",1,0);
	rb_define_attr(rb_cOgrePass,"shadow_receiver_fragment_program",1,0);
	rb_define_attr(rb_cOgrePass,"fragment_program",1,0);
	rb_define_attr(rb_cOgrePass,"geometry_program",1,0);

#endif
	using namespace RubyOgre::Pass;

	rb_cOgrePass = rb_define_class_under(rb_mOgre,"Pass",rb_cObject);
	rb_undef_alloc_func(rb_cOgrePass);
	rb_define_attr_method(rb_cOgrePass,"name",_getName,_setName);

	rb_define_attr_method(rb_cOgrePass,"ambient",_getAmbient,_setAmbient);
	rb_define_attr_method(rb_cOgrePass,"diffuse",_getDiffuse,_setDiffuse);
	rb_define_attr_method(rb_cOgrePass,"specular",_getSpecular,_setSpecular);
	rb_define_attr_method(rb_cOgrePass,"self_illumination",_getSelfIllumination,_setSelfIllumination);

	rb_define_attr_method(rb_cOgrePass,"fog_override",_getFogOverride,_setFogOverride);
	rb_define_attr_method(rb_cOgrePass,"fog_mode",_getFogMode,_setFogMode);
	rb_define_attr_method(rb_cOgrePass,"fog_color",_getFogColour,_setFogColour);
	rb_define_attr_method(rb_cOgrePass,"fog_density",_getFogDensity,_setFogDensity);
	rb_define_attr_method(rb_cOgrePass,"fog_start",_getFogStart,_setFogStart);
	rb_define_attr_method(rb_cOgrePass,"fog_end",_getFogEnd,_setFogEnd);

	
	rb_define_attr_method(rb_cOgrePass,"illuminationStage",_getIlluminationStage,_setIlluminationStage);


	rb_define_attr_method(rb_cOgrePass,"vertex_program_name",_getVertexProgramName,_setVertexProgram);
	rb_define_attr_method(rb_cOgrePass,"shadow_caster_vertex_program_name",_getShadowCasterVertexProgramName,_setShadowCasterVertexProgram);
	rb_define_attr_method(rb_cOgrePass,"shadow_receiver_vertex_program_name",_getShadowReceiverVertexProgramName,_setShadowReceiverVertexProgram);
	rb_define_attr_method(rb_cOgrePass,"shadow_receiver_fragment_program_name",_getShadowReceiverFragmentProgramName,_setShadowReceiverFragmentProgram);
	rb_define_attr_method(rb_cOgrePass,"fragment_program_name",_getFragmentProgramName,_setFragmentProgram);
	rb_define_attr_method(rb_cOgrePass,"geometry_program_name",_getGeometryProgramName,_setGeometryProgram);

	rb_define_method(rb_cOgrePass,"vertex_program",RUBY_METHOD_FUNC(_getVertexProgramName),0);// :nodoc:
	rb_define_method(rb_cOgrePass,"shadow_caster_vertex_program",RUBY_METHOD_FUNC(_getShadowCasterVertexProgramName),0);// :nodoc:
	rb_define_method(rb_cOgrePass,"shadow_receiver_vertex_program",RUBY_METHOD_FUNC(_getShadowReceiverVertexProgramName),0);// :nodoc:
	rb_define_method(rb_cOgrePass,"shadow_receiver_fragment_program",RUBY_METHOD_FUNC(_getShadowReceiverFragmentProgramName),0);// :nodoc:
	rb_define_method(rb_cOgrePass,"fragment_program",RUBY_METHOD_FUNC(_getFragmentProgramName),0);// :nodoc:
	rb_define_method(rb_cOgrePass,"geometry_program",RUBY_METHOD_FUNC(_getGeometryProgramName),0);// :nodoc:

	rb_define_method(rb_cOgrePass,"create",RUBY_METHOD_FUNC(_createTextureUnitState),0);

	rb_define_method(rb_cOgrePass,"[]",RUBY_METHOD_FUNC(_get),1);
	rb_define_method(rb_cOgrePass,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cOgrePass,rb_mEnumerable);
	
	rb_define_method(rb_cOgrePass,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	registerklass<Ogre::Pass>(rb_cOgrePass);

	registerenum<Ogre::FogMode>("Ogre::FogMode")
		.add(Ogre::FOG_NONE,"none")
		.add(Ogre::FOG_EXP,"exp")
		.add(Ogre::FOG_EXP2,"exp2")
		.add(Ogre::FOG_LINEAR,"linear");

	registerenum<Ogre::IlluminationStage>("Ogre::IlluminationStage")
		.add(Ogre::IS_AMBIENT,"ambient")
		.add(Ogre::IS_PER_LIGHT,"per_light")
		.add(Ogre::IS_DECAL,"decal");
	//registerenum(Ogre::IS_DECAL,"decal");

}
