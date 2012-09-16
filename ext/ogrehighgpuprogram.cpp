/*
 * ogrehighgpuprogram.cpp
 *
 *  Created on: 29.08.2012
 *      Author: hanmac
 */

#include "ogreresource.hpp"
#include "ogreexception.hpp"
#define _manager Ogre::HighLevelGpuProgramManager::getSingletonPtr()

VALUE rb_cOgreHighGpuProgram;

template <>
VALUE wrap< Ogre::HighLevelGpuProgramPtr >(const Ogre::HighLevelGpuProgramPtr &gpuprogram )
{
	if(gpuprogram.isNull())
		return Qnil;
	return Data_Wrap_Struct(rb_cOgreHighGpuProgram, NULL, free, new Ogre::GpuProgramPtr(gpuprogram));
}

namespace RubyOgre {
namespace HighGpuProgram {

VALUE _singleton_createProgram(VALUE self,VALUE name,VALUE groupName,VALUE language,VALUE type)
{
	RUBYTRY(
	return wrap(_manager->createProgram(wrap<Ogre::String>(name),
		unwrapResourceGroup(groupName,Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME),
		wrap<Ogre::String>(language),
		wrapenum<Ogre::GpuProgramType>(type)
		));
	)
	return Qnil;
}
VALUE _singleton_supported(VALUE self,VALUE language)
{
	return wrap(_manager->isLanguageSupported(wrap<Ogre::String>(language)));
}

}
}

void Init_OgreHighGpuProgram(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);
	rb_cOgreGpuProgram = rb_define_class_under(rb_mOgre,"GpuProgram",rb_cOgreResource);
#endif
	using namespace RubyOgre::HighGpuProgram;

	rb_cOgreHighGpuProgram = rb_define_class_under(rb_mOgre,"HighGpuProgram",rb_cOgreGpuProgram);

	rb_define_singleton_method(rb_cOgreHighGpuProgram,"create_program",RUBY_METHOD_FUNC(_singleton_createProgram),4);
	rb_define_singleton_method(rb_cOgreHighGpuProgram,"supported?",RUBY_METHOD_FUNC(_singleton_supported),1);

}
