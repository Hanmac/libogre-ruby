#ifndef __RubyOgreConfigFile_H__
#define __RubyOgreConfigFile_H__

#include "main.hpp"
void Init_OgreConfigFile(VALUE rb_mOgre);
extern VALUE rb_cOgreConfigFile;

template <>
inline VALUE wrap< Ogre::ConfigFile >(Ogre::ConfigFile *configfile )
{
	return Data_Wrap_Struct(rb_cOgreConfigFile, NULL, NULL, configfile);
}

template <>
inline Ogre::ConfigFile* wrap< Ogre::ConfigFile* >(const VALUE &vconfigfile)
{
	if ( ! rb_obj_is_kind_of(vconfigfile, rb_cOgreConfigFile) )
		return NULL;
	Ogre::ConfigFile *configfile;
  Data_Get_Struct( vconfigfile, Ogre::ConfigFile, configfile);
	return configfile;
}
#endif /* __RubyOgreConfigFile_H__ */
