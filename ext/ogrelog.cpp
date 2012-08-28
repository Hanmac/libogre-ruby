#include "ogrelog.hpp"
#include "ogreloglistener.hpp"
#define _self wrap<Ogre::Log*>(self)
#define _singleton wrap<Ogre::LogManager*>(self)
VALUE rb_cOgreLog;


struct RubyLog{
	Ogre::String name;
};

template <>
VALUE wrap< Ogre::Log >(Ogre::Log *log )
{
	if(log == NULL)
		return Qnil;
	RubyLog *temp = new RubyLog;
	temp->name = log->getName();
	return Data_Wrap_Struct(rb_cOgreLog, NULL, NULL, log);
}

template <>
Ogre::Log* wrap< Ogre::Log* >(const VALUE &vlog)
{
	if ( ! rb_obj_is_kind_of(vlog, rb_cOgreLog) )
		return NULL;
	try{
		RubyLog *log;
		Data_Get_Struct( vlog, RubyLog, log);
		return Ogre::LogManager::getSingletonPtr()->getLog(log->name);
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
		return NULL;
	}
}
template <>
Ogre::LogManager* wrap< Ogre::LogManager* >(const VALUE &vlog)
{
	Ogre::LogManager *temp = Ogre::LogManager::getSingletonPtr();
	return temp != NULL ? temp : new Ogre::LogManager;
}

namespace RubyOgre
{
namespace Log
{

singlereturn(getName)

/*
*/
VALUE _log(int argc,VALUE *argv,VALUE self)
{
	VALUE message,level,mask;
	rb_scan_args(argc, argv, "13",&message,&level,&mask);
	Ogre::LogMessageLevel olevel = wrapenum<Ogre::LogMessageLevel>(level);
	if(NIL_P(mask))
		mask = Qfalse;
	RUBYTRY(_self->logMessage(wrap<Ogre::String>(message), olevel, RTEST(mask));)
	return self;
}
/*
*/
VALUE _logshift(VALUE self,VALUE message)
{
	RUBYTRY(_self->logMessage(wrap<Ogre::String>(message), Ogre::LML_NORMAL, false);)
	return self;
}

macro_attr_enum(LogDetail,Ogre::LoggingLevel)
macro_attr_bool(TimeStampEnabled)

/*
*/
VALUE _destroy(VALUE self)
{
	Ogre::LogManager::getSingletonPtr()->destroyLog(_self);
	return Qnil;
}
/*
*/
VALUE _addListener(VALUE self,VALUE val)
{
	_self->addListener(wrap<Ogre::LogListener*>(val));
	return self;
}
/*
*/
VALUE _removeListener(VALUE self,VALUE val)
{
	_self->removeListener(wrap<Ogre::LogListener*>(val));
	return self;
}



/*
*/
VALUE _singleton_createLog(int argc,VALUE *argv,VALUE self)
{
	VALUE name,defaultlog,debuggeroutput,suppressFileOutput;
	rb_scan_args(argc, argv, "13",&name,&defaultlog,&debuggeroutput,&suppressFileOutput);
	if(NIL_P(defaultlog))
		defaultlog = Qfalse;
	if(NIL_P(debuggeroutput))
		debuggeroutput = Qtrue;
	if(NIL_P(suppressFileOutput))
		suppressFileOutput = Qfalse;
	RUBYTRY(return wrap(_singleton->createLog(wrap<Ogre::String>(name),RTEST(defaultlog),RTEST(debuggeroutput),RTEST(suppressFileOutput)));)
	return Qnil;
}
/*
*/
VALUE _singleton_log(int argc,VALUE *argv,VALUE self)
{
	VALUE message,level,mask;
	rb_scan_args(argc, argv, "13",&message,&level,&mask);
	Ogre::LogMessageLevel olevel = wrapenum<Ogre::LogMessageLevel>(level);
	if(NIL_P(mask))
		mask = Qfalse;
	RUBYTRY(_singleton->logMessage(wrap<Ogre::String>(message), olevel, RTEST(mask));)
	return self;
}
/*
*/
VALUE _singleton_logshift(VALUE self,VALUE message)
{
	RUBYTRY(_singleton->logMessage(wrap<Ogre::String>(message), Ogre::LML_NORMAL, false);)
	return self;
}

/*
 * call-seq:
 *   manager[name] -> Ogre::Log or nil
 * 
 * returns a log
 * ===Return value
 * Ogre::Log or nil
*/
VALUE _singleton_getLog(VALUE self,VALUE name)
{
	RUBYTRY(return wrap(_singleton->getLog(wrap<Ogre::String>(name)));)
	return Qnil;
}
/*
*/
VALUE _singleton_getdefaultLog(VALUE self)
{
	return wrap(_singleton->getDefaultLog());
}
/*
*/
VALUE _singleton_setdefaultLog(VALUE self,VALUE log)
{
	_singleton->setDefaultLog(wrap<Ogre::Log*>(log));
	return log;
}

}
}

