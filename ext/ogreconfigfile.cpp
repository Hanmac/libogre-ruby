#include "ogreconfigfile.hpp"
#include "ogredatastream.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::ConfigFile*>(self)
VALUE rb_cOgreConfigFile;

VALUE OgreConfigFile_alloc(VALUE self)
{
	Ogre::ConfigFile *temp = new Ogre::ConfigFile;
	return wrap(temp);
}
/*
*/
VALUE OgreConfigFile_initialize(int argc,VALUE* argv,VALUE self)
{
	VALUE file,hash,temp;
	bool trimWhitespace;
	rb_scan_args(argc, argv, "11",&file,&hash);
	Ogre::String separators;
	if(!rb_obj_is_kind_of(hash,rb_cHash) || NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("trimWhitespace")))))
		trimWhitespace = true;
	else
		trimWhitespace = RTEST(temp);
	if(!rb_obj_is_kind_of(hash,rb_cHash) || NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("separators")))))
		separators = "\t:=";
	else
		separators = rb_string_value_cstr(&temp);
	try{
		if(rb_obj_is_kind_of(file,rb_cOgreDataStream))
			_self->load((Ogre::DataStreamPtr)wrap<Ogre::DataStream*>(file),separators,trimWhitespace);
		if(!rb_obj_is_kind_of(hash,rb_cHash) || NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("group_name")))))
			_self->load(rb_string_value_cstr(&file),separators,trimWhitespace);
		else
			_self->load(rb_string_value_cstr(&file),rb_string_value_cstr(&temp),separators,trimWhitespace);
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
	return self;
}

/*
*/
VALUE OgreConfigFile_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	Ogre::ConfigFile::SectionIterator sec = _self->getSectionIterator();
	Ogre::ConfigFile::SettingsBySection::iterator it;
	Ogre::ConfigFile::SettingsMultiMap::iterator it2;
	for (it = sec.begin(); it != sec.end(); ++it) {
		for (it2 = it->second->begin();it2 != it->second->end(); ++it2) {
			rb_yield_values(3,ID2SYM(rb_intern(it->first.c_str())),ID2SYM(rb_intern(it2->first.c_str())),wrap(it2->second));
		}
	}
	return self;
}

/*
*/
void Init_OgreConfigFile(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreConfigFile = rb_define_class_under(rb_mOgre,"ConfigFile",rb_cObject);
	rb_define_alloc_func(rb_cOgreConfigFile,OgreConfigFile_alloc);
	rb_define_method(rb_cOgreConfigFile,"initialize",RUBY_METHOD_FUNC(OgreConfigFile_initialize),-1);
	rb_define_method(rb_cOgreConfigFile,"each",RUBY_METHOD_FUNC(OgreConfigFile_each),0);

	rb_include_module(rb_cOgreConfigFile,rb_mEnumerable);
}
