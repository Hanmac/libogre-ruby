#include "ogrelog.hpp"
#include "ogreloglistener.hpp"
#define _self wrap<Ogre::Log*>(self)
#define _singleton wrap<Ogre::LogManager*>(self)
VALUE rb_cOgreLog;
/*
*/
VALUE OgreLog_getName(VALUE self)
{
	return wrap(_self->getName());
}

/*
*/
VALUE OgreLog_log(int argc,VALUE *argv,VALUE self)
{
	VALUE message,level,mask;
	rb_scan_args(argc, argv, "13",&message,&level,&mask);
	Ogre::LogMessageLevel olevel;
	if(NIL_P(level))	
		olevel = Ogre::LML_NORMAL;
	else
		olevel = wrap<Ogre::LogMessageLevel>(level);
	if(NIL_P(mask))
		mask = Qfalse;
	try{
		message = rb_funcall(message,rb_intern("to_s"),0);
		_self->logMessage(rb_string_value_cstr(&message), olevel, RTEST(mask));
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
	return self;
}
/*
*/
VALUE OgreLog_logshift(VALUE self,VALUE message)
{
	try{
		message = rb_funcall(message,rb_intern("to_s"),0);
		_self->logMessage(rb_string_value_cstr(&message), Ogre::LML_NORMAL, false);
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
	return self;
}
/*
*/
VALUE OgreLog_getLogDetail(VALUE self)
{
	return wrap(_self->getLogDetail());
}
/*
*/
VALUE OgreLog_setLogDetail(VALUE self,VALUE val)
{
	_self->setLogDetail(wrap<Ogre::LoggingLevel>(val));
	return val;
}
/*
*/
VALUE OgreLog_isTimeStampEnabled(VALUE self)
{
	return _self->isTimeStampEnabled() ? Qtrue : Qfalse;
}
/*
*/
VALUE OgreLog_setTimeStampEnabled(VALUE self,VALUE val)
{
	_self->setTimeStampEnabled(RTEST(val));
	return val;
}
/*
*/
VALUE OgreLog_destroy(VALUE self)
{
	Ogre::LogManager::getSingletonPtr()->destroyLog(_self);
	return Qnil;
}
/*
*/
VALUE OgreLog_addListener(VALUE self,VALUE val)
{
	Ogre::LogListener *listener = wrap<Ogre::LogListener*>(val);
	if(listener)
		_self->addListener(listener);
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreLogListener),rb_obj_classname(val));
	return self;
}
/*
*/
VALUE OgreLog_removeListener(VALUE self,VALUE val)
{
	Ogre::LogListener *listener = wrap<Ogre::LogListener*>(val);
	if(listener)
		_self->removeListener(listener);
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreLogListener),rb_obj_classname(val));
	return self;
}



