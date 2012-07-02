/*
 * ogregpuprogram.cpp
 *
 *  Created on: 01.07.2012
 *      Author: hanmac
 */

#include "ogreresource.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::GpuProgram*>(self)
#define _manager Ogre::GpuProgramManager::getSingletonPtr()
VALUE rb_cOgreGpuProgram;

template <>
VALUE wrap< Ogre::GpuProgramPtr >(Ogre::GpuProgramPtr *GpuProgram )
{
	return Data_Wrap_Struct(rb_cOgreGpuProgram, NULL, free, GpuProgram);
}

template <>
Ogre::GpuProgram* wrap< Ogre::GpuProgram* >(const VALUE &vGpuProgram)
{
	return unwrapPtr<Ogre::GpuProgramPtr>(vGpuProgram, rb_cOgreGpuProgram)->get();
}


namespace RubyOgre {
namespace GpuProgram {

macro_attr(Source,Ogre::String)
macro_attr(SourceFile,Ogre::String)
macro_attr(SyntaxCode,Ogre::String)
macro_attr_enum(Type,Ogre::GpuProgramType)

macro_attr_bool(SkeletalAnimationIncluded)
macro_attr_bool(MorphAnimationIncluded)
macro_attr_bool(VertexTextureFetchRequired)
macro_attr_bool(AdjacencyInfoRequired)

singlereturn(getLanguage)


VALUE _singleton_createProgram(VALUE self,VALUE name,VALUE groupName,VALUE filename,VALUE type,VALUE syntaxcode)
{
	return wrap(_manager->createProgram(wrap<Ogre::String>(name),
		unwrapResourceGroup(groupName,Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME),
		wrap<Ogre::String>(filename),
		wrapenum<Ogre::GpuProgramType>(type),
		wrap<Ogre::String>(syntaxcode)
		));
}

VALUE _singleton_createProgramFromString(VALUE self,VALUE name,VALUE groupName,VALUE string,VALUE type,VALUE syntaxcode)
{
	return wrap(_manager->createProgramFromString(wrap<Ogre::String>(name),
		unwrapResourceGroup(groupName,Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME),
		wrap<Ogre::String>(string),
		wrapenum<Ogre::GpuProgramType>(type),
		wrap<Ogre::String>(syntaxcode)
		));
}

}
}

void Init_OgreGpuProgram(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);
#endif
	using namespace RubyOgre::GpuProgram;

	rb_cOgreGpuProgram = rb_define_class_under(rb_mOgre,"GpuProgram",rb_cOgreResource);

	rb_define_attr_method(rb_cOgreGpuProgram,"source",_getSource,_setSource);
	rb_define_attr_method(rb_cOgreGpuProgram,"source_file",_getSourceFile,_setSourceFile);
	rb_define_attr_method(rb_cOgreGpuProgram,"syntaxCode",_getSyntaxCode,_setSyntaxCode);
	rb_define_attr_method(rb_cOgreGpuProgram,"type",_getType,_setType);

	rb_define_method(rb_cOgreResource,"language",RUBY_METHOD_FUNC(_getLanguage),0);

	rb_define_singleton_method(rb_cOgreResource,"create_program",RUBY_METHOD_FUNC(_singleton_createProgram),5);
	rb_define_singleton_method(rb_cOgreResource,"create_program_from_string",RUBY_METHOD_FUNC(_singleton_createProgramFromString),5);


	registerenum<Ogre::GpuProgramType>("Ogre::GpuProgramType")
		.add(Ogre::GPT_VERTEX_PROGRAM,"vertex")
		.add(Ogre::GPT_FRAGMENT_PROGRAM,"fragment")
		.add(Ogre::GPT_GEOMETRY_PROGRAM,"geometry");
}



