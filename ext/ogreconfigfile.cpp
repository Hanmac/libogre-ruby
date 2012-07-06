#include "ogreconfigfile.hpp"
#include "ogredatastream.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::ConfigFile*>(self)
VALUE rb_cOgreConfigFile;

namespace RubyOgre {
namespace ConfigFile {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::ConfigFile);
}
/*
*/
VALUE _initialize(int argc,VALUE* argv,VALUE self)
{
	VALUE file,hash,temp;
	bool trimWhitespace = true;
	rb_scan_args(argc, argv, "11",&file,&hash);
	Ogre::String separators("\t:=");
	if(rb_obj_is_kind_of(hash,rb_cHash))
	{
		if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("trimWhitespace")))))
			trimWhitespace = RTEST(temp);
		if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("separators")))))
			separators = wrap<Ogre::String>(temp);
	}
	RUBYTRY(
		if(rb_obj_is_kind_of(file,rb_cOgreDataStream))
			_self->load(wrap<Ogre::DataStreamPtr>(file),separators,trimWhitespace);
		else if(!rb_obj_is_kind_of(hash,rb_cHash) || NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("group_name")))))
			_self->load(wrap<Ogre::String>(file),separators,trimWhitespace);
		else
			_self->load(wrap<Ogre::String>(file),wrap<Ogre::String>(temp),separators,trimWhitespace);
	)
	return self;
}
/*
 * call-seq:
 *   [id[,sction]] -> [String] or nil
 * 
 * returns all settings of the given key.
*/
VALUE _get(int argc,VALUE* argv,VALUE self)
{
	VALUE key,section;
	rb_scan_args(argc, argv, "11",&key,&section);
	Ogre::String temp;
	if(NIL_P(section))
		temp = Ogre::StringUtil::BLANK;
	else
		temp = wrap<Ogre::String>(section);
	RUBYTRY(return wrap<Ogre::String>(_self->getMultiSetting(wrap<Ogre::String>(key),temp));)
	return Qnil;
}
/*
 * call-seq:
 *   each {|section,key,value| }
 *   each -> Enumerator
 * 
 * iterates the ConfigFile
*/
VALUE _each(VALUE self)
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

}}
/*
 * Document-class: Ogre::ConfigFile
 * 
 * This class represents an configfile.
*/
void Init_OgreConfigFile(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	using namespace RubyOgre::ConfigFile;

	rb_cOgreConfigFile = rb_define_class_under(rb_mOgre,"ConfigFile",rb_cObject);
	rb_define_alloc_func(rb_cOgreConfigFile,_alloc);
	rb_define_method(rb_cOgreConfigFile,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_method(rb_cOgreConfigFile,"[]",RUBY_METHOD_FUNC(_get),-1);
	rb_define_method(rb_cOgreConfigFile,"each",RUBY_METHOD_FUNC(_each),0);

	rb_include_module(rb_cOgreConfigFile,rb_mEnumerable);

	registerklass<Ogre::ConfigFile>(rb_cOgreConfigFile);
}