/*
*/
VALUE OgreLog_singleton_createLog(int argc,VALUE *argv,VALUE self)
{
	VALUE name,defaultlog,debuggeroutput,suppressFileOutput;
	rb_scan_args(argc, argv, "13",&name,&defaultlog,&debuggeroutput,&suppressFileOutput);
	if(NIL_P(defaultlog))
		defaultlog = Qfalse;
	if(NIL_P(debuggeroutput))
		debuggeroutput = Qtrue;
	if(NIL_P(suppressFileOutput))
		suppressFileOutput = Qfalse;
	try{
		return wrap(_singleton->createLog(rb_string_value_cstr(&name),RTEST(defaultlog),RTEST(debuggeroutput),RTEST(suppressFileOutput)));
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
		return Qnil;
	}
}
/*
*/
VALUE OgreLog_singleton_log(int argc,VALUE *argv,VALUE self)
{
	VALUE message,level,mask;
	rb_scan_args(argc, argv, "13",&message,&level,&mask);
	Ogre::LogMessageLevel olevel;
	if(NIL_P(level))	
		olevel = Ogre::LML_NORMAL;
	else
		olevel = wrap<Ogre::LogMessageLevel>(level);
	if(NIL_P(mask))
		mask = Qfalse;
	try{
		message = rb_funcall(message,rb_intern("to_s"),0);
		_singleton->logMessage(rb_string_value_cstr(&message), olevel, RTEST(mask));
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
	return self;
}
/*
*/
VALUE OgreLog_singleton_logshift(VALUE self,VALUE message)
{
	try{
		message = rb_funcall(message,rb_intern("to_s"),0);
		_singleton->logMessage(rb_string_value_cstr(&message), Ogre::LML_NORMAL, false);
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
	}
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
VALUE OgreLog_singleton_getLog(VALUE self,VALUE name)
{
	try{
		return wrap(_singleton->getLog(rb_string_value_cstr(&name)));
	}catch(Ogre::Exception& e){
		rb_raise(wrap(e));
		return Qnil;
	}
}
/*
*/
VALUE OgreLog_singleton_getdefaultLog(VALUE self)
{
	Ogre::Log *temp = _singleton->getDefaultLog();
	return temp ? wrap(temp) : Qnil;
}
/*
*/
VALUE OgreLog_singleton_setdefaultLog(VALUE self,VALUE log)
{
	if (rb_obj_is_kind_of(log, rb_cOgreLog))
		_singleton->setDefaultLog(wrap<Ogre::Log*>(log));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreLog),rb_obj_classname(log));
	return log;
}


void Init_OgreLog(VALUE rb_mOgre)
{
	#if 0
	rb_mOgre = rb_define_module("Ogre");
	#endif
	rb_cOgreLog = rb_define_class_under(rb_mOgre,"Log",rb_cObject);
	rb_undef_alloc_func(rb_cOgreLog);
	
	rb_define_method(rb_cOgreLog,"name",RUBY_METHOD_FUNC(OgreLog_getName),0);
	rb_define_method(rb_cOgreLog,"log",RUBY_METHOD_FUNC(OgreLog_log),-1);
	rb_define_method(rb_cOgreLog,"<<",RUBY_METHOD_FUNC(OgreLog_logshift),1);
	
	rb_define_method(rb_cOgreLog,"detail",RUBY_METHOD_FUNC(OgreLog_getLogDetail),0);
	rb_define_method(rb_cOgreLog,"detail=",RUBY_METHOD_FUNC(OgreLog_setLogDetail),1);

	rb_define_method(rb_cOgreLog,"timestamp",RUBY_METHOD_FUNC(OgreLog_isTimeStampEnabled),0);
	rb_define_method(rb_cOgreLog,"timestamp=",RUBY_METHOD_FUNC(OgreLog_setTimeStampEnabled),1);

	rb_define_method(rb_cOgreLog,"addListener",RUBY_METHOD_FUNC(OgreLog_addListener),1);
	rb_define_method(rb_cOgreLog,"removeListener",RUBY_METHOD_FUNC(OgreLog_removeListener),1);

	rb_define_method(rb_cOgreLog,"destroy",RUBY_METHOD_FUNC(OgreLog_destroy),0);
	
	rb_define_singleton_method(rb_cOgreLog,"createLog",RUBY_METHOD_FUNC(OgreLog_singleton_createLog),-1);
	rb_define_singleton_method(rb_cOgreLog,"log",RUBY_METHOD_FUNC(OgreLog_singleton_log),-1);
	rb_define_singleton_method(rb_cOgreLog,"<<",RUBY_METHOD_FUNC(OgreLog_singleton_logshift),1);
	rb_define_singleton_method(rb_cOgreLog,"[]",RUBY_METHOD_FUNC(OgreLog_singleton_getLog),1);
	rb_define_singleton_method(rb_cOgreLog,"defaultLog",RUBY_METHOD_FUNC(OgreLog_singleton_getdefaultLog),0);
	rb_define_singleton_method(rb_cOgreLog,"defaultLog=",RUBY_METHOD_FUNC(OgreLog_singleton_setdefaultLog),1);
}