void Init_OgreLog(VALUE rb_mOgre)
{
	#if 0
	rb_mOgre = rb_define_module("Ogre");

	rb_define_attr(rb_cOgreLog,"detail",1,1);
	rb_define_attr(rb_cOgreLog,"timestamp",1,1);

	#endif
	using namespace RubyOgre::Log;
	rb_cOgreLog = rb_define_class_under(rb_mOgre,"Log",rb_cObject);
	rb_undef_alloc_func(rb_cOgreLog);
	
	rb_define_method(rb_cOgreLog,"name",RUBY_METHOD_FUNC(_getName),0);
	rb_define_method(rb_cOgreLog,"log",RUBY_METHOD_FUNC(_log),-1);
	rb_define_method(rb_cOgreLog,"<<",RUBY_METHOD_FUNC(_logshift),1);
	
	rb_define_attr_method(rb_cOgreLog,"detail",_getLogDetail,_setLogDetail);
	rb_define_attr_method(rb_cOgreLog,"timestamp",_getTimeStampEnabled,_setTimeStampEnabled);

	rb_define_method(rb_cOgreLog,"addListener",RUBY_METHOD_FUNC(_addListener),1);
	rb_define_method(rb_cOgreLog,"removeListener",RUBY_METHOD_FUNC(_removeListener),1);

	rb_define_method(rb_cOgreLog,"destroy",RUBY_METHOD_FUNC(_destroy),0);
	
	rb_define_singleton_method(rb_cOgreLog,"createLog",RUBY_METHOD_FUNC(_singleton_createLog),-1);
	rb_define_singleton_method(rb_cOgreLog,"log",RUBY_METHOD_FUNC(_singleton_log),-1);
	rb_define_singleton_method(rb_cOgreLog,"<<",RUBY_METHOD_FUNC(_singleton_logshift),1);
	rb_define_singleton_method(rb_cOgreLog,"[]",RUBY_METHOD_FUNC(_singleton_getLog),1);
	rb_define_singleton_method(rb_cOgreLog,"defaultLog",RUBY_METHOD_FUNC(_singleton_getdefaultLog),0);
	rb_define_singleton_method(rb_cOgreLog,"defaultLog=",RUBY_METHOD_FUNC(_singleton_setdefaultLog),1);

	registerenum<Ogre::LoggingLevel>("Ogre::LoggingLevel")
		.add(Ogre::LL_LOW,"low")
		.add(Ogre::LL_NORMAL,"normal")
		.add(Ogre::LL_BOREME,"boreme");
	registerenum<Ogre::LogMessageLevel>("Ogre::LogMessageLevel",Ogre::LML_NORMAL)
		.add(Ogre::LML_TRIVIAL,"trivial")
		.add(Ogre::LML_NORMAL,"normal")
		.add(Ogre::LML_CRITICAL,"critical");
}
